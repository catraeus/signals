// $Id: FrmOsHor.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : FrmOsHor.hpp
// Original Author    : duncang
// Creation Date      : Oct 21, 2013
// Copyright          : Copyright © 2013 - 2017 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#ifndef __FRM_OS_HOR_HPP_
#define __FRM_OS_HOR_HPP_
#include <gtkmm.h>

#include <caes/CaesTypes.hpp>
#include <caes/CaesCallBack.hpp>
#include <caes/AudioFile/Signal.hpp>

#include "../../Ctl/Os/CtlOsHor.hpp"
#include "../../Ctl/CtlMsgDspch.hpp"

#include "../../Mdl/MdlOs.hpp"

class FrmOsHor : public Gtk::Frame {
  public:
  public:
                    FrmOsHor        ( Gtk::Window *i_p, Signal *i_sig );
    virtual        ~FrmOsHor        ( void );
  private:
            void    BuildEnv        ( void );
            void    BuildContnGrid  ( void );
            void    BuildTimeGrid   ( void );
            void    IntraConnect    ( void );
            void    InterConnect    ( void );
            void    BuildMain       ( void );

            bool    OsHorRshAll     ( void         *i_ddd          );

            void    OnTimeGrp       ( void );
            bool    OnTcScale       (GdkEventKey   *i_event, Gtk::Entry *i_txt);
  private:
  public:
// | Horizontal
    Gtk::Box            vbxCtlHoriz;
// | 0 Signal Frame Rate & Interpolation Method
    Gtk::Frame          frmCtlH0_Signal;
    Gtk::Box            hbxCtlH0_Signal;
    Gtk::Label          lblFrmVsec;
    Gtk::Entry          txtSmpVsec;
    Gtk::Label          lblTerp;   // Interpolation method ... smooth, skip etc.
    Gtk::ComboBoxText  *txtTerp;

// | 1 Time Hold
    Gtk::Frame          frmCtlH1_Hold;
    Gtk::Box            hbxCtlH1_Hold;
    Gtk::Box            vbxDummyHoldR;
    Gtk::Grid           grdHorizHold;

    Gtk::Box            vbxRbgScrSize;
    Gtk::RadioButton::Group rbgScrSize;
    Gtk::RadioButton*   rbScrDiv;
    Gtk::RadioButton*   rbScrScr;
    Gtk::Box            vbxRbgScroll;
    Gtk::RadioButton::Group rbgScroll;
    Gtk::RadioButton*   rbSrlRatio;
    Gtk::RadioButton*   rbSrlScrTime;
    Gtk::RadioButton*   rbSrlSrdTime;
    Gtk::Box            vbxRbgPlayback;
    Gtk::RadioButton::Group rbgPlayback;
    Gtk::RadioButton*   rbPbkRatio;
    Gtk::RadioButton*   rbPbkRshTim;
    Gtk::RadioButton*   rbPbkSrdTim;

// | 2 Playback (P) - scrolling (srl) and striding (srd) ratio numbers (rto) -- Continuity
    Gtk::Frame          frmCtlH2_Contn;
    Gtk::Box            hbxCtlH2_Contn;
    Gtk::Box            vbxDummyContnR;
    Gtk::Grid           grdHorizContn;
    //Column (C) labels
    Gtk::Label          lblCPrsh;
    Gtk::Label          lblCPpbkRto;
    Gtk::Label          lblCPsrd;
    Gtk::Label          lblCPsrlRto;
    Gtk::Label          lblCPscr;
    //Row (R) labels
    Gtk::Label          lblRPtim;
    Gtk::Label          lblRPsmp;
    Gtk::Label          lblRPrto;

// | 3 Numeric Time Scaling
    // Numeric Data
    Gtk::Frame          frmCtlH3_Numeric;
    Gtk::Box            hbxCtlH3_Numeric;
    Gtk::Box            vbxDummyNumericR;
    Gtk::Entry          txtTimPrsh;
    Gtk::Entry          txtTimPsrd;
    Gtk::Entry          txtTimPscr;

    Gtk::Entry          txtSmpPrsh;
    Gtk::Entry          txtSmpPsrd;
    Gtk::Entry          txtSmpPscr;

    Gtk::Entry          txtPbkRto;
    Gtk::Entry          txtSrlRto;



// | 3 Times and Frames per display unit
    Gtk::Grid           grdCtlH3_Numeric;
    Gtk::Label          lblHNBlank;

    Gtk::Label          lblHNPxl;
    Gtk::Label          lblHNDiv;
    Gtk::Label          lblHNScr;

    Gtk::Label          lblHNSec;
    Gtk::Label          lblHNSmp;

    Gtk::Entry          txtTimVpxl;
    Gtk::Entry          txtTimVdiv;
    Gtk::Entry          txtTimVscr;

    Gtk::Entry          txtSmpVpxl;
    Gtk::Entry          txtSmpVdiv;
    Gtk::Entry          txtSmpVscr;

    CtlOsHor           *ctOsHor;
    MdlOs              *mdOs;
    CtlMsgDspch        *ctMd;

    Gtk::Window        *parent;
    Signal             *sig;

    CbT<FrmOsHor>      *MRU_OsHorRshAll;
  public:
    sigc::connection   cnTxRshTim;
  private:
  };

#endif // __FRM_OS_HOR_HPP_
