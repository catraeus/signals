
//=================================================================================================
// Original File Name : CfgEnv.cpp
// Original Author    : duncang
// Creation Date      : 2010-12-17
// Copyright          : Copyright © 2010 - 2023 by Catraeus and Duncan Gray
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

        CfgEnv::CfgEnv(int i_argc, char *i_argv[], char *i_envp[])
: argc(i_argc)
, argv(i_argv)
, envp(i_envp) {
  fatal = envp == NULL;
                if(fatal) return;
  BuildApp ();  if(fatal) return;
  BuildCfg ();
  BuildUser();  if(fatal) return;

  inFile  = 0;

  fileNameInputLine     = new char[MAX_LINE_LEN];
  workingDir            = new char[MAX_LINE_LEN];
  fileNameRel           = new char[MAX_LINE_LEN];
  fileNameAbs           = new char[MAX_LINE_LEN];


//____________________________
  strcpy(workingDir, CWD);

  PrintVersion();
}
        CfgEnv::~CfgEnv               ( void        ) {
  WriteCfgFile();
  delete cu->dirName;
  delete cu->fileName;
  delete cu->lines;
  delete appName;
  for(uint i=0; i<cu->lineCount; i++) {
    delete cu->lines[i];
    }
  if(cu->file != NULL)
    fclose(cu->file);
}
void    CfgEnv::PrintVersion(void) {
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
void  CfgEnv::BuildApp(void) {
  verMaj  = VER_MAIN;
  verMin  = VER_POINT;
  buildNo = GIT_MARK;

  CWD                   = new char[MAX_LINE_LEN];
  appId                 = new char[MAX_LINE_LEN];

  appName               = new char[sizeof(APP_NAME)+1];
  appDesc               = new char[sizeof(APP_DESC)+1];
  strCopyright          = new char[sizeof(STR_CPYR)+1];
  strAuthors            = new char[sizeof(STR_AUTH)+1];
  strUrl                = new char[sizeof(STR_URL)+1];
  strUrlLabel           = new char[sizeof(STR_URL_LBL)+1];

  strcpy(appName,       APP_NAME);
  strcpy(appId,        "com.catraeus.AAS.chert");
  strcat(appId,         APP_ID_NM);
  strcpy(appDesc,       APP_DESC);
  strcpy(strCopyright,  STR_CPYR);
  strcpy(strAuthors,    STR_AUTH);
  strcpy(strUrl,        STR_URL);
  strcpy(strUrlLabel,   STR_URL_LBL);

  char *theErr = getcwd(CWD, 4096); // IMPORTANT getcwd() assumes we made the buffer.
  if(theErr == NULL) {
    fprintf(stderr, "BAD CWD ... VERY STRANGE\n"); fflush(stderr);
    fatal = true;
    return;
  }
  fprintf(stderr, "Found CWD at: %s\n", CWD); fflush(stderr);


  return;
}
void  CfgEnv::BuildCfg(void) {
  cfgGlbl = new sCfgSpec; // TODO Nothing here for now
  cu = new sCfgSpec;


  cu->dirName      = new char[MAX_LINE_LEN];
 *cu->dirName      = '\0';
  cu->fileName     = new char[MAX_LINE_LEN];
 *cu->fileName     = '\0';
  cu->file         = NULL;
  cu->lines        = new char*[MAX_CFG_LINES];
  for(llong i=0; i<MAX_CFG_LINES; i++)
    cu->lines[i] = NULL;
  cu->lineCount    = 0;
  cu->dirty        = false;

  return;
}
void  CfgEnv::BuildUser(void) {
  char tStr[1024];
  int  accessResult;

//==========================================================================
// What is the home like
  for(int i=0; (envp[i] != NULL) && (*cu->dirName == '\0'); i++) {
    if(strncmp((const char*)(envp[i]), "HOME", (size_t)4) == 0) {
      char *p = &((envp[i])[5]); // MAGICK assumes that the envp format for this line is "HOME=..."  been stable since '68
      strcpy(cu->dirName, p);
      fprintf(stderr, "Found Root User Directory at %s\n", p);fflush(stderr);
    }
  }
  if(cu->dirName[0] == '\0') {
    fprintf(stderr, "FATAL -- No Home Directory Found In Environment.\n");fflush(stderr);
    fatal = true;
    return;
  }
//==========================================================================
// Use the default Linux home pattern for coniguration thingies
  strcat(cu->dirName, "/.config/");
  strcat(cu->dirName, appName);
//==== If there is a directory cool, else create one
  accessResult = access((const char*)cu->dirName, (int)F_OK);
  if(accessResult != 0) {
    fprintf(stderr, "Creating a new chert conig directory in ~/.config/.\n");fflush(stderr);
    accessResult = mkdir(cu->dirName, (mode_t)0755); // IMPORTANT this is octal. AND directories are 755
  }
  if(accessResult != 0) {
    fprintf(stderr, "FATAL -- unable to make config directory %s.\n", cu->dirName);fflush(stderr);
    fatal = true;
    return;
  }
//==== So, now the actual config file.
  sprintf(cu->fileName, "%s/config", cu->dirName);
  accessResult = access((const char*)cu->fileName, (int)F_OK);
  if(accessResult != 0) {
    if((errno) == ENOENT) {
      cu->file = fopen(cu->fileName, "w");
      fprintf(cu->file, "Hello File World!\n");fflush(cu->file);
      fclose(cu->file);
    }
    else {
      fatal = true;
      ErrNoToString(errno, tStr);
      fprintf(stderr, "FATAL Unable to access existing config file: %s with error %s\n", cu->fileName, tStr);fflush(stderr);
      return;
    }
  }


  cu->file = fopen(cu->fileName, "r+"); // IMPORTANT Leave it open for the duration of operation to prevent file intrusion.

  if(cu->file == NULL) {
    fatal = true;
    ErrNoToString(errno, tStr);
    fprintf(stderr, "FATAL Unable to access existing config file: %s with error %s\n", cu->fileName, tStr);fflush(stderr);
    return;
    }
  ReadCfgFile();
  return;
}

//=================================================================================================
void  CfgEnv::SetLineText      ( llong i_n, char   *i_s ) {
  if(i_n > cu->lineCount) return;
  if(cu->lines[i_n] != NULL) delete cu->lines[i_n];
  cu->lines[i_n] = new char[strlen(i_s)+1];
  strcpy(cu->lines[i_n], i_s);
  cu->dirty = true;
  WriteCfgFile();
  return;
}
char *CfgEnv::GetLineText      ( llong i_n   ) {
  return cu->lines[i_n];
}



void  CfgEnv::ReadCfgFile(void) {
  char *ts1;
  char *ts2;
  char *bs;

  ts1 = new char[MAX_LINE_LEN];
  ts2 = new char[MAX_LINE_LEN];
  rewind(cu->file);
  bs = fgets(ts1, MAX_LINE_LEN, cu->file);
  if(bs == NULL) {
    ErrNoToString(errno, ts1);
    strcpy(ts2, ts1);
    sprintf(ts1, "%s   Reading cfg file lines.", ts2);
    }
  else {
    while((bs != NULL) && (feof(cu->file) == 0)) {
      StripNPTrail(bs);
      if(*bs != '\0') {
        cu->lines[cu->lineCount++] = bs;
        ts1 = new char[MAX_LINE_LEN];
        }
      bs = fgets(ts1, MAX_LINE_LEN, cu->file);
      }
    }
  fprintf(stdout, "Config File Open Succeeded.\n\n");
  cu->dirty = false;
  return;
  }
void  CfgEnv::PrintCfgLines(void) {
  for(uint i=0; i<cu->lineCount; i++) {
    fprintf(stdout, "%s\n", cu->lines[i]);
    }
  return;
  }
void  CfgEnv::WriteCfgFile(void) {
  if(cu->dirty && (cu->file != NULL)) {
    rewind(cu->file);
    for(uint i=0; i<cu->lineCount; i++) {
      fprintf(cu->file, "%s\n", cu->lines[i]);
      }
    }
  fprintf(cu->file, "\n");
  cu->dirty = false;
  return;
  }
