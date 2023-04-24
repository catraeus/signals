// $Id: CtlSaHor.cpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : CtlSaHor.cpp
// Original Author    : duncang
// Creation Date      : Oct 21, 2013
// Copyright          : Copyright © 2013 - 2017 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include <string.h>

#include <caes/CaesTypes.hpp>

#include "CtlSaHor.hpp"

CtlSaHor *CtlSaHor::ctSaHor = NULL;

          CtlSaHor::CtlSaHor        ( Signal *i_sig ) {
  BuildEnv(i_sig);
  lastAvg = false;
  mdSa->SetSmpVana(2048);
}
          CtlSaHor::~CtlSaHor       ( void          ) {
}
CtlSaHor *CtlSaHor::GetInstance     ( Signal *i_sig ) {
  if(ctSaHor == NULL)
    ctSaHor = new CtlSaHor(i_sig);
  return ctSaHor;
}

void      CtlSaHor::BuildEnv        ( Signal *i_sig ) {
  sig            =                           i_sig;
  mdSa           = MdlSa       ::GetInstance();
  ctMd           = CtlMsgDspch ::GetInstance();
  ctRsmp         = CtlRsmp     ::GetInstance(sig);

  emit_SaHorReBase = new CbT<CtlSaHor>();
  emit_SaHorReBase->SetCallback(this, &CtlSaHor::CtHn_ReBase);
  ctMd->CtHn_SaHorReBase = emit_SaHorReBase;
  return;
}
void      CtlSaHor::SetScrSize      ( uint   i_w, uint i_h) {
  mdSa->SetPxlVscrY(i_h);
  mdSa->SetFPvScr(i_w);
  ctRsmp->ReScale();
  return;
  }



void      CtlSaHor::SetLog          ( void          ) {
  mdSa->SetLogF();
  ctMd->CtEm_SaReScale();
  return;
}
void      CtlSaHor::SetLin          ( void          ) {
  mdSa->SetLinF();
  ctMd->CtEm_SaReScale();
  return;
}


/*
   Anchor can be start, center, stop  ... really, center is at an anchor point at a percentage of a screen
   All this stuff needs grid binning coordinated with drawing the grid in the SaDraw
   GridSpacing
*/
void      CtlSaHor::SetFmin         ( double i_f ) {
  mdSa->SetFmin(i_f);
  ctMd->CtEm_SaReScale();
  return;
}
void      CtlSaHor::SetFCen         ( double i_f ) {
  mdSa->SetFCen(i_f);
  ctMd->CtEm_SaReScale();
  return;
}
void      CtlSaHor::SetFmax         ( double i_f ) {
  mdSa->SetFmax(i_f);
  ctMd->CtEm_SaReScale();
  return;
}
void      CtlSaHor::SetFspan        ( double i_f ) {
  return;
}
void      CtlSaHor::SetNtime        ( ullong i_t ) {
  mdSa->SetSmpVana(i_t);
  ctRsmp->ReScale();
  ctMd->CtEm_SaReScale();
  return;
}
void      CtlSaHor::SetNfreq        ( ullong i_f ) {
  mdSa->SetFrqVana(i_f);
  ctRsmp->ReScale();
  ctMd->CtEm_SaReScale();
  return;
}
void      CtlSaHor::SetDelFreq      ( double i_f ) {
  //mdSa->SetDelFreq(i_f);
  ctMd->CtEm_SaReScale();
  return;
}

bool      CtlSaHor::CtHn_ReBase     ( void *d    ) {
  ctRsmp->ReScale();
  mdSa->SetFS(sig->GetFS() * 0.5D);
  ctMd->CtEm_SaReScale();
  return false;
}
