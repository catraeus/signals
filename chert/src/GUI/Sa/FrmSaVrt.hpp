// $Id: FrmSaVrt.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : FrmSaVrt.hpp
// Original Author    : duncang
// Creation Date      : Oct 23, 2013
// Copyright          : Copyright © 2013 - 2017 by Catraeus and Duncan Gray
//
// Description        :
//   Do SpecAn Vertical Things for the user
//
//=================================================================================================

#ifndef __FRM_SA_VRT_HPP_
#define __FRM_SA_VRT_HPP_

#include <gtkmm.h>

#include <caes/AudioFile/Signal.hpp>

#include "../../Ctl/Sa/CtlSaVrt.hpp"
#include "../../Mdl/MdlSa.hpp"
#include "../../Ctl/CtlMsgDspch.hpp"

class FrmSaVrt: public Gtk::Frame {
  public:
                    FrmSaVrt       ( Signal *i_sig );
    virtual        ~FrmSaVrt       ( void          );
  private:
            void    BuildEnv       ( Signal *i_sig );
            void    BuildGrid      ( void          );
            void    BuildMain      ( void          );
            void    BuildSetup     ( void          );
            void    InterConnect   ( void          );
            void    IntraConnect   ( void          );

            void    OnLogLin       ( void          );
            void    OnBasis        ( void          );
            bool    OnVoltTop      ( GdkEventFocus* gdk_event);
  public:
  private:

    Gtk::Box              vbxCtlVert;

    Gtk::Box              hbxSpan;
    Gtk::ComboBoxText    *cbxBasis;
    Gtk::Entry            etxSpanTop;
    Gtk::Box              hbxScale;
    Gtk::CheckButton      btLog;

    Gtk::Grid             grdVert;
    Gtk::RadioButtonGroup grpRbVertCh;
    Gtk::EventBox         eb[4];
    Gtk::RadioButton      rb[4];
    Gtk::Label            lb[4];
    Gtk::CheckButton      cb[4];


//=================================================
    CtlSaVrt             *ctSaVrt;
    MdlSa                *mdSa;

    bool                  rshHoldOff;

    CtlMsgDspch          *ctMd;
    CbT<FrmSaVrt>        *MRU_SaVrtRshAll;
    bool                  SaVrtRshAll( void *i_d );

  };

#endif // __FRM_SA_VRT_HPP_
