
// $Id: CtlRemez.hpp 572 2021-06-21 00:42:24Z duncang $

//=================================================================================================
// Original File Name : CtlRemez.hpp
// Original Author    : duncang
// Creation Date      : 2017-03-12T15:04:25,431717357+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :

#ifndef __CTL_REMEZ_HPP_
#define __CTL_REMEZ_HPP_
#include <caes/CaesTypes.hpp>
#include <caes/CaesCallBack.hpp>
#include <caes/AudioFile/Signal.hpp>
#include <caes/CaesRemez.hpp>


#include "CtlMsgDspch.hpp"


class CtlRemez {
  //===============================================================================================
  //Types
  public:
  private:
  //===============================================================================================
  //Methods
                     CtlRemez      ( Signal *i_sig  );
    virtual         ~CtlRemez      ( void         );
            void     Setup         ( void         );
  public:
    static  CtlRemez *GetInstance  ( Signal *i_sig  );
            Remez    *GetModel     ( void         ) { return mdRemez                    ;};

            void     SetPbEdge     ( llong   i_b,     double  i_f  );
            double   GetPbEdge     ( void         ) { return mdRemez->GetEdge(1)        ;};
            double   SetXbWidth    ( double  i_f  );
            double   GetXbWidth    ( void         ) { return mdRemez->GetEdge(2) - mdRemez->GetEdge(1);};
            void     SetSbWeight   ( double  i_w  );
            double   GetSbWeight   ( void         ) { return mdRemez->GetW(1)           ;};

            ullong   GetNmax       ( void         ) { return mdRemez->GetNmax()         ;};
            void     SetN          ( llong    i_N );
            ullong   GetN          ( void         ) { return sig->GetN()             ;};
            void     SetT          ( double   i_N );
            double   GetT          ( void         ) { return sig->GetT()             ;};

            void     Doit          ( void         );

  private:
  //===============================================================================================
  //Fields
  public:
  private:

            Signal         *sig;
            Remez          *mdRemez;

            CtlMsgDspch    *ctMd;

    static  CtlRemez       *ctSine;
  };

#endif // __CTL_REMEZ_HPP_
