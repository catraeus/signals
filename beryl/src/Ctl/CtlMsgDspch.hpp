
// $Id: CtlMsgDspch.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : CtlMsgDspch.cpp
// Original Author    : duncang
// Creation Date      : 2017-02-06T01:32:18,581092635+00:00

// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//=================================================================================================


#ifndef __CTL_MSG_DSPCH_HPP_
#define __CTL_MSG_DSPCH_HPP_

#include <caes/CaesTypes.hpp>
#include <caes/CaesCallBack.hpp>

class CtlMsgDspch {
  private:
                                 CtlMsgDspch           (                );
    virtual                     ~CtlMsgDspch           (                );
  public:
    static CtlMsgDspch          *GetInstance           ( void           );  // I think it's pretty obvious why this is a singleton.

           void MRD_FileChanged       ( void             );
           void MRD_WaveChanged       ( void             );
           void MRD_ApodRshAll        ( void             );
           void MRD_NoiseRshAll       ( void             );
           void MRD_SineRshAll        ( void             );
           void MRD_SincNumerics      ( void             );
           void MRD_RemezRshAll       ( void             );

           CbV *MSU_FileRshAll;
           CbV *MSU_WaveRshAll;
           CbV *MSU_FaveRshAll;
           CbV *MSU_ApodRshAll;
           CbV *MSU_NoiseRshAll;
           CbV *MSU_SineRshAll;
           CbV *MSU_SincRshAll;
           CbV *MSU_RemezRshAll;
  private:
  public:

  private:
    static CtlMsgDspch          *ctMd;
};

#endif // __CTL_MSG_DSPCH_HPP_
