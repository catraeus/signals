
// $Id: AnBulk.hpp 757 2023-03-25 01:15:02Z duncang $

//=================================================================================================
// Original File Name : AnBulk.hpp
// Original Author    : duncang
// Creation Date      : Apr 27, 2019
// Copyright          : Copyright © 2019 by Catraeus and Duncan Gray
//
// Description        :
//    No assumptions, just do some standard stats.
//
//=================================================================================================

#ifndef __ANBULK_HPP_
#define __ANBULK_HPP_

#include <caes/CaesTypes.hpp>

#include <caes/AudioFile/Signal.hpp>
#include <caes/CaesStat.hpp>

#include "../Ctl/CtlMsgDspch.hpp"

class AnBulk {
  public:
             AnBulk        ( Signal *i_sigRaw, Signal *i_sigNorm );
    virtual ~AnBulk        ( void         );
    void     CalcRaw       ( void         );
    void     CalcNorm      ( void         );
    void     SetCarrIQ     ( bool i_isIQ  );
    bool     IsCarrIQ      ( void         ) { return isIQ;};
    double   GetRawM       ( llong   i_ch ) { return rawStats [i_ch]->GetM        ();};
    double   GetRawS       ( llong   i_ch ) { return rawStats [i_ch]->GetS        ();};
    double   GetRawNv      ( llong   i_ch ) { return rawStats [i_ch]->GetMin      ();};
    double   GetRawNo      ( llong   i_ch ) { return rawStats [i_ch]->GetMinOff   ();};
    double   GetRawXv      ( llong   i_ch ) { return rawStats [i_ch]->GetMax      ();};
    double   GetRawXo      ( llong   i_ch ) { return rawStats [i_ch]->GetMaxOff   ();};
    double   GetRawPrr     ( void         ) { return rawStats [   0]->GetRr       ();};
    double   GetFltM       ( llong   i_ch ) { return normStats[i_ch]->GetM        ();};
    double   GetFltS       ( llong   i_ch ) { return normStats[i_ch]->GetS        ();};
    double   GetFltNv      ( llong   i_ch ) { return normStats[i_ch]->GetMin      ();};
    double   GetFltNo      ( llong   i_ch ) { return normStats[i_ch]->GetMinOff   ();};
    double   GetFltXv      ( llong   i_ch ) { return normStats[i_ch]->GetMax      ();};
    double   GetFltXo      ( llong   i_ch ) { return normStats[i_ch]->GetMaxOff   ();};
    double   GetFltPrr     ( void         ) { return normStats[   0]->GetRr       ();};
    bool     GetValid      ( void         ) { return valid; };
  private:
    void     BuildEnv      ( void         );
  public:
  private:
    Stat        *rawStats[2];  // Raw input statistics machine
    Stat        *normStats[2]; // Flattened statistics machine
    Signal      *sigRaw;       // Raw input Signal
    Signal      *sigNorm;      // Normalized to 1.0 RMS Signal
    bool         isIQ;         // Please look at this with complex glasses

    bool         valid;

    CtlMsgDspch *ctMd;
};

#endif // __ANBULK_HPP_
