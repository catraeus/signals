
// $Id: WaveIn.cpp 450 2019-04-27 21:29:58Z duncang $

//=================================================================================================
// Original File Name : WaveIn.cpp
// Original Author    : duncang
// Creation Date      : May 9, 2011
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//
//
//=================================================================================================


#include "WaveIn.hpp"
#include <math.h>

WaveIn::WaveIn(Alsa *i_ae, AlsaStreamIn *i_asi)
: ae           (  NULL   )
, asi          (  NULL   )
, FS           (     1.0 )
, channels     (     1   )
, bitDepth     (    32   )
, deltaT       (     1.0 )
, dBFSd        ( 32768.0 )
, ampl         (     1.0 )
, freq         (     1.0 )
, vL           (  NULL   )
, vR           (  NULL   )
, N            (     0   ) {
  ae  = i_ae;
  asi = i_asi;
  vL          = (double *)malloc(32768*sizeof(double));
  vR          = (double *)malloc(32768*sizeof(double));
  }
WaveIn::~WaveIn() {
  }
void WaveIn::Announce() {
  fprintf(stdout, "Measurement System is Ready\n");
  }
bool WaveIn::Setup() {

  FS              = (double)(asi->GetFS());
  channels        = asi->GetCh();
  bitDepth        = asi->af->NumBits();


  deltaT          = PIx2 * freq / FS;
  dBFSd           = (1 << (bitDepth - 1)) - 1;
  theConn = asi->TakeWave.connect(sigc::mem_fun(this, &WaveIn::MeasLvlWB));
  return false;
  }
void WaveIn::MeasLvlWB(long i_count) {
  static double accL = 0.0;
  static double accR = 0.0;
  static double uppit = (double)(0x01000000) * (double)(0x01000000);
         double div;

  div = 1.0 / (double)i_count / 16.0;
  asi->Convert(i_count, vL, vR);
  for(long i=0; i<i_count; i++) {
    accL += vL[i]*vL[i]*uppit;
    accR += vR[i]*vR[i]*uppit;
    }
  N++;
  N &= 0x0000000f;
  if(N == 0) {
    fprintf(stdout, "%16.8f   %16.8f  %8ld\n", sqrt(accL*div), sqrt(accR*div), i_count);
    accL = 0.0;
    accR = 0.0;
    }
  return;
  }
