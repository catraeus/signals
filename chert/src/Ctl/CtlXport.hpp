// $Id: CtlXport.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : CtlXport.hpp
// Original Author    : duncang
// Creation Date      : 2016-12-26T23:14:46,862519570+00:00
// Copyright          : Copyright © 2016 by Catraeus and Duncan Gray
//
//
//=================================================================================================

/*! \brief

 Transport Controller.

 Created by int main();
 Useable by close to all - so may objects need to know what the transport is doing.
 Must be only one in the world, globality is not a problem.

 */

#ifndef __CTL_XPORT_HPP_
#define __CTL_XPORT_HPP_
#include <gtkmm.h>
#include <sigc++/sigc++.h>

#include <caes/CaesTypes.hpp>
#include <caes/CaesCallBack.hpp>
#include <caes/AudioFile/Signal.hpp>


#include "../Ctl/Os/CtlOsHor.hpp"
#include "../Mdl/MdlOs.hpp"

#include "CtlMsgDspch.hpp"
#include "CtlRsmp.hpp"

class CtlXport {
//==== Enums, Types, Structs, Unions ==============================================================
  private:
  public:
    enum eAct {
      XA_FIRST = 0x01,
      XA_PREV  = 0x02,
      XA_STOP  = 0x04,
      XA_START = 0x08,
      XA_NEXT  = 0x10,
      XA_LAST  = 0x20,
      XA_WHOLE = 0x40,
      XA_NONE  = 0x80
      };
//==== Methods ====================================================================================
//__ Administrivia
  private:
                              CtlXport      ( Signal *i_sig );  // Singleton Pattern
    virtual                  ~CtlXport      ( void          );  // Singleton Pattern
  public:
    static CtlXport          *GetInstance   ( Signal *i_sig );  // Singleton Pattern
           void               SetParentWin  ( Gtk::Window *i_parentWin ) {parentWin = i_parentWin; return;};
    //__ Events
  private:
           void               BuildEnv      ( void   );
           void               BuildSetup    ( void   );
           void               Connect       ( void   );
           CbT<CtlXport>     *MRU_XpStop;
           CbT<CtlXport>     *MRU_RshTime;
           bool               OnRshTime     ( void *i_d );
  public:

           bool               OnFirst       ( void *i_dummy);
           bool               OnPrev        ( void  *i_dummy );
           bool               OnStop        ( void  *i_dummy );
           bool               OnStart       ( void  *i_dummy );
           bool               OnNext        ( void  *i_dummy );
           bool               OnLast        ( void  *i_dummy );
           bool               OnWhole       ( void  *i_dummy );
           void               ButExtro      ( void           );
           void               KillButtons   ( void ) {buttonKill = true;  return;};
           void               LiveButtons   ( void ) {buttonKill = false; return;};

           bool               OnChangeT     ( GdkEventButton *i_event);
           bool               OnChangeN     ( GdkEventButton *i_event);
           void               OnTimeSlide   ( double          i_scalePos);


  private:
           bool               OnXpDataHit   ( void );
//==== Fields =====================================================================================
  private:
//__ Operational
  public:
           bool               running;
           bool               lastRunning;
           bool               hitByButton;
           bool               buttonKill;
           uint               buttonMask;
  public:
//__ Connections
  private:
           sigc::connection   tt_DrawItNow;
    static CtlXport          *ctXp;        // Singleton Pattern

           CtlMsgDspch       *ctMd;
           CtlRsmp           *ctRsmp;
           CtlOsHor          *ctOsHor;
           MdlOs             *mdOs;

           Signal            *sig;

           Gtk::Window       *parentWin;
  public:
};

#endif // ==CTL_XPORT_HPP_
