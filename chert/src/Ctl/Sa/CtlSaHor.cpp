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
  mdSa->SetTvAna(2048);
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

  CbHn_SaHorReBase = new CbT<CtlSaHor>();
  CbHn_SaHorReBase->SetCallback(this, &CtlSaHor::HandleReBase);
  ctMd->CtHn_SaHorReBase = CbHn_SaHorReBase;
  return;
}
void      CtlSaHor::SetScrSize      ( uint   i_w, uint i_h) {
  mdSa->SetAPvScr(i_h);
  mdSa->SetFPvScr(i_w);
  ctRsmp->ReScale();
  return;
  }



void      CtlSaHor::SetLog          ( void          ) {
  mdSa->SetFLog();
  ctMd->CtEm_SaReScale();
  return;
}
void      CtlSaHor::SetLin          ( void          ) {
  mdSa->SetFLin();
  ctMd->CtEm_SaReScale();
  return;
}


void      CtlSaHor::SetFStart       ( double i_f ) {
  mdSa->SetFStart(i_f);
  ctMd->CtEm_SaReScale();
  return;
}
void      CtlSaHor::SetFCen         ( double i_f ) {
  mdSa->SetFCen(i_f);
  ctMd->CtEm_SaReScale();
  return;
}
void      CtlSaHor::SetFCenPos      ( double i_f ) {
  mdSa->SetFCenPos(i_f);
  ctMd->CtEm_SaReScale();
  return;
}
void      CtlSaHor::SetFStop        ( double i_f ) {
  mdSa->SetFStop(i_f);
  ctMd->CtEm_SaReScale();
  return;
}
void      CtlSaHor::SetFspan        ( double i_f ) {
  return;
}
void      CtlSaHor::SetNtime        ( ullong i_t ) {
  mdSa->SetTvAna(i_t);
  ctRsmp->ReScale();
  ctMd->CtEm_SaReScale();
  return;
}
void      CtlSaHor::SetNfreq        ( ullong i_f ) {
  mdSa->SetFvAna(i_f);
  ctRsmp->ReScale();
  ctMd->CtEm_SaReScale();
  return;
}
void      CtlSaHor::SetDelFreq      ( double i_f ) {
  //mdSa->SetDelFreq(i_f);
  ctMd->CtEm_SaReScale();
  return;
}

bool      CtlSaHor::HandleReBase    ( void *d    ) {
  ctRsmp->ReScale();
  mdSa->SetFS(sig->GetFS());
  ullong tTn = sig->GetN();
  if(tTn > MdlSa::EK_AN_DFT)
    mdSa->SetTvAna(MdlSa::EK_AN_DFT);
  else
    mdSa->SetTvAna(tTn);
  ctMd->CtEm_SaReScale();
  return false;
}
