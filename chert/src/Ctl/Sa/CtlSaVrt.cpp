// $Id: CtlSaVrt.cpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : CtlSaVrt.cpp
// Original Author    : duncang
// Creation Date      : 2017-03-18T19:32:02,771922357+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include <string.h>

#include <caes/CaesTypes.hpp>

#include "CtlSaVrt.hpp"

CtlSaVrt *CtlSaVrt::ctSaHor = NULL;

          CtlSaVrt::CtlSaVrt        ( Signal *i_sig ) {
  BuildEnv   ( i_sig );
  BuildSetup (       );
}
          CtlSaVrt::~CtlSaVrt       ( void          ) {
}
CtlSaVrt *CtlSaVrt::GetInstance     ( Signal *i_sig ) {
            if(ctSaHor == NULL)
              ctSaHor = new CtlSaVrt(i_sig);
            return ctSaHor;
          }

void      CtlSaVrt::BuildEnv        ( Signal *i_sig ) {
  mdSa           = MdlSa       ::GetInstance(       );
  ctMd           = CtlMsgDspch ::GetInstance(       );
  ctRsmp         = CtlRsmp     ::GetInstance( i_sig );

  return;
}
void      CtlSaVrt::BuildSetup      ( void        ) {
  mdSa->SetALog();
  ctMd->MRD_SaVrtNumerics();
  return;
}
void      CtlSaVrt::SetScrSize      ( uint    i_w, uint i_h) {
  mdSa->SetAPvScr(i_h);
  mdSa->SetFPvScr(i_w);
  ctRsmp->ReScale();
  return;
  }
void      CtlSaVrt::SetVmax         ( double  i_v ) {
  mdSa->SetAATop(i_v);
  ctMd->MRD_SaVrtNumerics();
  return;
}


bool      CtlSaVrt::IpcSaVrtReCalc     ( void   *i_d ) {
  ctRsmp->ReScale();
  ctMd->MRD_SaVrtNumerics();
  return false;
}
