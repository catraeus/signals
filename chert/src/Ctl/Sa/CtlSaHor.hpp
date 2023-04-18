// $Id: CtlSaHor.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : CtlSaHor.hpp
// Original Author    : duncang
// Creation Date      : Oct 21, 2013
// Copyright          : Copyright © 2013 - 2017 by Catraeus and Duncan Gray
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

#ifndef __CTL_SA_HOR_HPP_
#define __CTL_SA_HOR_HPP_

#include <caes/CaesCallBack.hpp>
#include <caes/AudioFile/Signal.hpp>

//#include "CtlSaVrt.hpp"
#include "../../Mdl/MdlSa.hpp"
#include "../CtlRsmp.hpp"
#include "../CtlMsgDspch.hpp"

class CtlSaHor {
  public:
  public:
  private:
                      CtlSaHor        ( Signal *i_sig        );
    virtual          ~CtlSaHor        ( void                 );
  public:
    static  CtlSaHor *GetInstance     ( Signal *i_sig        );
            void      BuildEnv        ( Signal *i_sig        );

            //=====================================================================================================================
            //Screen and Horiz Settings only, no signal dependency
            void      SetScrSize      ( uint   i_w, uint i_h );

            void      SetLog          ( void           );
            void      SetLin          ( void           );
            //=====================================================================================================================

            void      SetModeAvg      ( void           );
            void      SetModeTrack    ( void           );

            void      SetFmin         ( double i_f     );
            void      SetFcen         ( double i_f     );
            void      SetFmax         ( double i_f     );

            void      SetAnchS        ( void           ) {mdSa->SetAnchS(); return;};
            void      SetAnchC        ( void           ) {mdSa->SetAnchC(); return;};
            void      SetAnchP        ( void           ) {mdSa->SetAnchP(); return;};

            void      SetNtime        ( ullong i_t     );
            void      SetNfreq        ( ullong i_f     );
            void      SetDelFreq      ( double i_f     );
  public:

 private:
  public:
  private:

           MdlSa           *mdSa;
           bool             lastAvg;
           CtlRsmp         *ctRsmp;

           CtlMsgDspch     *ctMd;
           CbT<CtlSaHor>   *MRU_SaHorReBase;
           bool                 SaHorReBase     ( void *d              ); //!< Assume that the Signal and all screen parameters are valid.  Now what?


    static CtlSaHor     *ctSaHor;
  };

#endif // __CTL_SA_HOR_HPP_
