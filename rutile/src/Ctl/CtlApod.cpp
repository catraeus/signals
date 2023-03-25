
// $Id: CtlApod.cpp 572 2021-06-21 00:42:24Z duncang $

//=================================================================================================
// Original File Name : CtlApod.cpp
// Original Author    : duncang
// Creation Date      : 2017-02-05T22:17:03:32,839109273+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//=================================================================================================


#include "CtlApod.hpp"
#include <stdio.h>

CtlApod *CtlApod::ctApod = NULL;

         CtlApod::CtlApod        ( Signal *i_sig           )
: sig  ( i_sig ) {
  mdApod     = Apodia      :: GetInstance();
  ctMd       = CtlMsgDspch :: GetInstance();

  mdApod->SetN(1);
  mdApod->SetShape(Apodia::EAT_DIRICHLET);
  mdApod->SetNormPeak();
  mdApod->SetAnti(false);
  mdApod->BuildWindow();

  return;
  }
         CtlApod::~CtlApod       ( void                    ) {
  return;
  }
CtlApod *CtlApod::GetInstance    ( Signal *i_sig           ) {
  if(ctApod == NULL)
    ctApod = new CtlApod(i_sig);
  return ctApod;
}

void     CtlApod::SetShape       ( Apodia::eShape i_shape  ) {
  if(i_shape == mdApod->GetShape())    return;
  mdApod->SetShape(i_shape); /*FIXME*/ // MAGIC Row Number maps to eShape
  Update();
  return;
}
void     CtlApod::SetAlpha       ( double i_alpha          ) {
  if(i_alpha == mdApod->GetAlpha()) return;
  mdApod->SetAlpha(i_alpha);
  Update();
  return;
}
void     CtlApod::SetAnti        ( bool   i_anti           ) {
  if(i_anti == mdApod->GetAnti()) return;
  mdApod->SetAnti(i_anti);
  Update();
  return;
}
void     CtlApod::SetN           ( llong i_N              ) {
  llong oldN;
  llong oldC;

  oldN = mdApod->GetN();
  if(i_N == oldN)      return;
  mdApod->SetN(i_N);
  i_N = mdApod->GetN(); // in case it honked it down to a better length
  oldN = sig->GetN();
  if(i_N == oldN)      return;
  oldC = sig->GetCh();
  sig->ReBase(oldC, i_N);

  Update();
  return;
}

void     CtlApod::Update         ( void                    ) {
  mdApod->BuildWindow();
  ctMd->MRD_ApodRshAll();
  return;
}

void     CtlApod::DoIt           ( double **i_a             ) {
  double **ary;
  llong   numCh;

  ary   = i_a;
  numCh = sig->GetCh();
  for(llong c=0; c<numCh; c++)
    mdApod->DoIt(ary[c]);
  return;
}
