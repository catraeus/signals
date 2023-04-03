

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
           void          PrintVersion     ( void        );
           void          SetFileName      ( char   *i_s );
           void          SetWorkingDir    ( char   *i_s );
           char         *GetWorkingDir    ( void        ) {return workingDir  ;};
           char         *GetFileNameAbs   ( void        ) {return fileNameAbs ;};
           void          CloseFileUser    ( void        ) {fclose(cu->file); return;};

           llong         GetLineCountUser ( void        ) {return cu->lineCount;};
           void          SetLineText      ( llong i_n, char   *i_s );
           char         *GetLineText      ( llong i_n   );

           bool          GetFatal         ( void        ) {return fatal       ;};
  protected:
  private:
           void          BuildApp         ( void        );
           void          BuildCfg         ( void        );
           void          BuildUser        ( void        );

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
    int       argc;
    char    **argv;
    char    **envp;
    bool      fatal;

    char     *fileNameInputLine;

    char     *CWD;
    FILE     *inFile;
    char     *workingDir;
    char     *fileNameRel;
    char     *fileNameAbs;

    char     *cfgRootGlbl;
    char     *cfgRootUser;

    sCfgSpec *cfgGlbl;
    sCfgSpec *cu;


    sWinSpec *wsFile;
    sWinSpec *wsXport;
    sWinSpec *wsOs;
    sWinSpec *wsSa;

    static CfgEnv *ce;
  };
/* \endcond */
#endif // __CFG_ENV_H_

