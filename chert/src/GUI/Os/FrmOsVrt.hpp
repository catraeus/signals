
//=================================================================================================
// Original File Name : FrmOsVrt.hpp
// Original Author    : duncang
// Creation Date      : Oct 16, 2013
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#ifndef __FRM_OS_VRT__HPP_
#define __FRM_OS_VRT__HPP_

#include <gtkmm.h>

#include <caes/CaesCallBack.hpp>
#include <caes/AudioFile/Signal.hpp>

#include "../../Mdl/MdlOs.hpp"
#include "../../Ctl/CtlMsgDspch.hpp"
#include "../../Ctl/Os/CtlOsVrt.hpp"


class FrmOsVrt: public Gtk::Frame {
  public:
                    FrmOsVrt       ( Gtk::Window *i_parent, Signal *i_sig);
    virtual        ~FrmOsVrt       ( void   );
            bool    ReSkin         ( void * );
  private:
            void    BuildEnv       ( Signal *i_sig );
            void    BuildChannels  ( void   );
            void    BuildMain      ( void   );
            void    IntraConnect   ( void   );
            void    InterConnect   ( void   );

            bool    OnVoltVscr     ( GdkEventFocus* gdk_event   );
            void    OnChEn         ( int  i_ch );

            bool    OnRshAll       ( void *i_d );
  public:
    Gtk::Window          *parent;
    Gtk::Box              hbxOsVert;

    Gtk::Box              vbxCtlVert;
    Gtk::SpinButton      *etxChan;
    Gtk::Box              hbxChan;
    Gtk::Box              hbxChanFill;
    Glib::RefPtr<
      Gtk::Adjustment>    adjChan;

    Gtk::Grid             grdVert;
    Gtk::RadioButtonGroup grpRbVertCh;
    Gtk::EventBox         cb[CtlOsVrt::COVK_MAX_CH];
    Gtk::RadioButton      rb[CtlOsVrt::COVK_MAX_CH];
    Gtk::Label            lb[CtlOsVrt::COVK_MAX_CH];
    Gtk::CheckButton      eb[CtlOsVrt::COVK_MAX_CH];

    Gtk::Box              vbxVoltGrid;
    Gtk::Label            lblVoltVscr;
    Gtk::Entry            txtVoltVscr;

    CtlOsVrt             *ctOsVrt;
    MdlOs                *mdOs;
    CtlMsgDspch          *ctMd;
    CbT<FrmOsVrt>        *MRU_OsVrtReSkin;
    CbT<FrmOsVrt>        *MRU_RshAll;
  };

#endif // __FRM_OS_VRT__HPP_
