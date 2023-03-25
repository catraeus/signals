
// $Id: CfgStrings.hpp 506 2019-12-25 15:35:12Z duncang $

//=================================================================================================
// Original File Name : af_Strings.h
// Original Author    : duncang
// Creation Date      : Nov 10, 2010
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//
//=================================================================================================

#ifndef __CFG_STRINGS_HPP_
#define __CFG_STRINGS_HPP_
#include "CfgEnv.hpp"
#include <string.h>

/* \cond HIDDEN_SYMBOLS */
class CfgStrings {
  public:
  private:
                       CfgStrings(const char *theLang, int buildNo);
    virtual           ~CfgStrings();
  public:
    static CfgStrings *GetInstance(void);
    static CfgStrings *GetInstance(const char *theLang, int buildNo);
    char **s;
    char *strsAppExit;
    char *strsFileOpen;
    char *strsFileSaveNone;
    char *strsFileCloseNone;
  private:
    char **English;
    char **French;
    char **Blank;
  public:
    enum eStr{
      PROG_NAME,
      MAIN_TITLE,
      CARD_CONFIG_TITLE,
      CARD_CONFIG_ST_CHG_CARD,
      ABOUT_TITLE,
      ABOUT_PROG,
      ABOUT_COMPANY,
      ABOUT_COPYRIGHT,
      ABOUT_VERSION,
      ANY_FREQUENCY,
      ANY_LEVEL,
      AUDIO_IO,
      NUM_ENTRIES
      };
  private:
    enum eConst{
    	MAX_STRLEN = 256
    };
  private:
    char *en_PROG_NAME;
    char *en_MAIN_TITLE;
    char *en_CARD_CONFIG_TITLE;
    char *en_CARD_CONFIG_ST_CHG_CARD;
    char *en_ABOUT_TITLE;
    char *en_ABOUT_PROG;
    char *en_ABOUT_COMPANY;
    char *en_ABOUT_COPYRIGHT;
    char *en_ABOUT_VERSION;
    char *en_ANY_FREQUENCY;
    char *en_ANY_LEVEL;
    char *en_AUDIO_IO;

    char *fr_PROG_NAME;
    char *fr_MAIN_TITLE;
    char *fr_CARD_CONFIG_TITLE;
    char *fr_CARD_CONFIG_ST_CHG_CARD;
    char *fr_ABOUT_TITLE;
    char *fr_ABOUT_PROG;
    char *fr_ABOUT_COMPANY;
    char *fr_ABOUT_COPYRIGHT;
    char *fr_ABOUT_VERSION;
    char *fr_ANY_FREQUENCY;
    char *fr_ANY_LEVEL;
    char *fr_AUDIO_IO;

    char *zz_PROG_NAME;
    char *zz_MAIN_TITLE;
    char *zz_CARD_CONFIG_TITLE;
    char *zz_CARD_CONFIG_ST_CHG_CARD;
    char *zz_ABOUT_TITLE;
    char *zz_ABOUT_PROG;
    char *zz_ABOUT_COMPANY;
    char *zz_ABOUT_COPYRIGHT;
    char *zz_ABOUT_VERSION;
    char *zz_ANY_FREQUENCY;
    char *zz_ANY_LEVEL;
    char *zz_AUDIO_IO;

    static CfgStrings *cs;
  };
/* \endcond HIDDEN_SYMBOLS */
#endif // __CFG_STRINGS_HPP_

