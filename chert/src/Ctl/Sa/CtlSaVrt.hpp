// $Id: CtlSaVrt.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : CtlSaVrt.hpp
// Original Author    : duncang
// Creation Date      : 2017-03-18T19:32:02,771922357+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//    Engine to figure out factors of an oscilloscope.
/*

Terms:
    Playback       | human-time  | Replay | Watching a sequence of images.  Freezing, Jogging forward and backward
    Playback Ratio | spanning    |        | Human-to-signal-time ... Refresh/sec given to the human OVER what rate if FS were honored?
    Stride         | signal-time | Fetch  | How many frames from leading-edge of screen n to screen n + 1
    Refresh        | spatial     | Sweep  | Single 2D image of data presentation.
    Scroll         | spatial     |        | Gap or overlap between two consecutive Screens.  Greater than 1 if gaps.
                                            Lots of traditional scopes only use the word "Scroll" when things get slow.
    Fix            | math        |        | There are 4 critical factors.  Two have to be chosen as fixed to allow 1 to be set while
                                            the last swivels (dependent variable) free.
    Signal         | signal-time |        | The whole recorded dataset.

    Frame          | FRM F
    Pixel          | PXL X
    Division       | DIV D
    Screen         | SCR N
    Stride         | SRD R
    Second         | SEC S
    Time           | TIM T
    Scroll         | SRL L

    Playback       | PBK K
    Ratio          | RTO O
    Rate           | RTE E
    Refresh        | RSH H
    Over           | OVR V
    Fix            | FIX I

*/
//
//=================================================================================================

#ifndef __CTL_SA_VRT_HPP_
#define __CTL_SA_VRT_HPP_

#include <caes/CaesCallBack.hpp>
#include <caes/AudioFile/Signal.hpp>

#include "../../Mdl/MdlSa.hpp"
#include "../CtlRsmp.hpp"
#include "../CtlMsgDspch.hpp"

class CtlSaVrt {
  public:
  public:
  private:
                      CtlSaVrt        ( Signal *i_sig );
    virtual          ~CtlSaVrt        ( void          );
  public:
    static  CtlSaVrt *GetInstance     ( Signal *i_sig );
  private:
            void      BuildEnv        ( Signal *i_sig );
            void      BuildSetup      ( void          );
  public:
            //=====================================================================================================================
            //Screen and Horiz Settings only, no signal dependency
            void      SetScrSize      ( uint   i_w, uint i_h );
            void      SetLog          ( void        ) { mdSa->SetALog();  return;};
            void      SetLin          ( void        ) { mdSa->SetAlin(); return;};
            //=====================================================================================================================
            void      SetVmax         ( double  i_v );


  public:

 private:
  public:
  private:

           MdlSa           *mdSa;
           CtlRsmp         *ctRsmp;

           CtlMsgDspch     *ctMd;
           bool             IpcSaVrtReCalc     ( void *d              ); //!< Something changed, Flood Everything Back to Right


    static CtlSaVrt     *ctSaHor;
  };

#endif // __CTL_SA_VRT_HPP_
