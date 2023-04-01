
// $Id: CtlWave.cpp 693 2022-12-28 03:44:39Z duncang $

//=================================================================================================
// Original File Name : CtlWave.cpp
// Original Author    : duncang
// Creation Date      : 2017-02-06T01:21:34,991820918+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//=================================================================================================


#include "CtlWave.hpp"
#include <stdio.h>

CtlWave *CtlWave::ctWave = NULL;

         CtlWave::CtlWave        ( Signal *i_sig )
: sig (i_sig) {
  BuildEnv   ();
  BuildSetup ();
  return;
  }
         CtlWave::~CtlWave       ( void       ) {
  return;
  }
CtlWave *CtlWave::GetInstance    ( Signal *i_sig ) {
  if(ctWave == NULL)
    ctWave = new CtlWave(i_sig);
  return ctWave;
}

void     CtlWave::BuildEnv       ( void       ) {
  ctApod   = CtlApod     ::GetInstance(sig);
  ctSine   = CtlSine     ::GetInstance(sig);
  ctNoise  = CtlNoise    ::GetInstance(sig);
  ctRemez  = CtlRemez    ::GetInstance(sig);
  ctSinc   = CtlSinc     ::GetInstance(sig);
  mdApod   = Apodia      ::GetInstance();
  mdRemez  = ctRemez->GetModel();;

  ctMd     = CtlMsgDspch ::GetInstance();
  return;
}
void     CtlWave::BuildSetup     ( void       ) {
  sigType  = ET_APOD;
  return;
}



void     CtlWave::SetTypeApod    ( void       ) {
  sigType =  ET_APOD     ;
  SetN(sig->GetN());
  return;
}
void     CtlWave::SetTypeApSrc   ( void       ) {
  sigType =  ET_APOD_SRC ;
  SetN(sig->GetN());
  return;
}
void     CtlWave::SetTypeSource  ( void       ) {
  sigType =  ET_SRC      ;
  SetN(sig->GetN());
  return;
}
void     CtlWave::SetTypeApSinc  ( void       ) {
  sigType =  ET_APOD_SINC ;
  SetN(sig->GetN());
  return;
}
void     CtlWave::SetTypeApSinSinc  ( void       ) {
  sigType =  ET_APOD_SIN_SINC ;
  SetN(sig->GetN());
  return;
}
void     CtlWave::SetTypeSinc    ( void       ) {
  sigType =  ET_SINC     ;
  SetN(sig->GetN());
  return;
}
void     CtlWave::SetTypeRemez   ( void       ) {
  sigType =  ET_REMEZ    ;
  SetN(sig->GetN());
  return;
}


void     CtlWave::SetN           ( llong i_N ) {
  llong nn;
  llong newN;

  newN = i_N;
  if(newN < 1)
    newN = 1;
  switch(sigType) {
    case ET_APOD :
      nn   = ctApod->GetNmax();
      newN  = llmin(newN, nn);
      ctApod->SetN(newN);
      newN = ctApod->GetN();
      break;
    case ET_APOD_SRC :
      nn   = ctApod->GetNmax();
      newN  = llmin(newN, nn);
      nn   = ctSine->GetNmax();
      newN  = llmin(newN, nn);
      nn   = ctNoise->GetNmax();
      newN  = llmin(newN, nn);
      ctApod->SetN(newN);
      newN = ctApod->GetN();
      break;
    case ET_SRC :
      nn   = ctSine->GetNmax();
      newN  = llmin(newN, nn);
      nn   = ctNoise->GetNmax();
      newN  = llmin(newN, nn);
      break;
    case ET_APOD_SINC :
      nn   = ctApod->GetNmax();
      newN  = llmin(newN, nn);
      nn   = ctSinc->GetNmax();
      newN  = llmin(newN, nn);
      ctApod->SetN(newN);
      newN = ctApod->GetN();
      break;
    case ET_SINC :
      nn   = ctSinc->GetNmax();
      newN  = llmin(newN, nn);
      break;
    case ET_REMEZ :
      nn   = ctRemez->GetNmax();
      newN  = llmin(newN, nn);
      break;
    default      :
      break;
  }
  nn = sig->GetN();
  if(nn == newN)      return;
  nn = sig->GetCh();
  sig->ReBase(nn, newN);
  ctMd->MRD_WaveChanged();
}
void     CtlWave::SetT           (double i_t ) {
  double tt;
  llong nn;

  tt  = i_t;
  tt *= sig->GetFS();
  tt += DBL_ROUNDER;
  nn = (llong)tt;
  SetN(nn);
  return;
}
void     CtlWave::SetCh          ( llong i_C ) {
  llong nn;
  llong oldC;

  oldC = sig->GetCh();
  if(oldC == i_C)
    return;
  nn = sig->GetN();
  sig->ReBase(i_C, nn);
  return;
}

void     CtlWave::DoIt           ( void       ) {
  llong   cc;
  llong   nn;
  double **ss;
  double    d;
  llong   numCh;
  llong   numN;

  if(sigType == ET_APOD) // Because the APOD multiplies by the input, it has to be 1.0
    d = 1.0;
  else
    d = 0.0;

  numCh = sig->GetCh();
  numN  = sig->GetN();
  ss    = sig->GetAry();
  for(cc=0; cc<numCh; cc++)
    for(nn=0; nn<numN; nn++)
      ss[cc][nn] = d; // Zero out the destination array

    switch(sigType) {
      case ET_APOD:
        ctApod->DoIt(ss);
        break;
      case ET_APOD_SRC:
        ctNoise->DoIt();
        ctSine->DoIt();
        ctApod->DoIt(ss);
        break;
      case ET_SRC:
        ctNoise->DoIt();
        ctSine->DoIt();
        break;
      case ET_APOD_SINC:
        ctSinc->DoIt();
        ctApod->DoIt(ss);
        break;
      case ET_APOD_SIN_SINC:
        ctSinc->DoIt();
        ctSine->DoIt();
        ctApod->DoIt(ss);
        break;
      case ET_SINC:
        ctSinc->DoIt();
        break;
      case ET_REMEZ:
        ctRemez->Doit();
        break;
      default:
        break;
    }
  return;
}
