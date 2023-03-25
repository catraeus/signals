
// $Id: CtlWaveWr.cpp 756 2023-03-25 00:45:33Z duncang $

//=================================================================================================
// Original File Name : CtlWaveWr.cpp
// Original Author    : duncang
// Creation Date      : 2017-02-06T01:21:34,991820918+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//=================================================================================================


#include "CtlWaveWr.hpp"
#include <stdio.h>

CtlWaveWr *CtlWaveWr::ctWave = NULL;

         CtlWaveWr::CtlWaveWr        ( Signal *i_sig )
: sig (i_sig) {
  BuildEnv   ();
  BuildSetup ();
  return;
  }
         CtlWaveWr::~CtlWaveWr       ( void          ) {
  return;
  }
CtlWaveWr *CtlWaveWr::GetInstance    ( Signal *i_sig ) {
  if(ctWave == NULL)
    ctWave = new CtlWaveWr(i_sig);
  return ctWave;
}

void     CtlWaveWr::BuildEnv       ( void          ) {

  ctMd     = CtlMsgDspch ::GetInstance();
  return;
}
void     CtlWaveWr::BuildSetup     ( void          ) {
  return;
}



void     CtlWaveWr::SetN           ( llong i_N     ) {
  llong newN;
  llong oldN=0;
  llong oldC;

  newN = i_N;
  if(newN < 1)
    newN = 1;
  oldN = sig->GetN();
  if(i_N == oldN)
    return;
  oldC = sig->GetCh();
  sig->ReBase(oldC, newN);
  ctMd->Emit_FileWrChg();
}
void     CtlWaveWr::SetT           (double i_t     ) {
  double tt;
  llong nn;

  tt  = i_t;
  tt *= sig->GetFS();
  tt += DBL_ROUNDER;
  nn = (llong)tt;
  SetN(nn);
  return;
}
void     CtlWaveWr::SetCh          ( llong i_C     ) {
  llong nn;
  llong oldC;

  oldC = sig->GetCh();
  if(oldC == i_C)
    return;
  nn = sig->GetN();
  sig->ReBase(i_C, nn);
  return;
}

void     CtlWaveWr::ReBase         ( void          ) {
  llong    cc;
  llong    nn;
  double **ss;
  double   d;
  llong    numCh;
  llong    numN;

  d = 0.0;

  numCh = sig->GetCh();
  numN  = sig->GetN();
  ss    = sig->GetAry();
  for(cc=0; cc<numCh; cc++)
    for(nn=0; nn<numN; nn++)
      ss[cc][nn] = d;

  return;
}
