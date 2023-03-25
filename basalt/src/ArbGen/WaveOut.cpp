
// $Id: WaveOut.cpp 137 2016-11-20 16:47:49Z duncang $

//=================================================================================================
// Original File Name : WaveOut.cpp
// Original Author    : duncang
// Creation Date      : Jan 13, 2010
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    Does the generator work
//
//=================================================================================================

#include <stdio.h>
#include "WaveOut.hpp"
#include <math.h>

     WaveOut::WaveOut(Alsa *i_ae, AlsaStreamOut *i_aso)
: ae(i_ae)
, aso(i_aso)
{
  freq        = 440.0;                  // sine wave frequency in Hz
  ampl        = 1.0;
  vL          = (double *)malloc(32768*sizeof(double));
  vR          = (double *)malloc(32768*sizeof(double));
  QT          = true;
  QTlast      = true;
  sigType     = EWT_SINE;

  M_2PI = atan(1.0) * 4.0;
  zero_dBFS_pk = 32767.0;

  channels    =  2;
  bitDepth    = 16;

  FS     = 1.0;
  deltaT = 1.0;
  phase  = 0.0;
  pp     = 0;
  }
     WaveOut::~WaveOut() {
  free(vL);
  free(vR);
  }
void WaveOut::Announce() {
#ifdef FIND_BADNESS
  printf("Sine freq:   %.4f Hz\n", freq);
  printf("Sine ampl:   %.4f A Full-Scale\n", ampl);
#endif
  return;
  }
bool WaveOut::Setup() {

  aso->SetBufferFrames(16384);
  aso->SetBuffPerRatio(8);
  FS              = (double)(aso->GetFS());
  channels        = aso->GetCh();
  bitDepth        = aso->af->NumBits();

  M_2PI           = 2.0 * M_PI;
  deltaT          = M_2PI*freq/FS;
  zero_dBFS_pk    = (double)(((ullong)1 << (ullong)(bitDepth - 1)) - (ullong)1);

  SetWave(sigType);
  return false;
  }
void WaveOut::GenSine            (snd_pcm_sframes_t i_count, double *i_phase) {
  double   phase;
  double  *pL;
  double  *pR;
  double  dA;
  double   A;

  pp++;
  pp &= 0x0000000f;
  //if(pp == 0)
    //fprintf(stdout, "tick\n");
  phase       = *i_phase;
  if( QTlast &&  QT) {
    dA =  0.0;
    A  =  0.0;
    }
  else if( QTlast && !QT) {
    dA =  1.0 / (double)i_count;
    A  =  0.0;
    }
  else if(!QTlast &&  QT) {
    dA = -1.0 / (double)i_count;
    A  =  1.0;
    }
  else {
    dA =  0.0;
    A  =  1.0;
    }
  QTlast = QT;

  uint i = i_count;
  pL = vL;
  pR = vR;
  while(i-- > 0) {
    *pL     = sin(phase) * zero_dBFS_pk * ampl * A;
    *(pR++) = *(pL++);
    phase += deltaT;
    if(phase >= M_2PI) phase -= M_2PI;
    A += dA;
    }
  *i_phase = phase;
  aso->Convert(i_count, vL, vR);
  }
void WaveOut::GenIMD4            (snd_pcm_sframes_t i_count, double *i_phase) {
        double   phase;
        uint     i;
  const double Fl1 =  860.0 - 3.0;
  const double Fl2 =  860.0 + 3.0;
  const double Fu1 = 1380.0 - 8.0;
  const double Fu2 = 1380.0 + 8.0;
  //const double Fl1 =  220.0;
  //const double Fl2 =  262.0;
  //const double Fu1 =  294.0;
  //const double Fu2 =  392.0;
        double *pL;
        double *pR;
        double  dA;
        double   A;
        double  dT;

  phase       = *i_phase;

  dT = M_2PI / FS;
       if( QTlast &&  QT) {
    dA =  0.0;
    A  =  0.0;
    }
  else if( QTlast && !QT) {
    dA =  1.0 / (double)i_count;
    A  =  0.0;
    }
  else if(!QTlast &&  QT) {
    dA = -1.0 / (double)i_count;
    A  =  1.0;
    }
  else {
    dA =  0.0;
    A  =  1.0;
    }
  QTlast = QT;
  i = i_count;
  pL = vL;
  pR = vR;
  while(i-- > 0){
    *pL  = sin(Fl1 * phase);
    *pL += sin(Fl2 * phase);
    *pL += sin(Fu1 * phase);
    *pL += sin(Fu2 * phase);
    *pL *= 0.25 * zero_dBFS_pk * ampl * A;
    *(pR++) = *(pL++);;
    phase += dT;
    if(phase >= M_2PI) phase -= M_2PI;
    A += dA;
    }
  *i_phase = phase;
  aso->Convert(i_count, vL, vR);
  }
void WaveOut::GenSweep           (snd_pcm_sframes_t i_count, double *i_phase) {
        double   phase;
        uint     i;
  //const double Fl1 =  860.0 - 3.0;
  //const double Fl2 =  860.0 + 3.0;
  //const double Fu1 = 1380.0 - 8.0;
  //const double Fu2 = 1380.0 + 8.0;
  const double Fl1 =  220.0;
  const double Fl2 =  262.0;
  const double Fu1 =  294.0;
  const double Fu2 =  392.0;
        double *pL;
        double *pR;
        double  dA;
        double   A;
        double  dT;

  phase       = *i_phase;

  dT = M_2PI / FS;
       if( QTlast &&  QT) {
    dA =  0.0;
    A  =  0.0;
    }
  else if( QTlast && !QT) {
    dA =  1.0 / (double)i_count;
    A  =  0.0;
    }
  else if(!QTlast &&  QT) {
    dA = -1.0 / (double)i_count;
    A  =  1.0;
    }
  else {
    dA =  0.0;
    A  =  1.0;
    }
  QTlast = QT;
  i = i_count;
  pL = vL;
  pR = vR;
  while(i-- > 0){
    *pL  = sin(Fl1 * phase);
    *pL += sin(Fl2 * phase);
    *pL += sin(Fu1 * phase);
    *pL += sin(Fu2 * phase);
    *pL *= 0.25 * zero_dBFS_pk * ampl * A;
    *(pR++) = *(pL++);;
    phase += dT;
    if(phase >= M_2PI) phase -= M_2PI;
    A += dA;
    }
  *i_phase = phase;
  aso->Convert(i_count, vL, vR);
  }
void WaveOut::SetFreq(double i_freq) {
  freq = i_freq;
  deltaT = M_2PI*freq/FS;
  }
void WaveOut::SetLevelVFS(double i_ampl) {
#ifdef FIND_BADNESS
  double dBFS = log10(i_ampl);
#endif
  ampl = i_ampl;
#ifdef FIND_BADNESS
  fprintf(stdout, "new ampl: %f VFS    %f dBFS\n", ampl, dBFS);
#endif
  }
void WaveOut::SetLeveldBFS(double i_ampl) {
  double VFS = pow(10.0, i_ampl / 20.0);
  ampl = VFS;
#ifdef FIND_BADNESS
  fprintf(stderr, "new ampl: %f VFS    %f dBFS\n", VFS, i_ampl);
#endif
  }
void WaveOut::SetWave(eSigType i_waveType) {
  sigType = i_waveType;
  theConn.disconnect();
  switch(sigType) {
    case EWT_SINE:
      theConn = aso->MakeWave.connect(sigc::mem_fun(this, &WaveOut::GenSine));
      break;
    case EWT_IMD4:
      theConn = aso->MakeWave.connect(sigc::mem_fun(this, &WaveOut::GenIMD4));
      break;
    case EWT_SWEEP:
      theConn = aso->MakeWave.connect(sigc::mem_fun(this, &WaveOut::GenSweep));
      break;
    default:
      theConn = aso->MakeWave.connect(sigc::mem_fun(this, &WaveOut::GenSine));
      break;
    }
  }
