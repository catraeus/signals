
// $Id: CtlNoise.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : CtlNoise.hpp
// Original Author    : duncang
// Creation Date      : 2017-02-05T22:17:03:32,839109273+00:00
// Copyright          : Copyright © 2013 - 2017 by Catraeus and Duncan Gray
//
// Description        :

#ifndef __CTL_NOISE_HPP_
#define __CTL_NOISE_HPP_

#include <caes/CaesTypes.hpp>
#include <caes/CaesCallBack.hpp>
#include <caes/AudioFile/Signal.hpp>


#include "CtlMsgDspch.hpp"


class CtlNoise {
  //===============================================================================================
  //Types
  private:
    enum eShape {
      ES_GAUSS,
      ES_RECT
    };
    enum eConst   {
      EC_MAX_N =     1024*1024*1024
    };
  public:
  private:
  //===============================================================================================
  //Methods
                     CtlNoise     ( Signal *i_sig );
    virtual         ~CtlNoise     ( void          );
  public:
    static  CtlNoise *GetInstance ( Signal *i_sig );

            void     SetShapeGauss( void          );
            void     SetShapeRect ( void          );
            bool     ShapeIsGauss ( void          ) { return shape == ES_GAUSS      ;};
            bool     ShapeIsRect  ( void          ) { return shape == ES_RECT       ;};

            void     SetRR        ( double  i_r  );
            double   GetRR        ( void         ) { return RR                     ;};

            ullong   GetNmax      ( void         ) { return EC_MAX_N               ;};
            void     SetN         ( llong   i_N  );
            ullong   GetN         ( void         ) { return sig->GetN()         ;};
            void     SetT         ( double  i_N  );
            double   GetT         ( void         ) { return sig->GetT()         ;};

            void     SetLevel     ( double  i_a  );
            double   GetLevel     ( void         ) { return amp  ;};

            void     DoIt         ( void         );

  private:
  //===============================================================================================
  //Fields
  public:
  private:
            double          amp;   // amplitude
            double          RR;       // Pearson's correlation coefficient for the noise
            eShape          shape;    // rect PDF or Gauss PDF

            Signal         *sig;

            CtlMsgDspch    *ctMd;

    static  CtlNoise       *ctNoise;
  };

#endif // __CTL_NOISE_HPP_
