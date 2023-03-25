
// $Id: CtlSine.hpp 696 2022-12-29 02:46:51Z duncang $

//=================================================================================================
// Original File Name : CtlSine.hpp
// Original Author    : duncang
// Creation Date      : 2017-03-12T15:04:25,431717357+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :

#ifndef __CTL_SINE_HPP_
#define __CTL_SINE_HPP_

#include <caes/CaesTypes.hpp>
#include <caes/CaesCallBack.hpp>
#include <caes/AudioFile/Signal.hpp>


#include "CtlMsgDspch.hpp"


class CtlSine {
  //===============================================================================================
  //Types
  private:
    enum eConst {
      MAX_COMPOS = 17,                // How many harmonics can we do?
      EC_MAX_N  = 1024*1024*256       // 1 G is too big, has to stay below FAT32 for stereo 4-byte
    };
  public:
  //===============================================================================================
  //Methods
  private:
                         CtlSine        ( Signal *i_sig  );
    virtual             ~CtlSine        ( void           );
  public:
    static  CtlSine     *GetInstance    ( Signal *i_sig  );

            ullong       GetNmax        ( void                   ) { return EC_MAX_N           ;};
            ullong       GetMaxCompos   ( void                   ) { return MAX_COMPOS         ;};
            void         SetLvlPhasor   ( ullong i_c, double i_a );
            double       GetLvlPhasor   ( ullong i_c             );
            void         SetPhase       ( ullong i_c, double i_a );
            double       GetPhase       ( ullong i_c             );
            void         SetLvlSin      ( ullong i_c, double i_a );
            double       GetLvlSin      ( ullong i_c             ) { return aSin[i_c]          ;};
            void         SetLvlCos      ( ullong i_c, double i_a );
            double       GetLvlCos      ( ullong i_c             ) { return aCos[i_c]          ;};
            void         SetFreqSine    ( ullong i_c, double i_f ); // Is always as freq rel to FS.
            double       GetFreqSine    ( ullong i_c             ) { return fSine[i_c]         ;};

            void         SetCentered    ( bool i_c  ) { centered   = i_c; return               ;};
            bool         GetCentered    ( void      ) {                   return centered      ;};
            void         SetQuadrature  ( bool i_q  ) { quadrature = i_q; return               ;};
            bool         GetQuadrature  ( void      ) {                   return quadrature    ;};

            void         DoIt           ( void        );

  private:
  //===============================================================================================
  //Fields
  public:
  private:

            Signal         *sig;

            //  Sinus Infections
            ullong          nSine;      // How many sine elements.  Element 0 is DC so the quad amplitude is not used
            double         *fSine;      // The Sines and Cosines each will be at the same frequency.
            double         *aSin;       // quadrature amplitudes OR out-of-phase shift
            double         *aCos;       // in-phase amplitudes   OR     in-phase shift
            bool            centered;   // To make an apodized filter be zero-phase.  false ? 0 phase = 0 samples : 0 phase = T[(N-1)/2].
            bool            quadrature; // Is this a 2 ch wave, then it can be IQ with mod.
            bool            error;      // Is something wrong with an input spec?

            CtlMsgDspch    *ctMd;

    static  CtlSine        *ctSine;
  };

#endif // __CTL_SINE_HPP_
