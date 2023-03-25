
//=================================================================================================
// Original File Name : Env.h
// Original Author    : duncang
// Creation Date      : May 31, 2012
// Copyright          : Copyright © 2012 - 2023 by Catraeus and Duncan Gray
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
  public:
  private:
                         CfgEnv           ( int i_argc, char *i_argv[], char *i_envp[] );
    virtual             ~CfgEnv           ( void        );
  public:
    static CfgEnv       *GetInstance      ( void        );
    static CfgEnv       *GetInstance      ( int i_argc, char *i_argv[], char *i_envp[] );
           void          ShowVersion      ( void        );
           void          SetupFile        ( void        );

           void          SetFileNameRd    ( char   *i_s );
           void          SetDirWorkRd     ( char   *i_s );
           char         *GetDirWorkRd     ( void        ) {return dirWorkRd;};

           void          SetFileNameWr    ( char   *i_s );
           void          SetDirWorkWr     ( char   *i_s );
           char         *GetDirWorkWr     ( void        ) {return dirWorkWr;};

           char         *GetFileNameAbs   ( void        ) {return fileNameAbsRd;};
  protected:
  private:
           void          CfgEnvInit       ( void        );
           void          CfgReBase        ( void        );
           void          CfgPrint         ( void        );
           void          CfgDirCheck      ( void        );
           void          CfgDirNew        ( void        );
           void          CfgFileCheck     ( void        );
           void          CfgFileOpen      ( void        );
           void          CfgFileNew       ( void        );
           void          CfgFileWrFrm     ( void        );
           void          CfgFileRd        ( void        );
           void          CfgFileWr        ( void        );
           void          SplitAbsPath     ( void        );
  public:
    int        verMaj;
    int        verMin;
    int        buildNo;
    char      *appName;
    char      *appId;
    char      *appDesc;
    char      *strCopyright;
    char      *strAuthors;
    char      *strUrl;
    char      *strUrlLabel;

  private:
    int        argc;
    char     **argv;
    char     **envp;
    char      *sFileNm;

    char      *CWD;

    FILE      *fileWr;
    char      *dirWorkWr;
    char      *fileNameRelWr;
    char      *fileNameAbsWr;

    FILE      *fileRd;
    char      *dirWorkRd;
    char      *fileNameRelRd;
    char      *fileNameAbsRd;

    char      *cfgFileName;
    FILE      *cfgFile;
    char      *cfgDirName;
    char     **cfgFileLines;
    uint       cfgFileLineCount;
    bool       cfgFileDirty;
    sWinSpec  *wsMain;




    static CfgEnv *ce;
  };
/* \endcond HIDDEN_SYMBOLS */
#endif // __CFG_ENV_H_

