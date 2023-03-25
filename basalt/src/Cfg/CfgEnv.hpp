
// $Id: CfgEnv.hpp 506 2019-12-25 15:35:12Z duncang $

//=================================================================================================
// Original File Name : Env.h
// Original Author    : duncang
// Creation Date      : May 31, 2012
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
/* \cond HIDDEN_SYMBOLS */
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
           void          WriteCfgFileFramework( void        );
           void          SetupNoCfgFile   ( void        );
           void          ReadCfgFile      ( void        );
           void          PrintCfgLines    ( void        );
           void          WriteCfgFile     ( void        );
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

    char  *cfgFileName;
    FILE  *cfgFile;
    char  *cfgDirName;
    char **cfgFileLines;
    uint   cfgFileLineCount;
    bool   cfgFileDirty;
    sWinSpec *wsMain;




    static CfgEnv *ce;
  };
/* \endcond HIDDEN_SYMBOLS */
#endif // __CFG_ENV_H_

