
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

                CfgSettings::CfgSettings() {
  ce           = CfgEnv::GetInstance();
  dirNameIn    = new char[MAX_PATH_LEN];
  dirNameOut   = new char[MAX_PATH_LEN];
  strcpy(dirNameIn, ce->GetLineText(0));
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

void            CfgSettings::SetDirNameIn    ( const char *i_str       ) {
  strcpy(dirNameIn, i_str);
  ce->SetLineText(0, dirNameIn); // HACK
  return;
}
