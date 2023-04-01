
// $Id: CfgEnv.cpp 692 2022-12-25 18:51:05Z duncang $

//=================================================================================================
// Original File Name : CfgEnv.cpp
// Original Author    : duncang
// Creation Date      : 2013-08-15
// Copyright          : Copyright © 2013 by Catraeus and Duncan Gray
//
// Description        :
//    Very widely used information.
//
//=================================================================================================

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include <caes/CaesString.hpp>

#include "CfgVersion.hpp"
#include "CfgEnv.hpp"
#include "../_PrjGlbl.hpp"

CfgEnv *CfgEnv::ce = NULL;

      CfgEnv::CfgEnv(int i_argc, char *i_argv[], char *i_envp[])
: argc(i_argc)
, argv(i_argv)
, envp(i_envp) {
  inFile = 0;

  verMaj  = VER_MAIN;
  verMin  = VER_POINT;
  buildNo = GIT_MARK;

  fileNameInputLine     = new char[MAX_LINE_LEN];
  CWD                   = new char[MAX_LINE_LEN];
  workingDir            = new char[MAX_LINE_LEN];
  fileNameRel           = new char[MAX_LINE_LEN];
  fileNameAbs           = new char[MAX_LINE_LEN];
  appId                 = new char[MAX_LINE_LEN];

  appName               = new char[sizeof(APP_NAME)+1];
  appDesc               = new char[sizeof(APP_DESC)+1];
  strCopyright          = new char[sizeof(STR_CPYR)+1];
  strAuthors            = new char[sizeof(STR_AUTH)+1];
  strUrl                = new char[sizeof(STR_URL)+1];
  strUrlLabel           = new char[sizeof(STR_URL_LBL)+1];

  cfgDirName            = new char[MAX_LINE_LEN];
  cfgFileName           = new char[MAX_LINE_LEN];
  cfgFileLines          = new char*[MAX_CFG_LINES];

//____________________________
  strcpy(appName,       APP_NAME);
  strcpy(appId,        "com.catraeus.AAS_");
  strcat(appId,         appName);
  strcpy(appDesc,       APP_DESC);
  strcpy(strCopyright,  STR_CPYR);
  strcpy(strAuthors,    STR_AUTH);
  strcpy(strUrl,        STR_URL);
  strcpy(strUrlLabel,   STR_URL_LBL);

  char *theErr = getcwd(CWD, 4096);
  if(theErr == NULL) {
    fprintf(stderr, "BAD CWD ... VERY STRANGE\n"); fflush(stderr);
  }
  strcpy(workingDir, CWD);

//____________________________
  *cfgDirName = '\0';
  if(envp != NULL) for(int i=0; envp[i] != NULL; i++){
    if(strncmp(envp[i], "HOME", 4) == 0) {
      char *p = &envp[i][5];
      strcpy(cfgDirName, p);
      }
    }
  strcat(cfgDirName, "/.");
  strcat(cfgDirName, appName);
  strcat(cfgDirName, "/");
  sprintf(cfgFileName, "%sconf", cfgDirName);
  ShowVersion();
  OpenCfgEnv();
  }
      CfgEnv::~CfgEnv(){
  delete cfgDirName;
  delete cfgFileName;
  delete cfgFileLines;
  delete appName;
  for(uint i=0; i<cfgFileLineCount; i++) {
    delete cfgFileLines[i];
    }
  WriteCfgFile();
  if(cfgFile != NULL)
    fclose(cfgFile);
}
void  CfgEnv::ShowVersion(void) {
  fprintf(stdout, "%s\n", appName);
  fprintf(stdout, "    %s\n", appDesc);
  fprintf(stdout, "    version %d.%d build %d\n", verMaj, verMin, buildNo);
  fprintf(stdout, "    %s\n", strCopyright);
  fprintf(stdout, "    CWD is %s\n", CWD);
  return;
}
CfgEnv *CfgEnv::GetInstance(int i_argc, char *i_argv[], char *i_envp[]) {
  if(ce == NULL)
    ce = new CfgEnv(i_argc, i_argv, i_envp);
  return ce;
}
CfgEnv *CfgEnv::GetInstance() {
  if(ce == NULL) {
    ce = new CfgEnv(0, NULL, NULL);
  }
  return ce;
}
//=================================================================================================
void  CfgEnv::SetupFile(void) {
  int accessMode;
  int accessAnswer;

  if(argc != 2) {
    fprintf(stdout, "Invocation doesn't seem to want to open a file.\n");
    return;
    }
  SetFileName(fileNameInputLine);
  accessMode = F_OK;
  accessAnswer = access(fileNameAbs, accessMode);
  if(accessAnswer == -1) {
    SetFileName((char *)"");
    inFile = 0;
    fprintf(stdout, "The command line input file has problems because %s.\n", strerror(errno));
    return;
    }
  inFile = fopen(fileNameAbs, "r");
  if(errno == 0) {
    fprintf(stdout, "The command line input file exists and can be opened.\n");
    fclose(inFile);
    inFile = 0;
    return;
    }
  SetFileName((char *)"");
  inFile = 0;
  fprintf(stdout, "The command line input file <%s>has problems being opened.\n", fileNameInputLine);
  return;
  }
void  CfgEnv::CleanupFileName(char *i_s) {
  char *pSrc;
  char *pDst;
  bool  cleaning;

  pSrc = i_s;
  pDst = i_s;
  while(*pSrc != '\0') {
    if( *pSrc == '\"' ||
        *pSrc == '\'' ||
        *pSrc == '`' ||
        ((*pSrc == '/') && (*(pSrc + 1) == '/')) ||
        0 ) {
      pSrc++;
      cleaning = true;
      }
    else {
      if(cleaning)
        *(pDst++) = *(pSrc++);
      else {
        pDst++;
        pSrc++;
        }
      }
    }
  *pDst = '\0';
  return;
  }
void  CfgEnv::SplitAbsPath(void) {
  char *pSrc;
  char *pDst;
  char *pMark;

  if(fileNameAbs[strlen(fileNameAbs) - 1] == '/') {
    if(strlen(fileNameAbs) == 1) {
      strcpy(workingDir, "/");
      fileNameRel[0] = '\0';
      return;
      }
    fileNameAbs[strlen(fileNameAbs) - 1] = '\0';
    strcpy(workingDir, fileNameAbs);
    fileNameRel[0] = '\0';
    return;
    }
  strcpy(workingDir, fileNameAbs);
  pMark = workingDir;
  pMark += strlen(fileNameAbs) - 1;
  while((*pMark != '/') && (pMark > workingDir))
    pMark--;
  pSrc = pMark + 1;
  pDst = fileNameRel;
  while(*pSrc != '\0')
    *(pDst++) = *(pSrc++);
  *pDst = '\0';
  *pMark = 0;

  return;
  }
void  CfgEnv::SetFileName(char *i_s) {
  bool isAbs;

  CleanupFileName(i_s);
  if(strlen(i_s) == 0) {
    strcpy(workingDir, CWD);
    strcpy(fileNameAbs, workingDir);
    strcpy(fileNameRel, "");
    return;
    }
  if(i_s[0] == '/')
    isAbs = true;
  else
    isAbs = false;

  if(!isAbs) {
    strcpy(fileNameAbs, workingDir);
    strcat(fileNameAbs, "/");
    strcat(fileNameAbs, i_s);
    CleanupFileName(fileNameAbs);
    }
  else
    strcpy(fileNameAbs, i_s);
  SplitAbsPath();
  return;
  }
//=================================================================================================
void  CfgEnv::OpenCfgEnv(void) {
  cfgFile = NULL;
  cfgFileLineCount = 0;
  cfgFileDirty = false;
  CheckForCfgDir();
  if(cfgFile == NULL) {
    }
  else {
    ReadCfgFile();
    //PrintCfgLines();
    }
  cfgFileDirty = false;
  //PrintCfgLines();
  //WriteCfgFile();
  return;
  }
void  CfgEnv::CheckForCfgDir(void) {
  int accessResult;

  accessResult = access(cfgDirName, F_OK);
  if(accessResult != 0) {
    if((errno) == ENOENT)
      NewCfgDir();
    else {
      ErrNoToString(errno, cfgDirName);
      SetupNoFile();
      }
    }
  else {
    CheckForCfgFile();
    }
  return;
  }
void  CfgEnv::NewCfgDir(void) {
  int accessResult = mkdir(cfgDirName, S_IRWXU);
  if(accessResult != 0) {
    if((errno) == EEXIST) {
      fprintf(stdout, "But wait, you called me because there was already a config dir at %s\n", cfgDirName);
      CheckForCfgFile();
      }
    else {
      ErrNoToString(errno, cfgFileName);
      SetupNoFile();
      }
    }
  else {
    fprintf(stdout, "%s made a configuration directory at %s\n", appName, cfgDirName);
    CheckForCfgFile();
    }
  return;
  }
void  CfgEnv::SetupNoFile(void) {
  fprintf(stdout, "%s is continuing without a config file.\n", appName);
  cfgFile = NULL;
  return;
  }
void  CfgEnv::CheckForCfgFile(void) {
  int accessResult;

  strcpy(cfgFileName, cfgDirName);
  strcat(cfgFileName, "/conf");
  accessResult = access(cfgFileName, F_OK);
  if(accessResult != 0) {
    if((errno) == ENOENT)
      NewCfgFile();
    else {
      ErrNoToString(errno, cfgFileName);
      SetupNoFile();
      }
    }
  else {
    OpenCfgFile();
    }
  return;
  }
void  CfgEnv::OpenCfgFile(void) {
  fprintf(stdout, "%s is opening a conf file at %s\n", appName, cfgFileName);
  cfgFile = fopen(cfgFileName, "rt");
  if(errno != 0) {
    fprintf(stderr, "%s creating conf file -- Suspicious error -- ", appName);
    ErrNoToString(errno, cfgFileName);
    }
  return;
  }
void  CfgEnv::NewCfgFile(void) {
  fprintf(stdout, "%s is creating a new conf file at %s\n", appName, cfgFileName);
  cfgFile = fopen(cfgFileName, "wt");
  if(errno != ENOENT) {
    fprintf(stderr, "%s creating conf file -- Suspicious error -- ", appName);
    ErrNoToString(errno, cfgFileName);
    }
  return;
  }
void  CfgEnv::ReadCfgFile(void) {
  char *buildStr;
  char *tStr;

  buildStr = (char *)malloc(MAX_LINE_LEN*sizeof(char));
  tStr = fgets(buildStr, MAX_LINE_LEN, cfgFile);
  if(tStr == NULL) {
    ErrNoToString(errno, buildStr);
    fprintf(stderr, "SYSTEM ERROR: %s   --  Reading cfg file lines from file: %s\n", buildStr, cfgFileName);fflush(stderr);
    }
  else {
    while((tStr != NULL) && (feof(cfgFile) == 0)) {
      StripNPTrail(tStr);
      if(*tStr != '\0') {
        cfgFileLines[cfgFileLineCount++] = tStr;
        buildStr = (char *)malloc(MAX_LINE_LEN*sizeof(char));
        }
      tStr = fgets(buildStr, MAX_LINE_LEN, cfgFile);
      }
    }
  return;
  }
void  CfgEnv::PrintCfgLines(void) {
  for(uint i=0; i<cfgFileLineCount; i++) {
    fprintf(stdout, "%s\n", cfgFileLines[i]);
    }
  return;
  }
void  CfgEnv::WriteCfgFile(void) {
  if(cfgFileDirty && (cfgFile != NULL)) {
    fclose(cfgFile);
    cfgFile = fopen(cfgFileName, "wt");
    for(uint i=0; i<cfgFileLineCount; i++) {
      fprintf(cfgFile, "%s\n", cfgFileLines[i]);
      }
    }
  fprintf(cfgFile, "\n");
  fclose(cfgFile);
  cfgFile = fopen(cfgFileName, "rt");
  cfgFileDirty = false;
  return;
  }

