// $Id: WinSa.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : WinSa.hpp
// Original Author    : duncang
// Creation Date      : Oct 14, 2012
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================


#ifndef __WIN_SA_HPP_
#define __WIN_SA_HPP_

#include <gtkmm.h>

#include <caes/CaesCallBack.hpp>
#include <caes/AudioFile/Signal.hpp>

#include "../../Cfg/CfgEnv.hpp"
#include "../../Cfg/CfgParticles.hpp"
#include "../../Cfg/CfgStrings.hpp"

#include "../../Ctl/CtlMsgDspch.hpp"


#include "../../Mdl/MdlSa.hpp"

#include "DrwSa.hpp"

#include "FrmSaAxisH.hpp"
#include "FrmSaAxisV.hpp"

#include "FrmSaMode.hpp"
#include "FrmSaHor.hpp"
#include "FrmSaVrt.hpp"
#include "FrmSaAp.hpp"

class WinSa: public Gtk::Window {
  public:
    enum eConst {
      EWSC_MAX_HORIZ_WIDTH = 4192,
      EWSC_MAX_CH          =    2
      };
  public:
                    WinSa            ( Signal *i_sig );
    virtual        ~WinSa            ( void      );
  protected:
    virtual void    on_hide          ( void                          );
    virtual void    on_show          ( void                          );
    virtual void    on_size_allocate ( Gtk::Allocation& i_allocation );
  private:
            void    BuildEnv         ( void      );
            void    BuildSubs        ( Signal *i_sig );
            void    BuildMain        ( void      );

            void    Connect          ( void      );
            void    ReTitle          ( void      );
            bool    OnReSize         ( void *i_N );
            bool    OnReSkin         ( void *i_d );
            bool    OnSaStatMsg      ( void *i_s );
  protected:
  private:
//==== The Main Window Envelope
    Gtk::Frame         frmMain;
    Gtk::Box           vbxMain;
    Gtk::Box           hbxMain;

//==== SpecAn
//==== SpecAn Draw Screen
    DrwSa             *vwDrwSa;
    Gtk::Box           hbxScrs;
    Gtk::Box           vbxScrs;

    Gtk::Box           hbxBfDdTop;      // Sliver above vwDrwSa to allow vAxis to center its labels on graticules
    Gtk::Box           hbxBfDdBot;      // Sliver below vwDrwSa to allow vAxis to center its labels on graticules

    FrmSaAxisV        *frmAxisV;        // Contains the vbxScrs that has all the other junk ... AND ... the vAxis.

    FrmSaAxisH        *frmAxisH;

    Gtk::Box           hbxBfDdLeft;      // Sliver left  of vwDrwOs to allow hAxis to center its labels on graticules
    Gtk::Box           hbxBfDdRite;      // Sliver right of vwDrwOs to allow hAxis to center its labels on graticules
    Gtk::Box           hbxVwDs;          // To allow left.right slivers

//==== Controls
    Gtk::Notebook     *nbkControls;
    Gtk::Box           vbxMode;
    Gtk::Box           vbxModeFill;
    Gtk::Box           vbxCtlHoriz;
    Gtk::Box           vbxHorFill;
    Gtk::Box           vbxCtlVert;
    Gtk::Box           vbxVrtFill;
    Gtk::Box           vbxCtlApod;
    Gtk::Box           vbxApFill;
    FrmSaMode         *vwSaMode;
    FrmSaHor          *vwSaHor;
    FrmSaVrt          *vwSaVrt;
    FrmSaAp           *vwSaApod;




//==== Status Bar all the way at the bottom
    Gtk::Frame         frmStbMain;
    Gtk::Statusbar    *stbMain;

// Analyzer
  private:
    MdlSa             *mdSa;

// Environment
  private:
    CfgEnv          *ce;
    CfgStrings      *cs;
    CfgParticles    *cp;

// ====  Message System
  private:
    CtlMsgDspch     *ctMd;
    CbT<WinSa>      *CbSaReSkin;
    CbT<WinSa>      *CbOnReSize;
    CbT<WinSa>      *MRU_Grab;
    CbT<WinSa>      *MRU_SaStatMsg;
  public:
    CbV             *MSU_SaWin;
  };

#endif /* __WIN_SA_HPP_ */
