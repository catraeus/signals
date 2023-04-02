
/* $Id: CfgEnv.hpp 634 2022-11-19 22:52:03Z duncang $ */

//=================================================================================================
// Original File Name : CfgEnv.h
// Original Author    : duncang
// Creation Date      : 2010-12-17
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//
//=================================================================================================

#ifndef __CFG_ENV_H_
#define __CFG_ENV_H_

#include <stdio.h>
#include <gdkmm.h>

#include <caes/CaesTypes.hpp>

class CfgEnv {
  private:
    struct sWinSpec {
      llong        posX;
      llong        posY;
      llong        sizeX;
      llong        sizeY;
      bool         shown;
      Gdk::Window *me;
    };
    struct sCfgSpec {
      char  *fileName;
      FILE  *file;
      char  *dirName;
      char **lines;
      uint   lineCount;
      bool   dirty;
    };
  public:
  private:
                         CfgEnv           ( int i_argc, char *i_argv[], char *i_envp[] );
    virtual             ~CfgEnv           ( void        );
  public:
    static CfgEnv       *GetInstance      ( void        );
    static CfgEnv       *GetInstance      ( int i_argc, char *i_argv[], char *i_envp[] );
           void          ShowVersion      ( void        );
           void          SetupFile        ( void        );
           void          SetFileName      ( char   *i_s );
           void          SetWorkingDir    ( char   *i_s );
           char         *GetWorkingDir    ( void        ) {return workingDir;};
           char         *GetFileNameAbs   ( void        ) {return fileNameAbs;};
  protected:
  private:
           void          OpenCfgEnv       ( void        );
           void          CheckForCfgDir   ( void        );
           void          NewCfgDir        ( void        );
           void          CheckForCfgFile  ( void        );
           void          OpenCfgFile      ( void        );
           void          NewCfgFile       ( void        );
           void          SetupNoFile      ( void        );
           void          ReadCfgFile      ( void        );
           void          PrintCfgLines    ( void        );
           void          WriteCfgFile     ( void        );
           void          CleanupFileName  ( char   *i_s );
           void          SplitAbsPath     ( void        );
  public:
    int    verMaj;
    int    verMin;
    int    buildNo;
    char  *appName;
    char  *appId;
    char  *appDesc;
    char  *strCopyright;
    char  *strAuthors;
    char  *strUrl;
    char  *strUrlLabel;

  private:
    int    argc;
    char **argv;
    char **envp;
    char  *fileNameInputLine;

    char  *CWD;
    FILE  *inFile;
    char  *workingDir;
    char  *fileNameRel;
    char  *fileNameAbs;

    char  *cfgRootGlbl;
    char  *cfgRootUser;

    sCfgSpec *cfgGlbl;
    sCfgSpec *cfgUser;


    sWinSpec *wsFile;
    sWinSpec *wsXport;
    sWinSpec *wsOs;
    sWinSpec *wsSa;

    static CfgEnv *ce;
  };
/* \endcond */
#endif // __CFG_ENV_H_

