
// $Id: CtlNoise.cpp 693 2022-12-28 03:44:39Z duncang $

//=================================================================================================
// Original File Name : CtlNoise.cpp
// Original Author    : duncang
// Creation Date      : 2017-02-05T22:17:03:32,839109273+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//=================================================================================================


#include <stdio.h>
#include <caes/CaesMath.hpp>
#include "CtlNoise.hpp"

CtlNoise *CtlNoise::ctNoise = NULL;

            CtlNoise::CtlNoise       ( Signal *i_sig )
: sig ( i_sig ) {
  ctMd      = CtlMsgDspch :: GetInstance();

  SetLevel(0.1);
  ctMd->MRD_NoiseRshAll();

  return;
  }
            CtlNoise::~CtlNoise      ( void          ) {
  return;
  }
CtlNoise   *CtlNoise::GetInstance    ( Signal *i_sig ) {
  if(ctNoise == NULL)
    ctNoise = new CtlNoise(i_sig);
  return ctNoise;
}






void         CtlNoise::SetShapeGauss      ( void          ) {
  shape = ES_GAUSS;
  ctMd->MRD_NoiseRshAll();
  return;
}
void         CtlNoise::SetShapeRect       ( void          ) {
  shape = ES_RECT;
  ctMd->MRD_NoiseRshAll();
  return;
}
void         CtlNoise::SetRR              ( double i_r    ) {
  if(i_r < -1.0) i_r = -1.0;
  if(i_r >  1.0) i_r =  1.0;
  RR = i_r;
  ctMd->MRD_NoiseRshAll();
  return;
}
void         CtlNoise::SetLevel       ( double   i_a  ) {
  amp = i_a;
  ctMd->MRD_NoiseRshAll();
  return;
}


void         CtlNoise::DoIt           ( void          ) {
  llong   ch;
  llong   N;
  double   d0;
  double   d1;
  double   amp;
  double **ary;
  double  *tVec;
  double  *bVec;



  ch  = sig->GetCh();
  N   = sig->GetN();
  ary = sig->GetAry();
  amp = GetLevel();

  d0 = sqrt(      GetRR()) * amp; // base for correlated factor
  d1 = sqrt(1.0 - GetRR()) * amp; // small adder for de-correlated factor

  bVec = new double[N]; // Base vector that gets Pearson to be able to approach 1.0
  if(ShapeIsGauss())
    //for(llong k = 0; k < N; k++)
      caes_RandGaussVec(N, &bVec);
  else
    for(llong k =0; k < N; k++)
      bVec[k] = caes_RandRect();
  for(llong k =0; k < N; k++)
    bVec[k] *= d0;



  for(llong i =0; i < ch; i++) {
    tVec = ary[i];
    if(ShapeIsGauss())
     // for(llong k =0; k < N; k++)
        caes_RandGaussVec(N, &tVec);
    else
      for(llong k =0; k < N; k++)
        tVec[k] = caes_RandRect();
    for(llong k =0; k < N; k++)
      tVec[k] *= d1;
  }
  for(llong i = 0; i < ch; i++) {
    tVec = ary[i];
    for(llong k = 0; k < N; k++)
      tVec[k] += bVec[k];
  }
  for(llong i = 0; i < ch; i++) {
    tVec = ary[i];
    //for(llong k = 0; k < N; k++) // NO we already took care of amp in the decorrelation factor above
    //  tVec[k] *= amp;
  }

  delete bVec;

  return;
}



