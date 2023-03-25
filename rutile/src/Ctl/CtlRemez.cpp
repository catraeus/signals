
// $Id: CtlRemez.cpp 572 2021-06-21 00:42:24Z duncang $

//=================================================================================================
// Original File Name : CtlRemez.cpp
// Original Author    : duncang
// Creation Date      : 2017-03-12T15:04:25,431717357+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//=================================================================================================


#include <stdio.h>
#include <caes/CaesMath.hpp>
#include "CtlRemez.hpp"

CtlRemez *CtlRemez::ctSine = NULL;

            CtlRemez::CtlRemez       ( Signal *i_sig  )
: sig (i_sig) {
  mdRemez   = new Remez();
  ctMd      = CtlMsgDspch :: GetInstance();

  Setup();
  ctMd->MRD_RemezRshAll();

  return;
  }
            CtlRemez::~CtlRemez      ( void         ) {
  return;
  }
CtlRemez   *CtlRemez::GetInstance    ( Signal *i_sig  ) {
  if(ctSine == NULL)
    ctSine = new CtlRemez(i_sig);
  return ctSine;
}

void        CtlRemez::SetPbEdge      ( llong   i_b, double  i_f ) {
  double xbw;
  xbw = mdRemez->GetEdge(2) - mdRemez->GetEdge(1);
  mdRemez->SetEdge(1, i_f);
  mdRemez->SetEdge(2, i_f + xbw);
  ctMd->MRD_RemezRshAll();
  return;
}
void        CtlRemez::SetSbWeight    ( double   i_w ) {
  mdRemez->SetW(1, i_w);
  ctMd->MRD_RemezRshAll();
  return;
}
void        CtlRemez::SetN           ( llong    i_N ) {
  llong oldN;
  llong oldC;

  oldN = sig->GetN();
  if(i_N == oldN)    return;
  mdRemez->SetN(i_N);
  i_N = mdRemez->GetN();
  oldN = sig->GetN();
  if(i_N == oldN)    return;
  oldC = sig->GetCh();
  sig->ReBase(oldC, i_N);
  ctMd->MRD_RemezRshAll();
  return;
}
void        CtlRemez::SetT           ( double   i_N ) {
  sig->SetT(i_N);
  ctMd->MRD_RemezRshAll();
  return;
}


void        CtlRemez::Setup          ( void         ) {
  mdRemez->SetTypeBandPass();
  mdRemez->SetNumB(2);
  mdRemez->SetEdge(0,  0.0);
  mdRemez->SetEdge(1,  0.067);
  mdRemez->SetEdge(2,  0.068);
  mdRemez->SetEdge(3,  0.5);
  mdRemez->SetG   (0,  1.0);
  mdRemez->SetG   (1,  0.0);
  mdRemez->SetW   (0,  1.0);
  mdRemez->SetW   (1, 1145.0);
}

void        CtlRemez::Doit           ( void         ) {
  double **ary;
  double  *s;
  llong    N;
  llong    numCh;

  ary   = sig->GetAry();
  numCh = sig->GetCh();
  N     = sig->GetN();


  mdRemez->SetN(N);
  for(llong c=0; c<numCh; c++) {
    s = ary[c];
    mdRemez->SetAry(s);
    mdRemez->Calculate();
    mdRemez->NormPeak();
  }
  return;
}

