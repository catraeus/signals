
// $Id: CtlWave.hpp 572 2021-06-21 00:42:24Z duncang $

//=================================================================================================
// Original File Name : CtlWave.hpp
// Original Author    : duncang
// Creation Date      : 2017-02-06T01:21:34,991820918+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
/*
  Here we sit at the top.  There are 4 ways to make a rutile signal:
      Simple Apodizer
      Source - which is a sine and a noise.
      Apod multiplied in time by Source (DON'T FORGET TO FORCE N TO BE THE SAME)
      Remez
 */
#ifndef __CTL_WAVE_HPP_
#define __CTL_WAVE_HPP_
#include <caes/CaesTypes.hpp>
#include <caes/AudioFile/Signal.hpp>


#include "CtlApod.hpp"
#include "CtlSine.hpp"
#include "CtlNoise.hpp"
#include "CtlSinc.hpp"
#include "CtlRemez.hpp"

#include "CtlMsgDspch.hpp"

class CtlWave {
  //===============================================================================================
  //Types
  private:
    enum eType {
      ET_APOD,
      ET_APOD_SRC,
      ET_SRC,
      ET_APOD_SINC,
      ET_SINC,
      ET_REMEZ
    };
  public:
    enum eConst   {
      EC_MAX_AP =     32768
    };
  private:
  //===============================================================================================
  //Methods
                     CtlWave        ( Signal *i_sig );
    virtual         ~CtlWave        ( void        );
  public:
    static  CtlWave *GetInstance    ( Signal *i_sig );
  private:
            void     BuildEnv       ( void        );
            void     BuildSetup     ( void        );
  public:
            void     SetTypeApod    ( void        );
            bool     GetTypeApod    ( void        ) { return sigType == ET_APOD             ;};
            void     SetTypeApSrc   ( void        );
            bool     GetTypeApSrc   ( void        ) { return sigType == ET_APOD_SRC         ;};
            void     SetTypeSource  ( void        );
            bool     GetTypeSource  ( void        ) { return sigType == ET_SRC              ;};
            void     SetTypeApSinc  ( void        );
            bool     GetTypeApSinc  ( void        ) { return sigType == ET_APOD_SINC        ;};
            void     SetTypeSinc    ( void        );
            bool     GetTypeSinc    ( void        ) { return sigType == ET_SINC             ;};
            void     SetTypeRemez   ( void        );
            bool     GetTypeRemez   ( void        ) { return sigType == ET_REMEZ            ;};

            void     SetCh          ( llong   i_c );
            llong    GetCh          ( void        ) { return sig->GetCh()                 ;};
            void     SetN           ( llong   i_N );
            llong    GetN           ( void        ) { return sig->GetN()                  ;};
            void     SetT           ( double  i_N );
            double   GetT           ( void        ) { return sig->GetT()                  ;};
            double   GetFS          ( void        ) { return sig->GetFS()                 ;};

            void     DoIt           ( void        );

  private:
  //===============================================================================================
  //Fields
  public:
  private:

           CtlApod      *ctApod;
           CtlSine      *ctSine;
           CtlNoise     *ctNoise;
           CtlSinc      *ctSinc;
           CtlRemez     *ctRemez;
           Apodia       *mdApod;
           Remez        *mdRemez;

           Signal       *sig;
           CtlMsgDspch  *ctMd;

           eType         sigType;

    static CtlWave      *ctWave;
  };

#endif // __CTL_WAVE_HPP_
