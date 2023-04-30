
// $Id: CtlRsmp.cpp 511 2020-06-21 17:17:47Z duncang $

//=================================================================================================
// Original File Name : CtlRsmp.cpp
// Original Author    : duncang
// Creation Date      : Jun 9, 2013
// Copyright          : Copyright © 2013 - 2017 by Catraeus and Duncan Gray
//
// Description        :
//=================================================================================================


#include <stdio.h>
#include "CtlRsmp.hpp"
#include <caes/CaesMath.hpp>

CtlRsmp *CtlRsmp::ctRsmp = NULL;

         CtlRsmp::CtlRsmp             ( Signal *i_sig     )
: sig (i_sig) {
  BuildEnv  ( sig );
  BuildMain (     );
  Connect   (     );
  return;
  }
         CtlRsmp::~CtlRsmp            ( void              ) {
  return;
  }
CtlRsmp *CtlRsmp::GetInstance         ( Signal *i_sig     ) {
  if(ctRsmp == NULL)
    ctRsmp = new CtlRsmp(i_sig);
  return ctRsmp;
}
void     CtlRsmp::BuildEnv            ( Signal *i_sig     ) {
  apod     = Apodia      :: GetInstance(       );
  mdOs     = MdlOs       :: GetInstance( i_sig );
  mdSa     = MdlSa       :: GetInstance(       );
  ctMd     = CtlMsgDspch :: GetInstance(       );
  xfrm     = new SpecTran();
  return;
}
void     CtlRsmp::BuildMain           ( void              ) {
  pSig     = new double *[EK_MAX_CH];         // since we are depending on just pointing into the big mama from the disk.
  pTre     = new double *[EK_MAX_CH]; for(uint i=0; i<EK_MAX_CH; i++) pTre  [i] = new double[EK_MAX_SA_SMPS];
  pTim     = new double *[EK_MAX_CH]; for(uint i=0; i<EK_MAX_CH; i++) pTim  [i] = new double[EK_MAX_SA_SMPS];
  pFre     = new double *[EK_MAX_CH]; for(uint i=0; i<EK_MAX_CH; i++) pFre  [i] = new double[EK_MAX_SA_FRQS];
  pFav     = new double *[EK_MAX_CH]; for(uint i=0; i<EK_MAX_CH; i++) pFav  [i] = new double[EK_MAX_SA_FRQS];
  pFwork   = new double *[EK_MAX_CH]; for(uint i=0; i<EK_MAX_CH; i++) pFwork[i] = new double[EK_MAX_SA_FRQS];
  pFim     = new double *[EK_MAX_CH]; for(uint i=0; i<EK_MAX_CH; i++) pFim  [i] = new double[EK_MAX_SA_FRQS];
  pSa      = new double *[EK_MAX_CH]; for(uint i=0; i<EK_MAX_CH; i++) pSa   [i] = new double[EK_MAX_SA_DOTS];
  pOs      = new double *[EK_MAX_CH]; for(uint i=0; i<EK_MAX_CH; i++) pOs   [i] = new double[EK_MAX_OS_DOTS];

  for(llong cc=0; cc<EK_MAX_CH; cc++) for(llong ii=0; ii<EK_MAX_SA_SMPS; ii++)    pTim[cc][ii] = 0.0;
  for(llong cc=0; cc<EK_MAX_CH; cc++) for(llong ii=0; ii<EK_MAX_SA_FRQS; ii++)    pFim[cc][ii] = 0.0;

  intOs    = EIO_PLUCK;
  sigDom   = ESD_REAL;
  saDom    = EAD_PWR;

  return;
}
void     CtlRsmp::Connect             ( void              ) {
  xfrm->SetTimeAry(pTre[0], pTim[0]);
  xfrm->SetFreqAry(pFre[0], pFim[0]);

  MRU_RsmpOsAcq = new CbT<CtlRsmp>();
  MRU_RsmpOsAcq->SetCallback(this, &CtlRsmp::RsmpOsAcq);
  ctMd->MSU_RsmpOsAcq = MRU_RsmpOsAcq;

  MRU_RsmpSaAcq = new CbT<CtlRsmp>();
  MRU_RsmpSaAcq->SetCallback(this, &CtlRsmp::RsmpSaAcq);
  ctMd->MSU_RsmpSaAcq = MRU_RsmpSaAcq;
  return;
}
void     CtlRsmp::ReScale             ( void              ) {
  apod->SetN(mdSa->GetTvAna());
  apod->SetNormRMS();
  apod->BuildWindow();
  xfrm->Resize(mdOs->GetSmpVana(), mdSa->GetFvAna());
  return;
}

void     CtlRsmp::SetIntOs            ( eIntOs   i_decMet ) {
  intOs = i_decMet;
  return;
};

void     CtlRsmp::GrabHere            ( void              ) {
  sig->GrabHere(pSig);
  return;
}


bool     CtlRsmp::RsmpOsAcq           ( void    *d        ) {
  llong  chDex;
  llong  sigDex;
  llong  dotDex;
  llong  numCh;
  llong  numSmps;
  llong  numDots;
  double ratio;
  double yDeNorm;
  double yShift;

  double x1;
  double y1;
  double x2;
  double y2;
  double m;
  double b;

  y2 = 0.0;                   // since the top of the screen is 0.0
  y1 = mdOs->GetPxlVscrY();   // since the low is at the maximum pixel count.  Thank you mr. Farnsworth and your tractor for that one.
  x2 = mdOs->GetVoltMax();    // This is straight, no chaser
  x1 = mdOs->GetVoltMin();    // likewise
  m  = (y2 - y1) / (x2 - x1); //straight from high-school algebra
  b  = (y1 * x2 - y2 * x1) / (x2 - x1); // Have faith in the maths Luke

//  ==== Transfer the time signal into the scope domain
  yDeNorm  = mdOs->GetPxlVscrY();
  yDeNorm *= -0.5;
  yShift   = mdOs->GetPxlVscrY();
  yShift  *=  0.5;

  numCh  = sig->GetCh();
  numSmps = mdOs->GetSmpVscr();
  if(sig->GetN() < numSmps)
    numSmps = sig->GetN();
  numDots  = mdOs->GetTPvScr();
  ratio  = (double)numSmps / (double)numDots;
  if(pSig == 0)
    return false;
  if(*pSig == 0)
    return false;
  if(numDots == numSmps) {
    for(chDex=0; chDex < numCh; chDex++) {
      dotDex  = 0;
      sigDex = 0;
      while(dotDex < numDots) {
        double dd;
        dd  = pSig[chDex][sigDex];
        dd *= m;
        dd += b;
        pOs[chDex][dotDex] = dd;
        sigDex++;
        dotDex++;
      }
    }
  }
  else {
    for(chDex=0; chDex < numCh; chDex++) {
      dotDex = 0;
      sigDex = 0;
      while(dotDex < numDots) {
        double dd;
        dd = pSig[chDex][sigDex];
        dd *= m;
        dd += b;
        pOs[chDex][dotDex] = dd;
        dotDex++;
        sigDex = (llong)((double)dotDex * ratio);
      }
    }
  }
  return false;
}



bool     CtlRsmp::RsmpSaAcq           ( void  *d            ) {
  llong  chDex;
  llong  numCh;

  double **pFreAvg;

  llong  freqDex;
  llong  numFreq;
  double FS;
  double fMinXf;
  double fDelXf;
  double fMaxXf;
  double fMinSa;
  double fDelSa;
  double fMaxSa;
  double fStopSa;

  llong  saDex;
  llong  numSa;

  bool   isLogX;
  bool   isLogY;

  double x1;
  double y1;
  double x2;
  double y2;
  double m;
  double b;

  numCh   = sig->GetCh();
  //fprintf(stderr, ".");fflush(stderr);
  numFreq = mdSa->GetFvAna();
  numSa   = mdSa->GetFPvScr();
  FS      = sig->GetFS();

  pFreAvg = pFre;
  for(uint chDex=0; chDex < numCh; chDex++)
    apod->DoIt(pSig[chDex], pTre[chDex]);
  xfrm->Calc();
  xfrm->ToPS();
  for(llong cc=0; cc<numCh;   cc++)
    for(llong ii=0; ii<numFreq; ii++)
      pFwork[cc][ii] = pFreAvg[cc][ii];

  isLogX  = mdSa->IsFLog();
  isLogY  = mdSa->IsALog();


  fMinXf = 0.0;
  fMaxXf = 0.5 * FS;
  fDelXf = fMaxXf / (double)numFreq * 2.0;
  if(numFreq <= EK_DIV_FFT)
    fDelXf *= 0.5;

  fMinSa = mdSa->GetFStart();
  fMaxSa = mdSa->GetFStop();
  fStopSa = fMaxSa < (FS * 0.5) ? fMaxSa : (FS * 0.5);
  if(isLogX) {
    fMinSa = log10(fMinSa);
    fMaxSa = log10(fMaxSa);
  }
  fDelSa = (fMaxSa - fMinSa) / (double)(numSa);

  //  ==== Figure out the vertical scale.
    y2 = 0.0;                   // since the top of the screen is 0.0
    y1 = mdSa->GetAPvScr();   // since the low is at the maximum pixel count.  Thank you mr. Farnsworth and your tractor for that one.
    x2 = mdSa->GetAATop();       // This is straight, no chaser
    x1 = mdSa->GetAABot();       // likewise
    if(isLogY) {
      for(chDex = 0; chDex < numCh; chDex++) {
        for(freqDex = 0; freqDex < numFreq; freqDex++) {
          double r;
          r = fabs(pFwork[chDex][freqDex]);
          if(r < 0.0000000001)
             r = 0.0000000001;
          pFwork[chDex][freqDex] = log10(r);
        }
      }
      x2 = log10(x2);
      x1 = log10(x1);
    }

    m  = (y2 - y1) / (x2 - x1); //straight from high-school algebra
    b  = (y1 * x2 - y2 * x1) / (x2 - x1); // Have faith in the maths Luke

    for(chDex=0; chDex < 1; chDex++) {
      saDex   = 0;
      freqDex = 0;
      double thisFreq;
      double thisFreqLow;
      double thisFreqIntLow;
      double thisFreqHigh;
      thisFreq = -1.0e23;
      while(thisFreq < fStopSa) {
        double ll;
        double dd;
        double hh;

        thisFreq = (double)saDex * fDelSa + fMinSa; // actual frequency stepped by dot location of SA.
        if(isLogX)
          thisFreq = pow10(thisFreq); // and the log/lin thing needs to be undone.

        thisFreqIntLow  = thisFreq; // Now, since the SA and the DFT are aligned, absolute, by above ...
        thisFreqIntLow -= fMinXf;   // Slide down to the bottom of the DFT range
        thisFreqIntLow /= fDelXf;   // Turn into integer offsets from low.
        thisFreqIntLow = floor(thisFreqIntLow);
        freqDex = (llong)thisFreqIntLow;  // Now bracket our desired frequency to allow interpolation.
        thisFreqLow = thisFreqIntLow;
        thisFreqLow *= fDelXf;
        thisFreqLow += fMinXf;

        thisFreqHigh  = thisFreqIntLow + 1.0;
        thisFreqHigh *= fDelXf;
        thisFreqHigh += fMinXf;

        if(freqDex < 0)        freqDex = 0;
        if(freqDex >= numFreq - 1) {
          dd = x1;
        }
        else {
          ll = pFwork[chDex][freqDex];
          freqDex++;
          hh = pFwork[chDex][freqDex];

          dd = ll + (thisFreq - thisFreqLow) / fDelXf * (hh - ll);
        }
        dd *= m;
        dd += b;
        if(saDex > EK_MAX_SA_DOTS)
          saDex = EK_MAX_SA_DOTS;
        pSa[chDex][saDex] = dd;
        saDex++;
      }
      llong ddd;
      ddd = llmin(EK_MAX_SA_DOTS, numFreq); // FIXME -- This is pretty unruly.  The number of dots is not at all numFreq
      for( ; saDex < ddd; saDex++) {
        pSa[chDex][saDex] = x1 * m + b;
      }
    }


  return false;
}
void     CtlRsmp::CalcSpecAvg         ( void                ) {
  llong    numFreq;
  double  *fred;
  double **ary;
  double  *pS;
  double   factor;
  llong    N;
  llong    I;
  char     ss[32768];

  fprintf(stdout, "CtlRsmp::CalcSpecAvg()\n"); fflush(stdout);
  numFreq = mdSa->GetTvAna();
  N       = sig->GetN();
  fred = new double[numFreq];
  ary = sig->GetAry();
  if(ary == 0)
    return;
  pS = ary[0];
  factor  = ((double)N / (double)numFreq);
  I       = (llong)(factor + .0001);
  factor  = 1.0 / factor;
  for(llong f=0; f<numFreq; f++) {
    pFav[0][f] = 0.0;
  }
  xfrm->SetFreqAry(fred, pFim[0]);
  for(llong i=0; i<I; i++) {
    fprintf(stderr, "avg:  %lf\r", (double)i / (double)I); fflush(stderr);
    sprintf(ss, "avg:  %lf", (double)i / (double)I);
    ctMd->MRD_SaStatMsg(ss);
    apod->DoIt(pS, pTre[0]);
    xfrm->Calc();
    xfrm->ToPS();
    for(llong f=0; f<numFreq; f++) {
      pFav[0][f] += fred[f] * fred[f];
    }
    pS += numFreq;
  }
  for(llong f=0; f<numFreq; f++) {
    pFav[0][f] *= factor;
    pFav[0][f] = sqrt(pFav[0][f]);
  }
  xfrm->SetFreqAry(pFre[0], pFim[0]);
  return;
}
