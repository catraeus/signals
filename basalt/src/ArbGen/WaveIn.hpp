
// $Id: WaveIn.hpp 450 2019-04-27 21:29:58Z duncang $

//=================================================================================================
// Original File Name : WaveIn.h
// Original Author    : duncang
// Creation Date      : May 9, 2011
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//
//
//=================================================================================================


#ifndef WAVEIN_H_
#define WAVEIN_H_
#include <math.h>
#include <alsa/asoundlib.h>
#include <alsa/pcm.h>
#include <sigc++/sigc++.h>
#include <caes/Alsa/AlsaStreamIn.hpp>
#include <caes/Alsa/Alsa.hpp>
#include <caes/CaesTypes.hpp>

class WaveIn : public sigc::trackable {
  public:
                      WaveIn(Alsa *i_ae, AlsaStreamIn *i_asi);
    virtual          ~WaveIn();
    void              Announce();
    bool              Setup();
    void              MeasLvlWB(long i_count);
  private:
    Alsa             *ae;
    AlsaStreamIn     *asi;
    sigc::connection  theConn;
  public:
    double            FS;
    uint              channels;
    uint              bitDepth;
    double            deltaT;
    double            dBFSd;
    double            ampl;
    double            freq;         // sine wave frequency in Hz
    double           *vL;
    double           *vR;
  private:
    uint              N;
  };

#endif // WAVEIN_H_
