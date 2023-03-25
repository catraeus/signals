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
          CtlSaHor::~CtlSaHor       ( void ) {
}
CtlSaHor *CtlSaHor::GetInstance     ( Signal *i_sig ) {
  if(ctSaHor == NULL)
    ctSaHor = new CtlSaHor(i_sig);
  return ctSaHor;
}

void      CtlSaHor::BuildEnv        ( Signal *i_sig ) {
  mdSa           = MdlSa       ::GetInstance();
  ctMd           = CtlMsgDspch ::GetInstance();
  ctRsmp         = CtlRsmp     ::GetInstance(i_sig);

  MRU_SaHorReBase = new CbT<CtlSaHor>();
  MRU_SaHorReBase->SetCallback(this, &CtlSaHor::SaHorReBase);
  ctMd->MSU_SaHorReBase = MRU_SaHorReBase;
  return;
}
void      CtlSaHor::SetScrSize      ( uint   i_w, uint i_h) {
  mdSa->SetPxlVscrY(i_h);
  mdSa->SetPxlVscrX(i_w);
  ctRsmp->ReScale();
  return;
  }
void      CtlSaHor::SetLog          ( void ) {
  mdSa->SetLogX(true );
  ctMd->MRD_SaHorNumerics();
  return;
}
void      CtlSaHor::SetLin          ( void ) {
  mdSa->SetLogX(false);
  ctMd->MRD_SaHorNumerics();
  return;
}

void      CtlSaHor::SetModeAvg      ( void ) {
  mdSa->SetAvg(true);
  if(!lastAvg) {
    fprintf(stdout, "ToAvg\n"); fflush(stdout);
    ctRsmp->CalcSpecAvg();
  }
  lastAvg = true;
  ctMd->MRD_SaHorNumerics();
  return;
}
void      CtlSaHor::SetModeTrack    ( void ) {
  mdSa->SetAvg(false);
  if(lastAvg) {
    fprintf(stdout, "ToTrack\n"); fflush(stdout);
  }
  lastAvg = false;
  ctMd->MRD_SaHorNumerics();
  return;
}

void      CtlSaHor::SetFmin         ( double i_f ) {
  mdSa->SetFmin(i_f);
  ctMd->MRD_SaHorNumerics();
  return;
}
void      CtlSaHor::SetFmax         ( double i_f ) {
  mdSa->SetFmax(i_f);
  ctMd->MRD_SaHorNumerics();
  return;
}

void      CtlSaHor::SetNtime        ( ullong i_t ) {
  mdSa->SetSmpVana(i_t);
  ctRsmp->ReScale();
  ctMd->MRD_SaHorNumerics();
  return;
}
void      CtlSaHor::SetNfreq        ( ullong i_f ) {
  mdSa->SetFrqVana(i_f);
  ctRsmp->ReScale();
  ctMd->MRD_SaHorNumerics();
  return;
}
void      CtlSaHor::SetDelFreq      ( double i_f ) {
  //mdSa->SetDelFreq(i_f);
  ctMd->MRD_SaHorNumerics();
  return;
}

bool      CtlSaHor::SaHorReBase     (void *d) {
  ctRsmp->ReScale();
  ctMd->MRD_SaHorNumerics();
  return false;
}
