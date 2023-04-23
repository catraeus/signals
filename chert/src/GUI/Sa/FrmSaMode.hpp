// $Id: FrmSaMode.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : UtilApodFunc.hpp
// Original Author    : duncang
// Creation Date      : Aug 28, 2013
// Copyright          : Copyright © 2013 - 2017 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#ifndef __FRM_MODE_HPP_
#define __FRM_MODE_HPP_

#include <gtkmm.h>

#include <caes/AudioFile/Signal.hpp>

#include "../../Ctl/CtlMsgDspch.hpp"

class FrmSaMode: public Gtk::Frame {
  public:
                    FrmSaMode      ( Signal *i_sig );
    virtual        ~FrmSaMode      ( void );
  private:
            void    BuildEnv       ( Signal *i_sig );
            void    BuildMain      ( void );
            void    BuildSetup     ( void );
            void    Connect        ( void );

            void    ChangedMode    ( void );
            void    MRU_ModeRsh    ( void );
  private:
  public:
  protected:
    //====================
    // Spec row
    Gtk::Box                 hbxMain;
    Gtk::Box                 vbxSaMode;
    Gtk::RadioButton::Group  rbgSaMode;
    Gtk::RadioButton*        rbModeTrack;
    Gtk::RadioButton*        rbModeAvg;

    //====================
    // Vector text box

  private:

    CtlMsgDspch         *ctMd;
  };

#endif // __FRM_MODE_HPP_
