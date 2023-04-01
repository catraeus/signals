
// $Id: CtlSine.cpp 713 2023-02-13 01:30:20Z duncang $

//=================================================================================================
// Original File Name : CtlSine.cpp
// Original Author    : duncang
// Creation Date      : 2017-03-12T15:04:25,431717357+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//=================================================================================================


#include <stdio.h>
#include <caes/CaesMath.hpp>
#include "CtlSine.hpp"

CtlSine *CtlSine::ctSine = NULL;

            CtlSine::CtlSine      ( Signal *i_sig  )
: sig ( i_sig ) {
  ctMd     = CtlMsgDspch :: GetInstance();

  aSin       = new double [MAX_COMPOS];
  aCos       = new double [MAX_COMPOS];
  fSine      = new double [MAX_COMPOS];
  nSine      = 1;
  centered   = false;
  quadrature = false;
  error      = false;

  for(ullong i = 0; i < MAX_COMPOS; i++) {
    aSin [i] = 0.0;
    aCos [i] = i == 1 ? 1.0 : 0.0;
    fSine[i] = i == 1 ? 1.0 : 0.0;
  }
  ctMd->MRD_SineRshAll();

  return;
}
            CtlSine::~CtlSine     ( void         ) {
  return;
  }
CtlSine    *CtlSine::GetInstance  ( Signal *i_sig  ) {
  if(ctSine == NULL)
    ctSine = new CtlSine(i_sig);
  return ctSine;
}

void         CtlSine::SetFreqSine        ( ullong i_c, double i_f    ) {
  fprintf(stderr, "\n\nCtlSine::SetFreqSine(ch: %llu f: %lf)\n\n", i_c, i_f); fflush(stderr);
  if(i_f < 0.0) i_f = 0.0;
  if(i_f > 0.5) i_f = 0.5;
  if(i_c >= MAX_COMPOS) i_c = MAX_COMPOS-1;
  fSine[i_c] = i_f;
  ctMd->MRD_SineRshAll();
  return;
}
void         CtlSine::SetLvlCos          ( ullong i_c, double i_a    ) {
  aCos[i_c] = i_a;
  ctMd->MRD_SineRshAll();
  return;
}
void         CtlSine::SetLvlSin          ( ullong i_c, double i_a    ) {
  aSin[i_c] = i_a;
  ctMd->MRD_SineRshAll();
  return;
}
void         CtlSine::SetLvlPhasor       ( ullong i_c, double i_a    ) {
  double ph;
  ph = GetPhase(i_c);
  aCos[i_c] = i_a * cos(ph);
  aSin[i_c] = i_a * sin(ph);
  ctMd->MRD_SineRshAll();
  return;
}
double       CtlSine::GetLvlPhasor       ( ullong i_c                ) {
  double a;
  a  = aCos[i_c] * aCos[i_c];
  a += aSin[i_c] * aSin[i_c];
  a  = sqrt(a);
  return a;
}
void         CtlSine::SetPhase           ( ullong i_c, double i_ph   ) {
  double a;
  a = GetLvlPhasor(i_c);
  aCos[i_c] = a * cos(i_ph);
  aSin[i_c] = a * sin(i_ph);
  ctMd->MRD_SineRshAll();
  return;
}
double       CtlSine::GetPhase           ( ullong i_c    ) {
  return atan2(aSin[i_c], aCos[i_c]);
}

void         CtlSine::DoIt               ( void          ) {
  llong    ch;
  llong    N;
  double   amp;
  double **ary;
  double  *tVec;
  double   dt;
  double   ph;
  double   tt;


  ch   = sig->GetCh();
  N    = sig->GetN();
  dt   = PIx2;           // One tick is 1 cycle in radians and since freq is rel FS no more correction
  dt  *= fSine[1];       // and finally, the fundamental.

  ary = sig->GetAry();

  if(quadrature) {
    if(ch != 2)  {
      error = true;
      return;
    }
    else {
      tt = dt;
      while(tt > PIx2) tt -= PIx2;

      tVec = ary[0]; // In Phase

      amp  = GetLvlCos(1);
      amp *= SQ2;
      ph   = 0.0;
      for(llong i =0; i < N; i++) {
        tVec[i] += cos(ph) * amp;
        ph += tt;
        while(ph > PIx2) ph -= PIx2; // this mess is to avoid number system problems with big arguments of sin/cos
      }

      tVec = ary[1]; // Quadrature

      amp  = GetLvlSin(1);
      amp *= SQ2;
      ph   = 0.0;
      for(llong i =0; i < N; i++) {
        tVec[i] += sin(ph) * amp;
        ph += tt;
        while(ph > PIx2) ph -= PIx2;
      }
    }
  }
  else { // Not Quadrature
    for(llong c =0; c < ch; c++) {
      for(ullong h=0; h<MAX_COMPOS; h++) {
        tt = dt * (double)h;
        while(tt > PIx2) tt -= PIx2;

        tVec = ary[c];

        amp  = GetLvlCos(h);
        amp *= SQ2;
        ph   = 0.0;
        for(llong i =0; i < N; i++) {
          tVec[i] += cos(ph) * amp;
          ph += tt;
          while(ph > PIx2) ph -= PIx2;
        }
        amp  = GetLvlSin(h);
        amp *= SQ2;
        ph   = 0.0;
        for(llong i =0; i < N; i++) {
          tVec[i] += sin(ph) * amp;
          ph += tt;
          while(ph > PIx2) ph -= PIx2;
        }
      }
    }
  }
  return;
}




