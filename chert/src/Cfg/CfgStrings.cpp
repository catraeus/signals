// $Id: CfgStrings.cpp 500 2019-12-15 16:47:28Z duncang $

//=================================================================================================
// Original File Name : CfgStrings.cpp
// Original Author    : duncang
// Creation Date      : Nov 10, 2010
// Copyright          : Copyright © 2010 - 2011 by Catraeus and Duncan Gray
//
// Description        :
//
//=================================================================================================

#include "CfgStrings.hpp"
#include "CfgVersion.hpp"

CfgStrings *CfgStrings::cs = NULL;

CfgStrings::CfgStrings(const char *theLang, int buildNo) {
	char verNbuild[32768];


  sprintf(verNbuild, "version %d.%d -- build %d", VER_MAIN, VER_POINT, buildNo);

	English = new char*[NUM_ENTRIES];
	French  = new char*[NUM_ENTRIES];
	Blank   = new char*[NUM_ENTRIES];

	en_PROG_NAME               = new char[MAX_STRLEN];
	en_MAIN_TITLE              = new char[MAX_STRLEN];
	en_CARD_CONFIG_TITLE       = new char[MAX_STRLEN];
	en_CARD_CONFIG_ST_CHG_CARD = new char[MAX_STRLEN];
	en_ABOUT_TITLE             = new char[MAX_STRLEN];
	en_ABOUT_PROG              = new char[MAX_STRLEN];
	en_ABOUT_COMPANY           = new char[MAX_STRLEN];
	en_ABOUT_COPYRIGHT         = new char[MAX_STRLEN];
	en_ABOUT_VERSION           = new char[MAX_STRLEN];
	en_ANY_FREQUENCY           = new char[MAX_STRLEN];
	en_ANY_LEVEL               = new char[MAX_STRLEN];

	strcpy(en_PROG_NAME                , "chert");
	strcpy(en_MAIN_TITLE               , "chert Audio Analyzer");
	strcpy(en_CARD_CONFIG_TITLE        , "chert - Configure Sound Card");
	strcpy(en_CARD_CONFIG_ST_CHG_CARD  , "Card changed:  ");
	strcpy(en_ABOUT_TITLE              , "About chert");
	strcpy(en_ABOUT_PROG               , "chert Audio Analyzer");
	strcpy(en_ABOUT_COMPANY            , "Catraeus");
	strcpy(en_ABOUT_COPYRIGHT          , "Copyright © 2010 - 2012; Catraeus and Duncan Gray");
	strcpy(en_ABOUT_VERSION            ,  verNbuild);
	strcpy(en_ANY_FREQUENCY            , "Frequency");
	strcpy(en_ANY_LEVEL                , "Level");

	fr_PROG_NAME               = new char[MAX_STRLEN];
	fr_MAIN_TITLE              = new char[MAX_STRLEN];
	fr_CARD_CONFIG_TITLE       = new char[MAX_STRLEN];
	fr_CARD_CONFIG_ST_CHG_CARD = new char[MAX_STRLEN];
	fr_ABOUT_TITLE             = new char[MAX_STRLEN];
	fr_ABOUT_PROG              = new char[MAX_STRLEN];
	fr_ABOUT_COMPANY           = new char[MAX_STRLEN];
	fr_ABOUT_COPYRIGHT         = new char[MAX_STRLEN];
	fr_ABOUT_VERSION           = new char[MAX_STRLEN];
	fr_ANY_FREQUENCY           = new char[MAX_STRLEN];
	fr_ANY_LEVEL               = new char[MAX_STRLEN];

	strcpy(fr_PROG_NAME               , "chert");
	strcpy(fr_MAIN_TITLE              , "chert Analyseur de l'Audio");
	strcpy(fr_CARD_CONFIG_TITLE       , "chert - Configurer Carte Son");
	strcpy(fr_CARD_CONFIG_ST_CHG_CARD , "Carte changé:  ");
	strcpy(fr_ABOUT_TITLE             , "À chert");
	strcpy(fr_ABOUT_PROG              , "chert Analyseur de l'Audio");
	strcpy(fr_ABOUT_COMPANY           , "Catraeus");
	strcpy(fr_ABOUT_COPYRIGHT         , "Copyright © 2010 - 2012; Catraeus et Duncan Gray");
	strcpy(fr_ABOUT_VERSION           ,  verNbuild);
	strcpy(fr_ANY_FREQUENCY           , "Fréquence");
	strcpy(fr_ANY_LEVEL               , "Niveau");

	zz_PROG_NAME               = new char[MAX_STRLEN];
	zz_MAIN_TITLE              = new char[MAX_STRLEN];
	zz_CARD_CONFIG_TITLE       = new char[MAX_STRLEN];
	zz_CARD_CONFIG_ST_CHG_CARD = new char[MAX_STRLEN];
	zz_ABOUT_TITLE             = new char[MAX_STRLEN];
	zz_ABOUT_PROG              = new char[MAX_STRLEN];
	zz_ABOUT_COMPANY           = new char[MAX_STRLEN];
	zz_ABOUT_COPYRIGHT         = new char[MAX_STRLEN];
	zz_ABOUT_VERSION           = new char[MAX_STRLEN];
	zz_ANY_FREQUENCY           = new char[MAX_STRLEN];
	zz_ANY_LEVEL               = new char[MAX_STRLEN];

	strcpy(zz_PROG_NAME               , "chert");
	strcpy(zz_MAIN_TITLE              , "chert Audio Analyzer");
	strcpy(zz_CARD_CONFIG_TITLE       , "chert - Configure Sound Card");
	strcpy(zz_CARD_CONFIG_ST_CHG_CARD , "Card changed:  ");
	strcpy(zz_ABOUT_TITLE             , "About chert");
	strcpy(zz_ABOUT_PROG              , "chert Audio Analyzer");
	strcpy(zz_ABOUT_COMPANY           , "Catraeus");
	strcpy(zz_ABOUT_COPYRIGHT         , "Copyright © 2010 - 2011; Catraeus and Duncan Gray");
	strcpy(zz_ABOUT_VERSION           ,  verNbuild);
	strcpy(zz_ANY_FREQUENCY           , "Frequency");
	strcpy(zz_ANY_LEVEL               , "Level");

  English  [PROG_NAME]               = en_PROG_NAME;
  English  [MAIN_TITLE]              = en_MAIN_TITLE;
  English  [CARD_CONFIG_TITLE]       = en_CARD_CONFIG_TITLE;
  English  [CARD_CONFIG_ST_CHG_CARD] = en_CARD_CONFIG_ST_CHG_CARD;
  English  [ABOUT_TITLE]             = en_ABOUT_TITLE;
  English  [ABOUT_PROG]              = en_ABOUT_PROG;
  English  [ABOUT_COMPANY]           = en_ABOUT_COMPANY;
  English  [ABOUT_COPYRIGHT]         = en_ABOUT_COPYRIGHT;
  English  [ABOUT_VERSION]           = en_ABOUT_VERSION;
  English  [ANY_FREQUENCY]           = en_ANY_FREQUENCY;
  English  [ANY_LEVEL]               = en_ANY_LEVEL;

  French   [PROG_NAME]               = fr_PROG_NAME;
  French   [MAIN_TITLE]              = fr_MAIN_TITLE;
  French   [CARD_CONFIG_TITLE]       = fr_CARD_CONFIG_TITLE;
  French   [CARD_CONFIG_ST_CHG_CARD] = fr_CARD_CONFIG_ST_CHG_CARD;
  French   [ABOUT_TITLE]             = fr_ABOUT_TITLE;
  French   [ABOUT_PROG]              = fr_ABOUT_PROG;
  French   [ABOUT_COMPANY]           = fr_ABOUT_COMPANY;
  French   [ABOUT_COPYRIGHT]         = fr_ABOUT_COPYRIGHT;
  French   [ABOUT_VERSION]           = fr_ABOUT_VERSION;
  French   [ANY_FREQUENCY]           = fr_ANY_FREQUENCY;
  French   [ANY_LEVEL]               = fr_ANY_LEVEL;

  Blank    [PROG_NAME]               = zz_PROG_NAME;
  Blank    [MAIN_TITLE]              = zz_MAIN_TITLE;
  Blank    [CARD_CONFIG_TITLE]       = zz_CARD_CONFIG_TITLE;
  Blank    [CARD_CONFIG_ST_CHG_CARD] = zz_CARD_CONFIG_ST_CHG_CARD;
  Blank    [ABOUT_TITLE]             = zz_ABOUT_TITLE;
  Blank    [ABOUT_PROG]              = zz_ABOUT_PROG;
  Blank    [ABOUT_COMPANY]           = zz_ABOUT_COMPANY;
  Blank    [ABOUT_COPYRIGHT]         = zz_ABOUT_COPYRIGHT;
  Blank    [ABOUT_VERSION]           = zz_ABOUT_VERSION;
  Blank    [ANY_FREQUENCY]           = zz_ANY_FREQUENCY;
  Blank    [ANY_LEVEL]               = zz_ANY_LEVEL;

	     if (strcmp(theLang, "English") == 0)
		s = English;
	else if (strcmp(theLang, "French" ) == 0)
		s = French;
	else
		s = Blank;






}

CfgStrings::~CfgStrings() {
  delete en_PROG_NAME              ;
  delete en_MAIN_TITLE             ;
  delete en_CARD_CONFIG_TITLE      ;
  delete en_CARD_CONFIG_ST_CHG_CARD;
  delete en_ABOUT_TITLE            ;
  delete en_ABOUT_PROG             ;
  delete en_ABOUT_COMPANY          ;
  delete en_ABOUT_COPYRIGHT        ;
  delete en_ABOUT_VERSION          ;
  delete en_ANY_FREQUENCY          ;
  delete en_ANY_LEVEL              ;

  delete fr_PROG_NAME              ;
  delete fr_MAIN_TITLE             ;
  delete fr_CARD_CONFIG_TITLE      ;
  delete fr_CARD_CONFIG_ST_CHG_CARD;
  delete fr_ABOUT_TITLE            ;
  delete fr_ABOUT_PROG             ;
  delete fr_ABOUT_COMPANY          ;
  delete fr_ABOUT_COPYRIGHT        ;
  delete fr_ABOUT_VERSION          ;
  delete fr_ANY_FREQUENCY          ;
  delete fr_ANY_LEVEL              ;

  delete zz_PROG_NAME              ;
  delete zz_MAIN_TITLE             ;
  delete zz_CARD_CONFIG_TITLE      ;
  delete zz_CARD_CONFIG_ST_CHG_CARD;
  delete zz_ABOUT_TITLE            ;
  delete zz_ABOUT_PROG             ;
  delete zz_ABOUT_COMPANY          ;
  delete zz_ABOUT_COPYRIGHT        ;
  delete zz_ABOUT_VERSION          ;
  delete zz_ANY_FREQUENCY          ;
  delete zz_ANY_LEVEL              ;

  delete English                   ;
  delete French                    ;
  delete Blank                     ;

}

CfgStrings *CfgStrings::GetInstance(const char *theLang, int buildNo) {
  if(cs == NULL )
    cs = new CfgStrings(theLang, buildNo);
  return cs;
}
CfgStrings *CfgStrings::GetInstance() {
  if(cs == NULL )
    cs = new CfgStrings("English", 0);
  return cs;
}
