// $Id: CtlOsHor.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : CtlOsHor.hpp
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

#ifndef __MDL_OS_HOR_HPP_
#define __MDL_OS_HOR_HPP_

#include <caes/CaesCallBack.hpp>
#include <caes/AudioFile/Signal.hpp>

#include "CtlOsVrt.hpp"
#include "../CtlRsmp.hpp"
#include "../../Mdl/MdlOs.hpp"
#include "../../Mdl/MdlSa.hpp"
#include "../CtlMsgDspch.hpp"

class CtlOsHor {
  public:
  public:
  private:
                      CtlOsHor        ( Signal *i_sig        );
    virtual          ~CtlOsHor        ( void                 );
  public:
    static  CtlOsHor *GetInstance     ( Signal *i_sig        );
            void      BuildEnv        ( Signal *i_sig        );

            //=====================================================================================================================
            //Screen and Horiz Settings only, no signal dependency
            void      SetScrSize      ( uint   i_w, uint i_h );

            //=====================================================================================================================

            void      SetTimVrsh      ( double i_t     );
            void      SetTimVsrd      ( double i_t     );

            void      SetSmpVrsh      ( double i_s     );
            void      SetSmpVsrd      ( double i_s     );

            void      SetSrlRto       ( double i_r     );
            void      SetPbkRto       ( double i_r     );

            void      SetTimVpxl      ( double i_t     );
            void      SetTimVdiv      ( double i_t     );
            void      SetTimVscr      ( double i_t     );

            void      SetSmpVpxl      ( double i_s     );
            void      SetSmpVdiv      ( double i_s     );
            void      SetSmpVscr      ( double i_s     );


  public:

  private:
  public:
  private:
           MdlSa           *mdSa;
           MdlOs           *mdOs;
           CtlRsmp         *ctRsmp;

           CtlMsgDspch     *ctMd;
           CbT<CtlOsHor>   *MRU_OsHorReBase;
           bool             OsHorReBase        ( void *ddd         );


    static CtlOsHor     *ctOsHor;
  };

#endif // __MDL_OS_HOR_HPP_
