// $Id: FrmAp.hpp 392 2017-06-19 16:30:34Z duncang $

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

#ifndef __WIN_AP_HPP_
#define __WIN_AP_HPP_

#include <gtkmm.h>
#include <caes/CaesApodia.hpp>

#include "../../Ctl/CtlMsgDspch.hpp"


class FrmAp: public Gtk::Frame {
  public:
                    FrmAp          ( void );
    virtual        ~FrmAp          ( void );
  private:
            void    BuildEnv       ( void );
            void    BuildMain      ( void );
            void    BuildSetup     ( void );
            void    Connect        ( void );

            void    ChangedShape   ( void );
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

#endif // __UTLAPODFUNC_HPP_
