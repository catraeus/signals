
// $Id: WinMain.hpp 572 2021-06-21 00:42:24Z duncang $

//=================================================================================================
// Original File Name : WinMain.hpp
// Original Author    : duncang
// Creation Date      : 2013-08-15
// Copyright          : Copyright © 2013 - 2017 by Catraeus and Duncan Gray
//
// Description        :
//    Pretty self descriptive, eh!?
//
//=================================================================================================

#ifndef __WINMAIN_HPP_
#define __WINMAIN_HPP_

#include <gtkmm.h>



#include "../Cfg/CfgEnv.hpp"

#include "../Cfg/CfgParticles.hpp"
#include "../Cfg/CfgStrings.hpp"

#include "../Ctl/CtlWave.hpp"

#include <caes/AudioFile/Signal.hpp>
#include <caes/AudioFile/RiffMgr.hpp>
#include <caes/AudioFile/WaveFiler.hpp>
#include <caes/AudioFile/AudioFiler.hpp>
#include <caes/CaesCallBack.hpp>
#include "PageFileWr.hpp"
#include "PageRemez.hpp"


class WinMain: public Gtk::Window {
  public:
	                   WinMain            ( Signal *i_sig );
    virtual         ~WinMain            ( void );
  protected:
    virtual void     on_hide            ( void );
            void     OnQuit             ( void );
            void     OnHelpAbout        ( void );

  private:
            void     BuildEnv           ( void );
            void     BuildMain          ( void );
            void     BuildMenus         ( void );
            void     Connect            ( void );
            void     Setup              ( void );

  public:
  protected:
  private:
    //==============================================
    // Basics
    CfgEnv           *ce;
    CfgStrings       *cs;
    CfgParticles     *cp;
    //==============================================


    //==============================================
    // View
    // The first thing to go into the window  Contains menu, forms, status bar
    Gtk::Box          vbxWhole;
    Gtk::Box          hbxFormWrap;
    // Menu
    Gtk::MenuBar     *mbar_Main;

    Gtk::Menu        *menu_MainFile;
    Gtk::Menu        *menu_MainHelp;

    Gtk::MenuItem    *mitm_MainFile;
    Gtk::MenuItem    *mitm_MainFileQuit;
    Gtk::MenuItem    *mitm_MainHelp;
    Gtk::MenuItem    *mitm_MainHelpAbout;

    // Toolbar
    Gtk::Toolbar     *tbarMain;
    Gtk::ToolButton  *tbtnQuit;
    Gtk::ToolButton  *tbtnFileSave;
    // Containers, fillers and such
    Gtk::Frame       *frmForms;
    Gtk::Box          vbx_FillLeft;
    Gtk::Box          hbxForms;
    Gtk::Box          vbx_Holder;
    Gtk::Box          vbx_FillRight;
    Gtk::Box          hbx_FillTop;
    Gtk::Box          hbx_FillBot;
    // Overall Signal Choices
    // The Devil's Details
    Gtk::Notebook    *ntbk_Main;

    // At the bottom
    Gtk::Separator    sep_StatBar;
    Gtk::Statusbar   *stb_Main;

    WaveFiler        *two;
    Signal           *sig;
    CtlWave          *ctWave;

    PageFileWr       *vwFile;
    PageRemez         *vwRemez;

    bool    holdOffSigSel;
    int     dummy;

  };

#endif // __WINMAIN_HPP_
