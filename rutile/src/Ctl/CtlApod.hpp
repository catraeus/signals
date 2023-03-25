
// $Id: CtlApod.hpp 572 2021-06-21 00:42:24Z duncang $

//=================================================================================================
// Original File Name : CtlApod.hpp
// Original Author    : duncang
// Creation Date      : 2017-02-05T22:17:03:32,839109273+00:00
// Copyright          : Copyright © 2013 - 2017 by Catraeus and Duncan Gray
//
// Description        :

#ifndef __CTL_APOD_HPP_
#define __CTL_APOD_HPP_
#include <caes/CaesTypes.hpp>
#include <caes/CaesCallBack.hpp>
#include <caes/CaesApodia.hpp>
#include <caes/AudioFile/Signal.hpp>
#include "CtlMsgDspch.hpp"


class CtlApod {
  //===============================================================================================
  //Types
  public:
    enum eConst   {
      EC_MAX_AP =     32768
    };
  private:
  //===============================================================================================
  //Methods
                     CtlApod     ( Signal *i_sig           );
    virtual         ~CtlApod     ( void                    );
  public:
    static  CtlApod *GetInstance ( Signal *i_sig           );

            void     SetShape    ( Apodia::eShape  i_shape );
            void     SetAnti     ( bool            i_anti  );
            bool     GetAnti     ( void                    ) { return mdApod->GetAnti()               ;};
            void     SetAlpha    ( double          i_alpha );

            void     SetN        ( llong           i_N     );
            llong    GetN        ( void                    ) { return mdApod->GetN()                  ;};
            llong    GetNmax     ( void                    ) { return mdApod->GetNmax()               ;};

            bool     GetAlphaEd  ( void                    ) { return mdApod->GetAlphaRange() != 0.0  ;};

            void     Update      ( void                    );

            void     DoIt        ( double **i_a );

  private:
  //===============================================================================================
  //Fields
  public:
  private:
            Apodia         *mdApod;
            Signal         *sig;
            CtlMsgDspch    *ctMd;

    static  CtlApod        *ctApod;
  };

#endif // __CTL_APOD_HPP_
