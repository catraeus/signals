// $Id: FrmSaHor.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : FrmSaHor.hpp
// Original Author    : duncang
// Creation Date      : Oct 23, 2013
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#ifndef __FRM_SA_HOR_HPP_
#define __FRM_SA_HOR_HPP_

#include <gtkmm.h>


#include <caes/CaesTypes.hpp>
#include <caes/CaesCallBack.hpp>

#include <caes/AudioFile/Signal.hpp>

#include <caes/CaesApodia.hpp>

#include "../../Ctl/Sa/CtlSaHor.hpp"
#include "../../Mdl/MdlSa.hpp"
#include "../../Ctl/CtlMsgDspch.hpp"

#include "DrwSa.hpp"

/*! \brief Horizontal context of the spectrum analyzer.

There is a lot of stuff that has to be managed to make sense of the horizontal part of the signal presentation.


 */

class FrmSaHor : public Gtk::Frame {
  public:
                    FrmSaHor         ( Signal *i_sig );
    virtual        ~FrmSaHor         ( void      );
            void    SetDrwSa         ( DrwSa *v  );
  private:
            void    BuildEnv         ( void      );
            void    BuildMain        ( void      );
            void    BuildContnGrid   ( void      );
            void    BuildTimeGrid    ( void      );
            void    BuildSetup       ( void      );
            void    IntraConnect     ( void      );
            void    InterConnect     ( void      );

            void    OnLogLin         ( void      );

            bool    OnFaScale        (GdkEventKey   *i_v, Gtk::Entry *i_x);

            bool    SaHorRshAll      ( void *i_d );
  public:
  private:
// | Horizontal
    Gtk::Box           vbxCtlHoriz;
// | 0 Signal Frame Rate & Update Rate
    Gtk::Box           hbxCtlH0;
    Gtk::Label         lblFS;
    Gtk::Entry        *txtFS;
    Gtk::Label         lblTRfsh;
    Gtk::ComboBoxText *txtTRfsh;
    Gtk::CheckButton   btLog;
// | 2 Interpolation
    Gtk::Box           hbxTerp;
    Gtk::Label         lblTerp;
    Gtk::ComboBoxText *txtTerp;
// | 1 Continuity
    Gtk::Grid          grdHorizContn;
    Gtk::Label         lblFmin;
    Gtk::Entry         txtFmin;
    Gtk::Label         lblFmax;
    Gtk::Entry         txtFmax;
// | 3 Times and Frames per display unit
    Gtk::Grid          grdHorizNums;
    Gtk::Label         lblNtime;
    Gtk::Entry         txtNtime;
    Gtk::Label         lblDelFreq;
    Gtk::Entry         txtDelFreq;
    Gtk::Label         lblNfreq;
    Gtk::Entry         txtNfreq;


    Gtk::Label         lblHNBlank;
    Gtk::Label         lblHNDiv;
    Gtk::Label         lblHNScr;
    Gtk::Label         lblHNFrame;
    Gtk::Entry         txtHNsecPerScr;
    Gtk::Entry         txtHNfrmPerPxl;
    Gtk::Entry         txtHNfrmPerDiv;
    Gtk::Entry         txtHNfrmPerScr;

    CtlSaHor          *ctSaHor;
    MdlSa             *mdSa;
    DrwSa             *vwSaDrw;
    Signal            *sig;

    CtlMsgDspch       *ctMd;
    CbT<FrmSaHor>      *MRU_SaHorRshAll;
    bool                rshHoldOff;

  };

#endif // __FRM_SA_HOR_HPP_
