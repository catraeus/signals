

//=================================================================================================
// Original File Name : Env.cpp
// Original Author    : duncang
// Creation Date      : May 31, 2012
// Copyright          : Copyright © 2012 - 2023 by Catraeus and Duncan Gray
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

#include "CfgEnv.hpp"
#include "CfgVersion.hpp"
#include "../_PrjGlbl.hpp"


CfgEnv *CfgEnv::ce = NULL;

        CfgEnv::CfgEnv                ( int i_argc, char *i_argv[], char *i_envp[] )
: argc(i_argc)
, argv(i_argv)
, envp(i_envp) {
  fileRd = 0;

  verMaj  = VER_MAIN;
  verMin  = VER_POINT;
  buildNo = GIT_MARK;

  sFileNm               = new char[MAX_LINE_LEN];
  CWD                   = new char[MAX_LINE_LEN];

  dirWorkRd             = new char[MAX_LINE_LEN];
  fileNameRelRd         = new char[MAX_LINE_LEN];
  fileNameAbsRd         = new char[MAX_LINE_LEN];

  dirWorkWr             = new char[MAX_LINE_LEN];
  fileNameRelWr         = new char[MAX_LINE_LEN];
  fileNameAbsWr         = new char[MAX_LINE_LEN];

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
  strcpy(appId,        "com.catraeus.AAS.");
  strcat(appId,         APP_ID_NM);
  strcpy(appDesc,       APP_DESC);
  strcpy(strCopyright,  STR_CPYR);
  strcpy(strAuthors,    STR_AUTH);
  strcpy(strUrl,        STR_URL);
  strcpy(strUrlLabel,   STR_URL_LBL);

  char *theErr = getcwd(CWD, 4096);
  if(theErr == NULL) {
    fprintf(stderr, "BAD CWD ... VERY STRANGE\n"); fflush(stderr);
  }
  strcpy(dirWorkRd, CWD);

//____________________________
  *cfgDirName = '\0';
  if(envp != NULL) for(int i=0; (envp[i] != NULL) && (*cfgDirName == '\0'); i++){
    if(strncmp((const char*)(envp[i]), "HOME", (size_t)4) == 0) {
      char *p = &((envp[i])[5]);
      strcpy(cfgDirName, p);
    }
  }
  strcat  (cfgDirName, "/.");
  strcat  (cfgDirName, appName);
  strcat  (cfgDirName, "/");
  sprintf (cfgFileName, "%sconf", cfgDirName);
  ShowVersion();
  CfgEnvInit();
  SetupFile();
}
        CfgEnv::~CfgEnv               ( void        ) {
  CfgFileWr();
  delete cfgDirName;
  delete cfgFileName;
  delete cfgFileLines;
  delete appName;
  for(uint i=0; i<cfgFileLineCount; i++) {
    delete cfgFileLines[i];
    }
  if(cfgFile != NULL)
    fclose(cfgFile);
}
void    CfgEnv::ShowVersion           ( void        ) {
  fprintf(stdout, "%s\n", appName);
  fprintf(stdout, "    %s\n", appDesc);
  fprintf(stdout, "    version %d.%d build %d\n", verMaj, verMin, buildNo);
  fprintf(stdout, "    %s\n", strCopyright);
  fprintf(stdout, "    CWD is %s\n", CWD);
  return;
}
CfgEnv *CfgEnv::GetInstance           ( int i_argc, char *i_argv[], char *i_envp[] ) {
  if(ce == NULL)
    ce = new CfgEnv(i_argc, i_argv, i_envp);
  return ce;
}
CfgEnv *CfgEnv::GetInstance           ( void        ) {
  if(ce == NULL) {
    ce = new CfgEnv(0, NULL, NULL);
  }
  return ce;
}
//=================================================================================================
void    CfgEnv::SetupFile             ( void        ) {
  int accessMode;
  int accessAnswer;
  char tStr[256];

  if(argc < 2) {
    fprintf(stdout, "Invocation doesn't seem to want to open a file.\n");
    return;
    }
  strcpy(sFileNm, argv[1]);
  SetFileNameRd(sFileNm);

  accessMode = F_OK;
  accessAnswer = access(fileNameAbsRd, accessMode);
  if(accessAnswer == -1) {
    SetFileNameRd((char *)"");
    fileRd = 0;
    char ss[128];
    ErrNoToString(errno, ss);
    fprintf(stdout, "The command line input file has problems because %s.\n", strerror(errno));
    return;
    }
  fileRd = fopen(fileNameAbsRd, "r");
  if(errno == 0) {
    fprintf(stdout, "The command line input file exists and can be opened.\n");
    fclose(fileRd);
    fileRd = 0;
    return;
    }
  strcpy(tStr, "");
  SetFileNameRd(tStr);
  fileRd = 0;
  fprintf(stdout, "The command line input file <%s>has problems being opened.\n", sFileNm);
  return;
  }
void    CfgEnv::SetDirWorkRd          ( char   *i_s ) {
  bool isAbs;
  char tStr[32768];

  PathNameCleanup(i_s);
  if(strlen(i_s) == 0) {
    strcpy(dirWorkRd, CWD);
    return;
    }
  if(i_s[0] == '/')
    isAbs = true;
  else
    isAbs = false;

  if(!isAbs) {
    strcpy(tStr, dirWorkRd);
    strcat(tStr, "/");
    strcat(tStr, i_s);
    PathNameCleanup(tStr);
    }
  else
    strcpy(tStr, i_s);
  PathExtractPath(tStr, dirWorkRd);
  return;
}
void    CfgEnv::SetFileNameRd         ( char   *i_s ) {
  bool isAbs;

  PathNameCleanup(i_s);
  if(strlen(i_s) == 0) {
    strcpy(fileNameAbsRd, dirWorkRd);
    strcpy(fileNameRelRd, "");
    return;
    }
  if(i_s[0] == '/')
    isAbs = true;
  else
    isAbs = false;

  if(!isAbs) {
    strcpy(fileNameAbsRd, dirWorkRd);
    strcat(fileNameAbsRd, "/");
    strcat(fileNameAbsRd, i_s);
    PathNameCleanup(fileNameAbsRd);
    }
  else
    strcpy(fileNameAbsRd, i_s);
  PathExtractFileName(fileNameAbsRd, fileNameRelRd);
  PathExtractPath(fileNameAbsRd, dirWorkRd);
  return;
  }
void    CfgEnv::SetFileNameWr         ( char   *i_s ) {
  bool isAbs;

  PathNameCleanup(i_s);
  if(strlen(i_s) == 0) {
    strcpy(fileNameAbsWr, dirWorkWr);
    strcpy(fileNameRelWr, "");
    return;
    }
  if(i_s[0] == '/')
    isAbs = true;
  else
    isAbs = false;

  if(!isAbs) {
    strcpy(fileNameAbsWr, dirWorkWr);
    strcat(fileNameAbsWr, "/");
    strcat(fileNameAbsWr, i_s);
    PathNameCleanup(fileNameAbsWr);
    }
  else
    strcpy(fileNameAbsWr, i_s);
  PathExtractFileName(fileNameAbsWr, fileNameRelWr);
  PathExtractPath(fileNameAbsWr, dirWorkWr);
  return;
  }
void    CfgEnv::CfgEnvInit            ( void        ) {
  cfgFile          = NULL;
  cfgFileLineCount = 0;
  cfgFileDirty     = false;
  CfgDirCheck();
  CfgFileOpen();
  if(cfgFile == NULL) {
    }
  else {
    CfgFileRd();
    //CfgPrint();
    }
  cfgFileDirty = false;
  //CfgPrint();
  //CfgFileWr();
  return;
  }
void    CfgEnv::CfgDirCheck           ( void        ) {
  int accessResult;

  accessResult = access(cfgDirName, F_OK);
  if(accessResult != 0) {
    if((errno) == ENOENT) {
      CfgDirNew();
      }
    else {
      ErrNoToString(errno, cfgDirName);
      CfgReBase();
      }
    }
  return;
  }
void    CfgEnv::CfgDirNew             ( void        ) {
  int accessResult = mkdir(cfgDirName, S_IRWXU);
  if(accessResult != 0) {
    if((errno) == EEXIST) {
      fprintf(stdout, "But wait, you called me because there wasn't a config dir at %s\n", cfgDirName);
      CfgFileCheck();
      }
    else {
      ErrNoToString(errno, cfgFileName);
      CfgReBase();
      }
    }
  else {
    fprintf(stdout, "basalt made a configuration directory at %s\n", cfgDirName);
    CfgFileNew();
    }
  return;
  }
void    CfgEnv::CfgReBase             ( void        ) {
  fprintf(stdout, "basalt is continuing without a config file.\n");
  cfgFile = NULL;
  return;
  }
void    CfgEnv::CfgFileCheck          ( void        ) {
  int accessResult;

  strcpy(cfgFileName, cfgDirName);
  strcat(cfgFileName, "/conf");
  accessResult = access(cfgFileName, F_OK);
  if(accessResult != 0) {
    if((errno) == ENOENT)
      CfgFileNew();
    else {
      ErrNoToString(errno, cfgFileName);
      CfgReBase();
      }
    }
  else {
    CfgFileOpen();
    }
  return;
  }
void    CfgEnv::CfgFileOpen           ( void        ) {
  fprintf(stdout, "%s is opening a conf file at %s\n", appName, cfgFileName);
  cfgFile = fopen(cfgFileName, "rt");
  if(cfgFile == 0) {
    fprintf(stdout, "%s creating conf file -- Suspicious error -- ", appName);
    ErrNoToString(errno, cfgFileName);
    }
  return;
  }
void    CfgEnv::CfgFileNew            ( void        ) {
  fprintf(stdout, "basalt is creating a new conf file at %s\n", cfgFileName);
  cfgFile = fopen(cfgFileName, "wt");
  if(errno != ENOENT) {
    fprintf(stdout, "basalt creating conf file -- Suspicious error -- ");
    ErrNoToString(errno, cfgFileName);
    }
  else
    CfgFileWrFrm();
  return;
  }
void    CfgEnv::CfgFileWrFrm          ( void        ) {
  if(cfgFileLineCount > 0) {
    for(uint i=0; i<cfgFileLineCount; i++) {
      free(cfgFileLines[i]);
      }
    }
  cfgFileLineCount = 0;
  cfgFileLines[cfgFileLineCount] = new char[MAX_LINE_LEN];
  strcpy(cfgFileLines[cfgFileLineCount++], "<basalt_config>");
  cfgFileLines[cfgFileLineCount] = new char[MAX_LINE_LEN];
  strcpy(cfgFileLines[cfgFileLineCount++], "</basalt_config>");
  cfgFileLines[cfgFileLineCount] = new char[MAX_LINE_LEN];
  strcpy(cfgFileLines[cfgFileLineCount++], "");
  rewind(cfgFile);
  cfgFileDirty = true;
  CfgFileWr();
  return;
  }
void    CfgEnv::CfgFileRd             ( void        ) {
  char *ts;
  char *bs;

  ts = (char *)malloc(MAX_LINE_LEN*sizeof(char));
  bs = fgets(ts, MAX_LINE_LEN, cfgFile);
  if(bs == NULL) {
    fprintf(stdout, "Empty conf file.\n");
    CfgFileWrFrm();
    }
  else {
    while((bs != NULL) && (feof(cfgFile) == 0)) {
      StripNPTrail(bs);
      if(*bs != '\0') {
        cfgFileLines[cfgFileLineCount++] = bs;
        ts = (char *)malloc(MAX_LINE_LEN*sizeof(char));
        }
      bs = fgets(ts, MAX_LINE_LEN, cfgFile);
      }
    }
  return;
  }
void    CfgEnv::CfgPrint              ( void        ) {
  for(uint i=0; i<cfgFileLineCount; i++) {
    fprintf(stdout, "%s\n", cfgFileLines[i]);
    }
  return;
  }
void    CfgEnv::CfgFileWr             ( void        ) {
  if(cfgFileDirty && (cfgFile != NULL)) {
    fclose(cfgFile);
    cfgFile = fopen(cfgFileName, "wt");
    for(uint i=0; i<cfgFileLineCount; i++) {
      fprintf(cfgFile, "%s\n", cfgFileLines[i]);
      }
    }
  fclose(cfgFile);
  cfgFile = fopen(cfgFileName, "rt");
  cfgFileDirty = false;
  return;
  }
