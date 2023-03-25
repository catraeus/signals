
// $Id: CtlSinc.cpp 572 2021-06-21 00:42:24Z duncang $

//=================================================================================================
// Original File Name : CtlSinc.cpp
// Original Author    : duncang
// Creation Date      : 2017-03-12T15:04:25,431717357+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//=================================================================================================


#include <stdio.h>
#include <caes/CaesMath.hpp>
#include "CtlSinc.hpp"

CtlSinc *CtlSinc::ctSine = NULL;

            CtlSinc::CtlSinc      ( Signal *i_sig  )
: sig (i_sig) {
  ctMd     = CtlMsgDspch :: GetInstance();


  SetFreq(0.0625);
  ctMd->MRD_SincNumerics();

  return;
  }
            CtlSinc::~CtlSinc     ( void         ) {
  return;
  }
CtlSinc    *CtlSinc::GetInstance  ( Signal *i_sig  ) {
  if(ctSine == NULL)
    ctSine = new CtlSinc(i_sig);
  return ctSine;
}

void         CtlSinc::SetFreq            ( double i_f    ) {
  if(i_f < 0.0) i_f = 0.0;
  if(i_f > 0.5) i_f = 0.5;
  fCutoff = i_f;
  ctMd->MRD_SincNumerics();
  return;
}

void         CtlSinc::DoIt               ( void          ) {
  llong    ch;
  llong    N;
  double **ary;
  double  *tVec;
  double   dt;
  double   ph;
  double   pht;
  bool     isOdd;
  llong    dexP;
  llong    dexN;
  llong    numK;
  double   y;


  ch    = sig->GetCh();
  N     = sig->GetN();
  ary   = sig->GetAry();
  dt    = PIx2;
  dt    *= fCutoff;
  isOdd  = ((N % 2) == 1);
  numK   = N / 2;

  for(llong c =0; c < ch; c++) {
    tVec   = ary[c];
    dexP   = N / 2 + 1;
    dexN   = N / 2;
    if(isOdd) {
      ph  = dt / 2.0;
      pht = dt / 2.0;
      tVec[dexP++] = 1.0;
    }
    else {
      ph  = dt;
      pht = dt;
    }
    for(llong i =0; i < numK; i++) {
      y = sin(ph) / pht;
      tVec[dexP++] += y;
      tVec[dexN--] += y;
      ph  += dt;
      pht += dt;
      while(ph > PIx2) ph -= PIx2;
    }
  }
  return;
}




