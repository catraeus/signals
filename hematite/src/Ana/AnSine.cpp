
// $Id: AnSine.cpp 757 2023-03-25 01:15:02Z duncang $

//=================================================================================================
// Original File Name : AnSine.cpp
// Original Author    : duncang
// Creation Date      : Apr 27, 2019
// Copyright          : Copyright © 2019 by Catraeus and Duncan Gray
//
// Description        :
//    Analyzes Sine Waves.
//
//=================================================================================================

#include <gtkmm.h>
#include "AnSine.hpp"
#include <math.h>
#include <caes/CaesMath.hpp>
#include "fir_1k0_48k.hpp"
#include "fir_lpf_48k.hpp"

        AnSine::AnSine        ( Signal *i_sigRaw, Signal *i_sigNorm, Signal *i_sigCarr, Signal *i_sigBase, Signal *i_sigDemReIm , Signal *i_sigDemAmPh )
: sigRaw          (i_sigRaw      )
, sigNorm         (i_sigNorm     )
, sigCarr         (i_sigCarr     )
, sigBase         (i_sigBase     )
, sigDemReIm      (i_sigDemReIm  )
, sigDemAmPh      (i_sigDemAmPh  )
, anFc            (1000.0        )
, anBW            (1000.0        )
, isIQ            (false         ) {
  ctMd         = CtlMsgDspch::GetInstance();
  carrFirVec   = (double *)fir_1k0_48k;
  carrFirN     =  sizeof  (fir_1k0_48k) / sizeof(double);
  baseFirVec   = (double *)fir_lpf_48k;
  baseFirN     =  sizeof  (fir_lpf_48k) / sizeof(double);
  for(llong dex=0; dex<ASC_MAX_CH; dex++) meanZCt[dex] =    1.000;
  for(llong dex=0; dex<ASC_MAX_CH; dex++) stDvZCt[dex] =    0.001;
  for(llong dex=0; dex<ASC_MAX_CH; dex++) phase  [dex] =    0.000;
  for(llong dex=0; dex<ASC_MAX_CH; dex++) freq   [dex] =    1.000;
  fprintf(stderr, "firLen: %Ld\n", carrFirN); fflush(stderr);
  return;
}
        AnSine::~AnSine       ( void               ) {
  return;
}

void    AnSine::SetCarrIQ      ( bool    i_isIQ     ) {
  if(i_isIQ == isIQ)
    return;
  isIQ = i_isIQ;
  return;
}
void    AnSine::SetCarrFreq    ( double  i_carrFreq ) {
  if(i_carrFreq < 1.0)
    i_carrFreq = 1.0;
  if(i_carrFreq > (sigRaw->GetFS() - 1.0))
    i_carrFreq = sigRaw->GetFS() - 1.0;
  anFc = i_carrFreq;
  if(anBW > anFc)
    anBW = anFc;
  if(anBW > sigRaw->GetFS() - anFc)
    anBW = sigRaw->GetFS() - anFc;
  return;
}
void    AnSine::SetAnBW        ( double  i_anBW     ) {
  if(i_anBW == anBW)
    return;
  anBW = i_anBW;
  SetCarrFreq(anFc); // Schnock the anBW based on anFc
  return;
}
void    AnSine::EstZerXcr      ( void               ) {
  FreqEst0();
  PhaseEst();
  return;
}


void    AnSine::FreqEst0       ( void               ) {
  ullong   N;
  ullong   NZC;
  double  *aryZCT;
  double **normAry;
  bool     wasPos;
  bool     isPos;
  double   lastY;
  double   thisY;
  double   initZCt;
  double   lastZCt;
  double   thisZCt;
  double   FS;
  ullong   zcCount;
  double   completeness;
  char     tStr[256];

  zcCount = 0;

  strcpy(tStr, "Estimate Freq by Zero Crossings");
  ctMd->Emit_SigStatWork(tStr);
  completeness = 0.0;
  ctMd->Emit_SigStatCmpl(&completeness);
  while (Gtk::Main::events_pending())
    Gtk::Main::iteration();
  N       = sigNorm->GetN   ();
  normAry = sigNorm->GetAry ();
  FS      = sigNorm->GetFS  ();

  aryZCT = NULL;
  for(uint chDex = 0; chDex < sigNorm->GetCh(); chDex++) {
    double *v;
    v = normAry[chDex];
                    wasPos = false;
    if(v[0] >= 0.0) wasPos = true;
    NZC      = 0;
    lastY    = v[0];
    initZCt  = -1.0;
    thisZCt  = 0.0;
    for(uint i = 1; i < N; i++) { // First, find out how many positive-going zero crossings there are.
      thisY = v[i];
                      isPos = false;
      if(v[i] >= 0.0) isPos = true;
      if(isPos && !wasPos) {
        thisZCt  =  lastY / (lastY - thisY);
        thisZCt += (double)i;
        if(NZC == 0) initZCt = thisZCt;  // Capture the first zero crossing found
        NZC++;
      }
      wasPos = isPos;
      lastY = thisY;
    }
    meanZCt[chDex] = (thisZCt - initZCt) / (double)(NZC - 1); // The mean is a simple calculation. Number of Periods, not ZCs.
    if(aryZCT != NULL) delete aryZCT;
    aryZCT = new double[NZC];
                    wasPos = false;
    if(v[0] >= 0.0) wasPos = true;
    lastY   = v[0];
    lastZCt = -1.0;
    thisZCt =  0.0;
    zcCount    =  0;
    for(uint i = 1; i < N; i++) { // Now populate an array of ZC times
      thisY = v[i];
                      isPos = false;
      if(v[i] >= 0.0) isPos = true;
      if(isPos && !wasPos) {
        thisZCt  =  lastY / (lastY - thisY);
        thisZCt += (double)i;
        if(zcCount > 0) { // There needs to be a first zero-crossing to find a first delta.
          aryZCT[zcCount - 1] = thisZCt - lastZCt - meanZCt[chDex]; // This is the RMS finding session.  Subtract the mean.
        }
        zcCount++;
        lastZCt = thisZCt;  // This is cycle jitter.  It will be really high if there is freq drift.
      }
      wasPos = isPos;
      lastY  = thisY;
    }
    stDvZCt[chDex] = 0.0;
    for(uint i = 0; i < NZC - 1; i++) {         // Accumulating Periods, not ZCs
      stDvZCt[chDex] += aryZCT[i] * aryZCT[i];  // Sum of the Squares
    }
    stDvZCt[chDex] /= (double)(NZC - 2);        // The Mean, unbiased.  first, the number of periods is 1 less than the number of zero-crossings.
    stDvZCt[chDex]  = sqrt(stDvZCt[chDex]);     // The Root
    stDvZCt[chDex] /= FS;                       // compensate for FS (normalize to present as sec jitter RMS)
    freq   [chDex]  = 1.0 / meanZCt[chDex];     // But this is currently as T - FS-relative freq
    meanZCt[chDex] /= FS;                       // compensate for FS (de-normalize) Can do this now tha RMS is done.
  }
  delete aryZCT;
  completeness = 1.0;
  ctMd->Emit_SigStatCmpl(&completeness);
  while (Gtk::Main::events_pending())
    Gtk::Main::iteration();
  return;
}
void    AnSine::PhaseEst       ( void               ) {
  llong    N;
  double   absAmp;
  double **normAry;
  double   delPh;    // delta Phase of the sinusoid estimated elsewhere, per FS tick.
  double   currPh;   // instantaneous phase
  double   realAmp;
  double   imagAmp;
  double  *currSmp;
  double   wrapPh;
  double   completeness;
  char     tStr[256];

  wrapPh = PI * 2.0;

  N       = sigNorm->GetN   ();
  normAry = sigNorm->GetAry ();

  for(llong chDex = 0; chDex < sigNorm->GetCh(); chDex++) {
    delPh   = PI * 2.0 * freq[chDex];
    sprintf(tStr, "Estimate Phase ch[%Ld]", chDex);
    ctMd->Emit_SigStatWork(tStr);
    currPh  = 0.0;
    realAmp = 0.0;
    imagAmp = 0.0;
    currSmp = normAry[chDex];
    for(llong i = 0; i < N; i++) {
      realAmp += *currSmp * cos(currPh);
      imagAmp += *currSmp * sin(currPh);
      currSmp++;
      currPh += delPh;
      if(currPh > wrapPh)
        currPh -= wrapPh;
      if((i % 10000000) == 0) {
        completeness = (double)i / (double)N;
        ctMd->Emit_SigStatCmpl(&completeness);
        while (Gtk::Main::events_pending())
          Gtk::Main::iteration();
      }
    }
    realAmp *= SQ2;
    imagAmp *= SQ2;
    realAmp /= (double)N;
    imagAmp /= (double)N;
    phase[chDex] = atan2(realAmp, imagAmp);
    phase[chDex] /= PI;
    phase[chDex] *= 180;
    absAmp = sqrt(realAmp * realAmp + imagAmp * imagAmp);
    currSmp = normAry[chDex];
    for(llong i=0; i<N; i++)
      currSmp[i] /= absAmp;
    completeness = 1.0;
    ctMd->Emit_SigStatCmpl(&completeness);
    while (Gtk::Main::events_pending())
      Gtk::Main::iteration();
  }
  completeness = 1.0;
  ctMd->Emit_SigStatCmpl(&completeness);
  while (Gtk::Main::events_pending())
    Gtk::Main::iteration();
  return;
}






//=================================================================================================
//==== Demodulation machinery now.
void    AnSine::DemFiltCarr   ( void        ) {
  llong    normN;
  double **normAry;
  double  *normVec;
  double   normFS;

  llong    carrN;
  double **carrAry;
  double  *carrVec;

  char     tStr[256];

  normN    = sigNorm->GetN();
  normAry  = sigNorm->GetAry();
  normVec  = normAry[0];  // Let's assume a real-only raw signal for now.  This discards the other channels.
  normFS   = sigNorm->GetFS();

  carrN    = normN - carrFirN + 1;

             sigCarr->MakeBlank();
  carrAry  = sigCarr->ReBase(2, carrN); // So, we'll put the filtered thinger into the 0 array
             sigCarr->SetFS(normFS);
  carrVec  = carrAry[0];
  sprintf(tStr, "Carrier Filter");
  ctMd->Emit_SigStatWork(tStr);
  while (Gtk::Main::events_pending())
    Gtk::Main::iteration();

  ConvolveInt           ( carrFirN, carrFirVec,   normN, normVec, carrVec, &(AnSine::Report), this );
  return;
}
void    AnSine::DemCmplx      ( void        ) {
  double   thisFC;
  double   thisFS;
  double   curPh;
  double   delPh;

  double   carrN;
  double **carrAry;
  double  *carrVec;

  double   demN;  (void)demN;  //  The demod is in-place, so it is actually the carrXXX too
  double **demAry;
  double  *demVec;

  double  *pSrc;
  double  *pDst;

  char     tStr[256];

  thisFC = 1.0 / meanZCt[0];
  if(dabs(anFc - thisFC) / anFc > 0.01) // Fail if more than 1% off
    return;

  carrN   = sigCarr->GetN();
  carrAry = sigCarr->GetAry();

  demN    = carrN;
  demAry  = carrAry;


  thisFS  = sigRaw->GetFS();
  delPh   = thisFC / thisFS;
  delPh  *= PIx2;

  sprintf(tStr, "Demodulate IQ");
  ctMd->Emit_SigStatWork(tStr);
  while (Gtk::Main::events_pending())
    Gtk::Main::iteration();



  carrVec = carrAry[0];
  demVec  = demAry[1];  // IMPORTANT  Here is where the carrAry gets re-used/usurped for the demod output.
  pSrc    = carrVec;
  pDst    = demVec;
  curPh   = 0.0;
  for(ullong dn=0; dn<carrN; dn++) {
   *pDst   = sin(curPh) * *pSrc;
    curPh += delPh;
    pSrc++;
    pDst++;
    while(curPh > PIx2) curPh -= PIx2;
  }




  carrVec = carrAry[0];
  demVec  = demAry[0];   // IMPORTANT  Here is where the carrAry gets re-used/usurped for the demod output. Destroying source done last.
  pSrc    = carrVec;     // Yes redundant, but future generations won't have to search for where they went wrong.
  pDst    = demVec;
  curPh   = 0.0;
  for(ullong dn=0; dn<carrN; dn++) {
   *pDst = cos(curPh) * *pSrc;
    curPh += delPh;
    pSrc++;
    pDst++;
    while(curPh > PIx2) curPh -= PIx2;
  }

  return;
}
void    AnSine::DemFiltBase   ( void        ) {
  llong    baseN;
  double **baseAry;
  double  *baseVec;

  llong    demN;  // Warning, the demodulate here is the in-place in the Base Signal, not to the Dem Signal.
  double **demAry;
  double  *demVec;
  double   carrFS;

  char     tStr[256];

  demN    = sigCarr->GetN();
  demAry  = sigCarr->GetAry();
  carrFS  = sigCarr->GetFS();

  baseN   = demN - baseFirN + 1;

            sigBase->MakeBlank();
  baseAry = sigBase->ReBase(2, baseN); // Is an IQ signal
            sigBase->SetFS(carrFS);

  demVec  = demAry[0];  //  Carr has had the carrier taken out by sin/cos
  baseVec = baseAry[0];
  sprintf(tStr, "Baseband Filter I");
  ctMd->Emit_SigStatWork(tStr);
  while (Gtk::Main::events_pending())
    Gtk::Main::iteration();

  ConvolveInt           ( baseFirN, baseFirVec,   demN, demVec, baseVec, &(AnSine::Report), this );



  demVec     = demAry[1];  //  Carr has had the carrier taken out by sin/cos
  baseVec    = baseAry[1];
  sprintf(tStr, "Baseband Filter Q");
  ctMd->Emit_SigStatWork(tStr);
  while (Gtk::Main::events_pending())
    Gtk::Main::iteration();

  ConvolveInt           ( baseFirN, baseFirVec,   demN, demVec, baseVec, &(AnSine::Report), this );
  return;
}
void    AnSine::DemDecimate   ( void        ) {
  llong    baseN;
  double **baseAry;
  double   baseFS;

  llong    demN;
  double **demReImAry;
  double **demAmPhAry;
  double   demFS;

  double   decimRatio;
  llong    decimStride;

  baseN   = sigBase->GetN();
  baseAry = sigBase->GetAry();
  baseFS  = sigBase->GetFS();

  demFS       = 1000.0;
  decimRatio  = demFS / baseFS;  // FIXME, the carrier frequency / decimation ratio is MAGICK number here.
  decimStride = (llong)floor(1.0 / decimRatio +  DBL_EPS);
  demN        = (llong)floor((double)baseN * decimRatio +  DBL_EPS);
  demReImAry  = sigDemReIm->ReBase(2, demN);
            sigDemReIm->SetFS(demFS);
  for(llong i=0; i<demN; i++)
    demReImAry[0][i] = baseAry[0][i * decimStride];
  for(llong i=0; i<demN; i++)
    demReImAry[1][i] = baseAry[1][i * decimStride];

  demAmPhAry  = sigDemAmPh->ReBase(2, demN);
                sigDemAmPh->SetFS(demFS);
  for(llong i=0; i<demN; i++) {
    double re = demReImAry[0][i];
    double im = demReImAry[1][i];
    double am = sqrt(re * re + im * im);
    double ph = atan2(im, re);
    demAmPhAry[0][i] = am;
    demAmPhAry[1][i] = ph;
  }
  DemRect();
  return;
}
void    AnSine::DemRect       ( void        ) {
  Stat   *tTaylor;
  double  t2;
  double  t1;
  double  t0;
  double  *vec;

  vec = sigDemAmPh->GetAry()[1];
  tTaylor = new Stat();
  tTaylor->SetVec(sigDemAmPh->GetN(), vec);
  tTaylor->CalcTaylor3(&t0, &t1, &t2);
  t1 *= sigDemAmPh->GetFS() / PIx2;
  t0 *= 1.0D / PIx2;
  fprintf(stdout, "        Rectification:  t2: %lg    t1: %lg    t0: %lg\n", t2, t1, t0);
  ctMd->Emit_SigWrChg();
  return;
}



//=================================================================================================
//==== Reporting.
void    AnSine::Report         ( double *o_d, void *o_cp) {
  AnSine *tAs = (AnSine *)o_cp;

  tAs->ctMd->Emit_SigStatCmpl(o_d);
  while (Gtk::Main::events_pending())
    Gtk::Main::iteration();
 return;
}
