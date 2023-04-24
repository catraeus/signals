// $Id: CtlOsHor.cpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : CtlOsHor.cpp
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

#include "CtlOsHor.hpp"

CtlOsHor *CtlOsHor::ctOsHor = NULL;

          CtlOsHor::CtlOsHor        (Signal *i_sig) {
  BuildEnv(i_sig);
  mdOs->SetTimVrsh(0.0);
  ctMd->MRD_OsHorNumerics();
  }
          CtlOsHor::~CtlOsHor       (void) {
}
CtlOsHor *CtlOsHor::GetInstance     (Signal *i_sig) {
            if(ctOsHor == NULL)
              ctOsHor = new CtlOsHor(i_sig);
            return ctOsHor;
          }

void      CtlOsHor::BuildEnv        (Signal *i_sig) {
  mdOs           = MdlOs       ::GetInstance( i_sig );
  mdSa           = MdlSa       ::GetInstance(       );
  ctMd           = CtlMsgDspch ::GetInstance(       );
  ctRsmp         = CtlRsmp     ::GetInstance( i_sig );
  llong *pD;
  pD = mdSa->GetpTvAna();
       mdOs->SetSmpVanaP(pD);

  MRU_OsHorReBase = new CbT<CtlOsHor>();
  MRU_OsHorReBase->SetCallback(this, &CtlOsHor::OsHorReBase);
  ctMd->MSU_OsHorReBase = MRU_OsHorReBase;
  return;
}
void      CtlOsHor::SetScrSize      (uint   i_w, uint i_h) {
  mdOs->SetHeight(i_h);
  mdOs->SetWidth(i_w);
  ctRsmp->ReScale();
  ctMd->MRD_OsHorNumerics();
  return;
  }

void      CtlOsHor::SetTimVrsh      (double i_t ) {
  mdOs->SetTimVrsh(i_t);
  ctMd->MRD_OsHorNumerics();
  return;
  }
void      CtlOsHor::SetSmpVrsh      (double i_t ) {
  mdOs->SetSmpVrsh(i_t);
  ctMd->MRD_OsHorNumerics();
  return;
  }
void      CtlOsHor::SetSrlRto       (double i_srlRto ) {

  return;
  }
void      CtlOsHor::SetPbkRto       (double i_pbkRto ) {

  return;
  }


void      CtlOsHor::SetTimVpxl      (double i_t) {
  mdOs  ->SetTimVpxl(i_t);
  ctRsmp->ReScale();
  ctMd  ->MRD_OsHorNumerics();
  return;
  }
void      CtlOsHor::SetTimVdiv      (double i_t            ) {
  mdOs->SetTimVdiv(i_t);
  ctRsmp->ReScale();
  ctMd->MRD_OsHorNumerics();
  return;
  }
void      CtlOsHor::SetTimVscr      (double i_t) {
  mdOs->SetTimVscr(i_t);
  ctRsmp->ReScale();
  ctMd->MRD_OsHorNumerics();
  return;
  }



void      CtlOsHor::SetSmpVpxl      (double i_s) {
  mdOs->SetSmpVpxl(i_s);
  ctRsmp->ReScale();
  ctMd->MRD_OsHorNumerics();
  return;
  }
void      CtlOsHor::SetSmpVdiv      (double i_s) {
  mdOs->SetSmpVdiv(i_s);
  ctRsmp->ReScale();
  ctMd->MRD_OsHorNumerics();
  return;
  }
void      CtlOsHor::SetSmpVscr      (double i_s) {
  mdOs->SetSmpVscr(i_s);
  ctRsmp->ReScale();
  ctMd->MRD_OsHorNumerics();
  return;
  }

void      CtlOsHor::SetTimVsrd      (double i_t) {
  mdOs->SetTimVsrd(i_t);
  ctMd->MRD_OsHorNumerics();
  return;
  }
void      CtlOsHor::SetSmpVsrd      (double i_s) {
  mdOs->SetSmpVsrd(i_s);
  ctMd->MRD_OsHorNumerics();
  return;
  }

bool      CtlOsHor::OsHorReBase(void *d) {
  mdOs->OsReBase();
  ctRsmp->ReScale();
  ctMd->MRD_OsHorNumerics();
  return false;
}

