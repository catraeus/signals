
/* $Id: CfgEnv.hpp 572 2021-06-21 00:42:24Z duncang $ */

//=================================================================================================
// Original File Name : CfgEnv.h
// Original Author    : duncang
// Creation Date      : 2013-08-15
// Copyright          : Copyright © 2013 - 2017 by Catraeus and Duncan Gray
//
// Description        :
//
//=================================================================================================

#ifndef __CFG_ENV_HPP_
#define __CFG_ENV_HPP_

#include <stdio.h>
#include <gdkmm.h>
#include <caes/CaesTypes.hpp>
/* \cond HIDDEN_SYMBOLS */
class CfgEnv {
  private:

  public:
  private:
                         CfgEnv           ( int argc, char *argv[], char *envp[]);
    virtual             ~CfgEnv           ( void        );
  public:
    static CfgEnv       *GetInstance      ( void        );
    static CfgEnv       *GetInstance      ( int i_argc, char *i_argv[], char *i_envp[]);
           void          ShowVersion      ( void        );
           void          SetupFile        ( void        );
           void          SetFileName      ( char   *i_s );
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

    char  *cfgFileName;
    FILE  *cfgFile;
    char  *cfgDirName;
    char **cfgFileLines;
    uint   cfgFileLineCount;
    bool   cfgFileDirty;





    static CfgEnv *ce;
  };
/* \endcond */

#endif  // __CFG_ENV_HPP_


