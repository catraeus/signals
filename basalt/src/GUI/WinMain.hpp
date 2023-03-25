
// $Id: WinMain.hpp 682 2022-11-28 04:02:44Z duncang $

//=================================================================================================
// Original File Name : WinMain.hpp
// Original Author    : duncang
// Creation Date      : Dec 11, 2010
// Copyright          : Copyright © 2010-2012 by Catraeus and Duncan Gray
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

#include "Arb/CtlArb.hpp"
#include "Arb/Readout.hpp"
#include "Frames/CtlPhy.hpp"
#include "Frames/CtlFile.hpp"
#include "Frames/CtlSweep.hpp"
#include "WinAbout.hpp"

#include <caes/Alsa/AlsaStreamOut.hpp>
#include <caes/AudioFile/Signal.hpp>
#include <caes/AudioFile/WaveFiler.hpp>
#include <caes/CaesCallBack.hpp>


class WinMain: public Gtk::Window {
  public:
	                WinMain(Signal *i_sig);
    virtual      ~WinMain();

  protected:
    virtual void  on_hide(void);
            void  OnQuit(void);
            void  OnHelpAbout(void);

  private:
            void  BuildMenus(void);

  public:
  protected:
    Gtk::VBox        vbx_Main;
    Gtk::Notebook    ntbk_Ctl;

    CtlPhy          *vcAlsaFacility;  // derived from a Gtk::Frame.
    CtlFile         *vcWaveFile;      // derived from a Gtk::Frame.
    CtlSweep        *vcSweep;         // derived from a Gtk::Frame.
    CtlArb          *vcGenerator;     // derived from a Gtk::VBox.
    Gtk::Statusbar  *stb_Main;

  private:
    //==============================================
    // Basics
    CfgEnv          *ce;
    CfgStrings      *cs;
    CfgParticles    *cp;

    //==============================================
    // Windows

    //==============================================
    // Alsa Facilities
    Alsa          *theAlsa;

    //==============================================
    // Alsa Stream
    AlsaStreamOut *mcAlsaStream;
    pthread_t      portThreadTx;
    WaveFiler     *twf;
    Signal        *sig;

    //==============================================
    // Instrument Setup (Whole Screen)
    Gtk::HBox          hbx_Inst;


    //==============================================
    // Control Structure
    Gtk::MenuBar    *mbar_Main;

    Gtk::Menu       *menu_MainFile;
    Gtk::Menu       *menu_MainConfig;
    Gtk::Menu       *menu_MainHelp;

    Gtk::MenuItem   *mitm_MainFile;
    Gtk::MenuItem   *mitm_MainFileOpen;
    Gtk::MenuItem   *mitm_MainFileQuit;
    Gtk::MenuItem   *mitm_MainConfig;
    Gtk::MenuItem   *mitm_MainConfigCard;
    Gtk::MenuItem   *mitm_MainHelp;
    Gtk::MenuItem   *mitm_MainHelpAbout;

    Gtk::Toolbar    *tbar_Main;
    Gtk::ToolButton *tbtn_Quit;
    Gtk::ToolButton *tbtn_HelpAbout;


    Gtk::Statusbar *sbar_Main;


    int dummy;
  };

#endif // __WINMAIN_HPP_
