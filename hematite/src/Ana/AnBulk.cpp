
// $Id: AnBulk.cpp 757 2023-03-25 01:15:02Z duncang $

//=================================================================================================
// Original File Name : AnBulk.hpp
// Original Author    : duncang
// Creation Date      : Apr 27, 2019
// Copyright          : Copyright © 2019 by Catraeus and Duncan Gray
//
// Description        :
//    No assumptions, just do some standard stats.
//
//=================================================================================================

#include "AnBulk.hpp"

        AnBulk::AnBulk        ( Signal *i_sigRaw, Signal *i_sigNorm )
: sigRaw(i_sigRaw)
, sigNorm(i_sigNorm)
{
  BuildEnv();
}
        AnBulk::~AnBulk       ( void           ) {
}

void    AnBulk::SetCarrIQ     ( bool    i_isIQ ) {
  if(i_isIQ == isIQ)
    return;
  isIQ = i_isIQ;
  return;
}

void    AnBulk::BuildEnv      ( void           ) {

  ctMd       = CtlMsgDspch::GetInstance();

  isIQ       = false;
  valid      = false;

  rawStats[0]    = new Stat();
  rawStats[1]    = new Stat();
  normStats[0]   = new Stat();
  normStats[1]   = new Stat();
  return;
}

void    AnBulk::CalcRaw       ( void           ) {
  llong    rawN;
  double  *rawVec;
  llong    rawCh;

  rawN    = sigRaw ->GetN();
  rawCh   = sigRaw ->GetCh();
  rawVec  = sigRaw ->GetAry()[0];
  rawStats[0]->SetVec(rawN, rawVec);
  rawVec  = sigRaw ->GetAry()[1];
  rawStats[1]->SetVec(rawN, rawVec);
  valid = rawStats[0]->GetValid() && rawStats[1]->GetValid() && ((rawCh == 1) || (rawCh == 2));
  if(valid) {
    rawStats[0]->CalcNormal();
    rawStats[1]->CalcNormal();
    rawStats[0]->CalcRr(rawStats[1]);
  }
  return;
}
void    AnBulk::CalcNorm      ( void           ) {
  llong    rawCh;
  llong    rawN;
  double  *rawVec[2];
  double   rawFS;

  llong    normCh;
  llong    normN;
  double  *normVec[2];
  double   normFS;

  double  *dSrc;
  double  *dDst;
  double   rawDC;
  double   rawA;

  rawCh         = sigRaw  -> GetCh();
  rawN          = sigRaw  -> GetN();
  rawVec[0]     = sigRaw  -> GetAry()[0];
  if(rawCh > 1)
    rawVec[1]   = sigRaw  -> GetAry()[1];
  rawFS         = sigRaw  -> GetFS();

  normCh        = rawCh;
  normN         = rawN;
  normFS        = rawFS;
  normVec[0]    = sigNorm -> ReBase(normCh, normN)[0];
  if(normCh > 1)
    normVec[1]  = sigNorm -> GetAry()[1];
                  sigNorm -> SetFS(normFS);

  for(llong chDex=0; chDex<rawCh; chDex++) {
    dSrc  = rawVec[chDex];
    dDst  = normVec[chDex];
    for(llong i=0; i<rawN; i++) *(dDst++) = *(dSrc++);  //Copy it over.
    dDst  = normVec[chDex];
    rawDC = rawStats[chDex]->GetM();
    for(llong i=0; i<rawN; i++) *(dDst++) -= rawDC; // IMPORTANT DC has to be pulled out before gain normalization
    dDst = normVec[chDex];
    rawA  = rawStats[chDex]->GetS();
    rawA  = 1.0 / rawA;                             // Sorry, I just can't loop a divide.
    for(llong i=0; i<rawN; i++) *(dDst++) *= rawA;
  }
  normStats[0]->SetVec(normN, normVec[0]);
  valid = normStats[0]->GetValid();
  if(valid)
    normStats[0]->CalcNormal();
  if(normCh > 1) {
    normStats[1]->SetVec(normN, normVec[1]);
    valid &= normStats[0]->GetValid();
    if(valid)
      normStats[1]->CalcNormal();
    normStats[0]->CalcRr(normStats[1]);
  }
  return;
}
