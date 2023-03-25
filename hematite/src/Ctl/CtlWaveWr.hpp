
// $Id: CtlWaveWr.hpp 756 2023-03-25 00:45:33Z duncang $

//=================================================================================================
// Original File Name : CtlWaveWr.hpp
// Original Author    : duncang
// Creation Date      : 2017-02-06T01:21:34,991820918+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
/*
 This is only  for writing out the results of some analysis.
 */
#ifndef __CTL_WAVE_HPP_
#define __CTL_WAVE_HPP_

#include <caes/CaesTypes.hpp>
#include <caes/AudioFile/Signal.hpp>

#include "CtlMsgDspch.hpp"

class CtlWaveWr {
  //===============================================================================================
  //Types
  private:
  public:
    enum eConst   {
      EC_MAX_AP =     32768
    };
  private:
  //===============================================================================================
  //Methods
                     CtlWaveWr        ( Signal *i_sig );
    virtual         ~CtlWaveWr        ( void        );
  public:
    static  CtlWaveWr *GetInstance    ( Signal *i_sig );
  private:
            void     BuildEnv       ( void        );
            void     BuildSetup     ( void        );
  public:

            void     SetCh          ( llong   i_c );
            llong    GetCh          ( void        ) { return sig->GetCh()                 ;};
            void     SetN           ( llong   i_N );
            llong    GetN           ( void        ) { return sig->GetN()                  ;};
            void     SetT           ( double  i_N );
            double   GetT           ( void        ) { return sig->GetT()                  ;};
            double   GetFS          ( void        ) { return sig->GetFS()                 ;};

            void     ReBase         ( void        );

  private:
  //===============================================================================================
  //Fields
  public:
  private:


           Signal       *sig;
           CtlMsgDspch  *ctMd;

    static CtlWaveWr      *ctWave;
  };

#endif // __CTL_WAVE_HPP_
