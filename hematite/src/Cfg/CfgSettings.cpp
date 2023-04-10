
//=================================================================================================
// Original File Name : CfgSettings.cpp
// Original Author    : duncang
// Creation Date      : 2023-04-02
// Copyright          : Copyright © 2023 by Catraeus and Duncan Gray
//
// Description        :
/*    Parameters that the program uses for factors ranging from critical behavior to
         merely handy conveniences for the user.
*/
//
//=================================================================================================

#include "CfgSettings.hpp"

CfgSettings *CfgSettings::ct = NULL;
const char *CfgSettings::parmNames[] = {
  "DIR_NAME_IN",
  "DIR_NAME_OUT"
};

                CfgSettings::CfgSettings() {
  Build();
  return;
}
                CfgSettings::~CfgSettings() {
  delete(dirNameIn);
  delete(dirNameOut);
}
CfgSettings    *CfgSettings::GetInstance(void) {
  if(ct == NULL)
    ct = new CfgSettings();
  return ct;
}
void            CfgSettings::Build(void) {
  sParms *tParm;
  char   *pStr;

  pStr = NULL;

  ce           = CfgEnv::GetInstance();
  dirNameIn    = new char[MAX_PATH_LEN];
  dirNameOut   = new char[MAX_PATH_LEN];

  strcpy(dirNameIn, ce->GetLineText(0));
  if((llong)dirNameIn != 0) return;

  tParm = new sParms;
  tParm->parmValue = dirNameIn;
  tParm->scope = eScope::CTES_USER;
  parmMap[(char *)parmNames[0]] = tParm;

  for(llong i=0; i < ce->GetLineCountUser(); i++) {
    strcpy(pStr, ce->GetLineText(i));
    if(strncmp(pStr, parmNames[0], strlen(parmNames[0])) == 0) {
      strcpy(parmMap[(char *)parmNames[0]]->parmValue, &pStr[strlen(parmNames[0] + 2)]);
    }
  }

  return;
}

void            CfgSettings::SetDirNameIn    ( const char *i_str       ) {
  strcpy(dirNameIn, i_str);
  ce->SetLineText(0, dirNameIn); // HACK
  return;
}
