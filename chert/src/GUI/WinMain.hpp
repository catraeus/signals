
// $Id: WinMain.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : WinMain.hpp
// Original Author    : duncang
// Creation Date      : March 23, 2012
// Copyright          : Copyright © 2012 by Catraeus and Duncan Gray
//
/* Description       :

There are buttons and other entry widgets.
There are labels and other display widgets.
Some of the silly buttons do display autonomously, so we need to muck with them to make it behave.
Then there is the real reason we made this beast, the gigantic engine that:

Takes a time-domain input
Shuttles through it, very precisely.
Displays it directly ( The Scope )
Analyzes it : Frequency Domain, mostly, to present in a Spectrum Analyzer (SpecAn for the uninitiated)

There are 3 panels:
Main:   File Handling, Time Domain Transport, Physical Info, Scope & SpecAn show/hide.
Scope:  Show the Time Domain representation.
              Grab Functionality, View Scaling, Vertical and Time Measurements and Summaries.
SpecAn: Take that grabbed stuff, transmogrify it to freq domain and present it.
Histo:  Take that grabbed stuff, do stats and show it.


*/
//
//=================================================================================================

#ifndef __WIN_MAIN_HPP_
#define __WIN_MAIN_HPP_

#include <gtkmm.h>

#include <caes/CaesTypes.hpp>
#include <caes/CaesCallBack.hpp>
#include <caes/AudioFile/Signal.hpp>

#include "../Ctl/CtlMsgDspch.hpp"

#include "../Cfg/CfgEnv.hpp"
#include "../Cfg/CfgParticles.hpp"
#include "../Cfg/CfgStrings.hpp"

#include "WinXport.hpp"
#include "FrmFile.hpp"

#include "Os/WinOs.hpp"
#include "Sa/WinSa.hpp"
/*! \brief The highest level of all windows.

int main(int char **) is a legacy that hardly has anything.  The main window really starts and stops everything.
Only the CfgParticles, CfgEnv and CfgStrings are instantiated in main() because they need the more convenient access
to the startup parameters of the system.


*/

class WinMain : public Gtk::Window {
  public:
                  WinMain        ( Signal *i_sig );
    virtual      ~WinMain        ( void          );
            void  OnQuit         ( void          );
            void  OnScopeButn    ( void          );
            bool  HandleOsWin    ( void *i_tt    );
            void  OnSpecAnButn   ( void          );
            bool  HandleSaWin    ( void *i_tt    );
            bool  OnGrab         ( void *i_iii   );
            void  OnHelpAbout    ( void          );
            void  OnAnalyze      ( void          );
  protected:
  private:
            void  BuildEnv       ( Signal *i_sig );
            void  BuildMenus     ( void          );
            void  BuildMain      ( void          );
            void  Connect        ( void          );

  public:
    WinXport            *vwXprt;
    FrmFile             *vwFile;
    WinOs               *vwOsw;
    WinSa               *vwSaw;
  protected:
  private:
    Gtk::Box             vbxMainOuter;
    Gtk::Box             hbox_Main;
    Gtk::Box             vbxMainSub;
    Gtk::Box             vbxAnaVis;


    Gtk::ToggleButton   *tbtScope;
    Gtk::ToggleButton   *tbtSpecAn;

    CbT<WinMain>        *MRU_OsWin;
    CbT<WinMain>        *MRU_SaWin;

    //==============================================
    // Basics
    CfgEnv              *ce;
    CfgStrings          *cs;
    CfgParticles        *cp;


    //==============================================
    // MVC
    CtlMsgDspch         *ctMd;



    //==============================================
    // Control Structure
    Gtk::MenuBar    *mbar_Main;

    Gtk::Menu       *menu_MainFile;
    Gtk::Menu       *menu_MainHelp;

    Gtk::MenuItem   *mitm_MainFile;
    Gtk::MenuItem   *mitm_MainFileOpen;
    Gtk::MenuItem   *mitm_MainFileQuit;
    Gtk::MenuItem   *mitm_MainHelp;
    Gtk::MenuItem   *mitm_MainHelpAbout;

    Gtk::Toolbar    *tbar_Main;
    Gtk::ToolButton *tbtn_Quit;
    Gtk::ToolButton *tbtn_SpecAn;
    Gtk::ToolButton *tbtn_Scope;
    Gtk::ToolButton *tbtn_HelpAbout;

    Signal         *sig;

    bool            holdoffOsShowing; // To keep track of window openness
    bool            holdoffSaShowing; // To keep track of window openness


  };

#endif // #ifdef __WIN_MAIN_HPP_
