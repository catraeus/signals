
// $Id: AnSine.hpp 757 2023-03-25 01:15:02Z duncang $

//=================================================================================================
// Original File Name : AnSine.hpp
// Original Author    : duncang
// Creation Date      : Apr 27, 2019
// Copyright          : Copyright © 2019 by Catraeus and Duncan Gray
//
// Description        :
//    Analyzes an assumed moderately high quality sine wave.
//
//=================================================================================================

#ifndef __AN_SINUS_HPP_
#define __AN_SINUS_HPP_

#include <caes/CaesTypes.hpp>

#include <caes/CaesStat.hpp>

#include <caes/AudioFile/Signal.hpp>

#include "../Ctl/CtlMsgDspch.hpp"

#include "AnBulk.hpp"

class AnSine {
  private:
    enum eConst {
      ASC_MAX_CH = 4
    };
  public:
                     AnSine       ( Signal *i_sigRaw, Signal *i_sigNorm, Signal *i_sigCarr, Signal *i_sigBase, Signal *i_sigDemReIm , Signal *i_sigDemAmPh );
    virtual         ~AnSine       ( void              );
            void     SetCarrIQ    ( bool   i_isIQ     );
            bool     IsCarrIQ     ( void              ) {return isIQ;     };
            void     SetCarrFreq  ( double i_carrFreq );
            double   GetCarrFreq  ( void              ) {return anFc; };
            void     SetAnBW      ( double i_anBW     );
            double   GetAnBW      ( void              ) {return anBW;     };

            void     EstZerXcr    ( void         );
            void     DemFiltCarr  ( void         );
            void     DemCmplx     ( void         );
            void     DemFiltBase  ( void         );
            void     DemDecimate  ( void         );
            void     DemRect      ( void         );

            double   GetMean      (llong i) {if(i < 0) return meanZCt[0]; else if(i >= ASC_MAX_CH) return meanZCt[ASC_MAX_CH - 1]; else return meanZCt[i];};
            double   GetStDev     (llong i) {if(i < 0) return stDvZCt[0]; else if(i >= ASC_MAX_CH) return stDvZCt[ASC_MAX_CH - 1]; else return stDvZCt[i];};
            double   GetPhase     (llong i) {if(i < 0) return phase  [0]; else if(i >= ASC_MAX_CH) return phase  [ASC_MAX_CH - 1]; else return phase  [i];};
  private:
            void     FreqEst0     ( void        );
            void     PhaseEst     ( void        );
    static  void     Report       ( double *o_d, void *o_cp);
  public:
  private:
                  Signal        *sigRaw;
                  Signal        *sigNorm;
                  Signal        *sigCarr;
                  Signal        *sigBase;
                  Signal        *sigDemReIm;
                  Signal        *sigDemAmPh;
    const  static double         fir_1k0_48k[];
    const  static double         fir_lpf_48k[];
                  double         meanZCt[ASC_MAX_CH];
                  double         stDvZCt[ASC_MAX_CH];
                  double         phase  [ASC_MAX_CH];
                  double         freq   [ASC_MAX_CH];
                  double        *carrFirVec;
                  llong          carrFirN;
                  double        *baseFirVec;
                  llong          baseFirN;
                  double         anFc;     // always in FC = 1.0
                  double         anBW;     // assumed to be symmetrical about carrier, this is whole not single-sided BW.
                  bool           isIQ;     // Please look at this with imaginary glasses

                  CtlMsgDspch   *ctMd;
  public:

};

#endif // __AN_SINUS_HPP_
