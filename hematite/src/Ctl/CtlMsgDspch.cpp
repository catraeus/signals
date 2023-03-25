
// $Id: CtlMsgDspch.cpp 756 2023-03-25 00:45:33Z duncang $

//=================================================================================================
// Original File Name : CtlMsgDspch.cpp
// Original Author    : duncang
// Creation Date      : 2017-02-06T01:32:18,581092635+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//=================================================================================================


#include "CtlMsgDspch.hpp"
#include <stdlib.h>

CtlMsgDspch *CtlMsgDspch::ctMd = NULL;


             CtlMsgDspch::CtlMsgDspch             ( void            ) {
  HCB_AnBulkVoid           = NULL;
  HCB_AnSineVoid           = NULL;
  HCB_AnSineHasData        = NULL;

  HCB_MainReTitle          = NULL;
  HCB_MainStWork           = NULL;
  HCB_MainStCmpl           = NULL;

  HCB_SigWrChg             = NULL;
  HCB_WaveWrChg            = NULL;
  return;
}
             CtlMsgDspch::~CtlMsgDspch            ( void            ) {
}
CtlMsgDspch* CtlMsgDspch::GetInstance             ( void            ) {
  if(ctMd == NULL) ctMd = new CtlMsgDspch();
  return ctMd;
}

void         CtlMsgDspch::Emit_SigWrChg           ( void            ) {
  if(HCB_SigWrChg  != NULL) HCB_SigWrChg ->Execute(NULL);
  return;
}
void         CtlMsgDspch::Emit_WaveWrChg          ( void            ) {
  if(HCB_WaveWrChg != NULL) HCB_WaveWrChg->Execute(NULL);
  return;
}

void         CtlMsgDspch::Emit_FileRdChg          ( void            ) {
  if(HCB_AnBulkVoid    != NULL) HCB_AnBulkVoid    ->Execute(NULL);
  if(HCB_AnSineVoid    != NULL) HCB_AnSineVoid    ->Execute(NULL);
  if(HCB_MainReTitle   != NULL) HCB_MainReTitle   ->Execute(NULL);
  return;
}
void         CtlMsgDspch::Emit_SineHasData        ( void            ) {
  if(HCB_AnSineHasData != NULL) HCB_AnSineHasData ->Execute(NULL);
  return;
}
void         CtlMsgDspch::Emit_SigStatCmpl        ( double *i_tDbl  ) {
  if(HCB_MainStCmpl   != NULL) HCB_MainStCmpl  ->Execute(i_tDbl);
  return;
}
void         CtlMsgDspch::Emit_SigStatWork        ( char   *i_tStr  ) {
  if(HCB_MainStWork  != NULL) HCB_MainStWork   ->Execute(i_tStr);
  return;
}

