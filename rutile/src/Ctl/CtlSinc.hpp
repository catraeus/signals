
// $Id: CtlSinc.hpp 572 2021-06-21 00:42:24Z duncang $

//=================================================================================================
// Original File Name : CtlSinc.hpp
// Original Author    : duncang
// Creation Date      : 2017-03-12T15:04:25,431717357+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :

#ifndef __CTL_SINC_HPP_
#define __CTL_SINC_HPP_
#include <caes/CaesTypes.hpp>
#include <caes/CaesMath.hpp>
#include <caes/CaesCallBack.hpp>
#include <caes/AudioFile/Signal.hpp>


#include "CtlMsgDspch.hpp"


class CtlSinc {
  //===============================================================================================
  //Types
  private:
    enum eConst {
      MAX_SINES = 17,
      EC_MAX_N =     1024*1024*1024
    };
  public:
  //===============================================================================================
  //Methods
  private:
                         CtlSinc        ( Signal *i_sig  );
    virtual             ~CtlSinc        ( void           );
  public:
    static  CtlSinc     *GetInstance    ( Signal *i_sig  );

            ullong       GetNmax        ( void           ) { return EC_MAX_N          ;};
            void         SetFreq        ( double i_f     );
            double       GetFreq        ( void           ) { return fCutoff             ;};

            void         DoIt           ( void           );

  private:
  //===============================================================================================
  //Fields
  public:
  private:

            Signal         *sig;

            double          fCutoff;

            CtlMsgDspch    *ctMd;

    static  CtlSinc        *ctSine;
  };

#endif // __CTL_SINC_HPP_
