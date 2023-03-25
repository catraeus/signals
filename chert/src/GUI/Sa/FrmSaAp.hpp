// $Id: FrmSaAp.hpp 491 2019-06-15 23:52:25Z duncang $

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

#ifndef __FRM_SA_AP_HPP_
#define __FRM_SA_AP_HPP_

#include <gtkmm.h>
#include <caes/CaesApodia.hpp>

#include "../../Ctl/CtlMsgDspch.hpp"


class FrmSaAp: public Gtk::Frame {
  public:
                    FrmSaAp          ( void );
    virtual        ~FrmSaAp          ( void );
  private:
            void    BuildEnv       ( void );
            void    BuildMain      ( void );
            void    BuildSetup     ( void );
            void    Connect        ( void );

            void    OnShape        ( void );
            void    ChangedAlpha   ( void );
            void    ExecuteChange  ( void );
            bool    AlphaSigFocOut ( GdkEventFocus* event);
            void    AlphaSigAct    ( void );
  private:
  public:
//    CbV *CbSomethingChanged;
  protected:
    //====================
    // Spec row
    Gtk::Box             hbxMain;
    Gtk::ComboBoxText   *cbxShape;
    Gtk::Label          *lblAlpha;
    Gtk::Entry          *txtAlpha;

    //====================
    // Vector text box

  private:
//    CtlOsHor            *ctOsHor;
//    Signal              *sig;
    Apodia              *apod;

    CtlMsgDspch         *ctMd;
  };

#endif // __FRM_SA_AP_HPP_
