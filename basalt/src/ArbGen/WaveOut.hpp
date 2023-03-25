
// $Id: WaveOut.hpp 405 2018-01-20 22:18:32Z duncang $

//=================================================================================================
// Original File Name : WaveOut.h
// Original Author    : duncang
// Creation Date      : Jan 13, 2010
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    Does the generator work
//
//=================================================================================================

#ifndef WAVEFORM_H_
#define WAVEFORM_H_
#include <math.h>
#include <alsa/asoundlib.h>
#include <alsa/pcm.h>
#include <sigc++/sigc++.h>
#include <caes/Alsa/AlsaStreamOut.hpp>
#include <caes/Alsa/Alsa.hpp>
#include <caes/CaesTypes.hpp>

class WaveOut : public sigc::trackable {
  public:
    enum eSigType{
      EWT_SINE = 1,
      EWT_IMD4,
      EWT_SWEEP
      };
  public:
               WaveOut(Alsa *i_ae, AlsaStreamOut *i_aso);
    virtual   ~WaveOut();
    void       Announce();
    bool       Setup();
    void       GenSine(long i_count, double *i_phase);
    void       GenIMD4(long i_count, double *i_phase);
    void       GenSweep(long i_count, double *i_phase);
    void       SetFreq(double i_freq);
    void       SetLevelVFS(double i_ampl);
    void       SetLeveldBFS(double i_ampl);
    void       SetWave(eSigType i_waveType);
  private:
  public:
    double     FS;
    double     ampl;
    double     freq;         // sine wave frequency in Hz
    double     M_2PI;
    double     phase;
    double     deltaT;
    int        channels;
    double     zero_dBFS_pk;
    bool       QT;
    bool       QTlast;

    int        bitDepth;
    sigc::connection theConn;
  private:
    eSigType       sigType;
    Alsa          *ae;
    AlsaStreamOut *aso;
    double        *vL;
    double        *vR;
    uint     pp;
  };

#endif /* WAVEFORM_H_ */
