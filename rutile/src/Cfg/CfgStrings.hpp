
// $Id: CfgStrings.hpp 572 2021-06-21 00:42:24Z duncang $

//=================================================================================================
// Original File Name : CfgStrings.h
// Original Author    : duncang
// Creation Date      : Nov 10, 2010
// Copyright          : Copyright © 2010 - 2017 by Catraeus and Duncan Gray
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
             CfgStrings(const char *theLang);
    virtual ~CfgStrings();
  public:
    static CfgStrings *GetInstance(void);
    static CfgStrings *GetInstance(const char *theLang);
    char **s;
    char **English;
    char **French;
    char **Blank;
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

    static CfgStrings *cs;
  };
/* \endcond */
#endif // __CFG_STRINGS_HPP_
