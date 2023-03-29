
// $Id: CtlMsgDspch.hpp 757 2023-03-25 01:15:02Z duncang $

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

#include <caes/CaesCallBack.hpp>
#include <caes/CaesTypes.hpp>

class CtlMsgDspch {
  private:
                        CtlMsgDspch           (                  );
    virtual            ~CtlMsgDspch           (                  );
  public:
    static CtlMsgDspch *GetInstance           ( void             );  // I think it's pretty obvious why this is a singleton.

           void         Emit_FileRdChg        ( void             );

           void         Emit_SigWrChg         ( void             );
           void         Emit_SineHasData      ( void             );

           void         Emit_SigStatWork      ( char   *i_tStr   );
           void         Emit_SigStatCmpl      ( double *i_tDbl   );

  private:
  public:

           CbV *HCB_AnBulkVoid;    // PageAnBulk
           CbV *HCB_AnSineVoid;    // PageAnSine
           CbV *HCB_AnSineHasData; // PageAnSine

           CbV *HCB_MainReTitle;   // WinMain
           CbV *HCB_MainStCmpl;    // WinMain
           CbV *HCB_MainStWork;    // WinMain

           CbV *HCB_SigWrChg;      // PageFileWr

  private:
  public:

  private:
    static CtlMsgDspch          *ctMd;
};

#endif // __CTL_MSG_DSPCH_HPP_
