
// $Id: WinMain.hpp 763 2023-03-25 01:24:59Z duncang $

//=================================================================================================
// Original File Name : WinMain.hpp
// Original Author    : duncang
// Creation Date      : Jun 1, 2012
// Copyright          : Copyright © 2012 by Catraeus and Duncan Gray
//
// Description        :
//    Pretty self descriptive, eh!?
//
//=================================================================================================

#ifndef __WIN_MAIN_HPP_
#define __WIN_MAIN_HPP_

#include <gtkmm.h>

#include <caes/CaesTypes.hpp>
#include <caes/CaesCallBack.hpp>
#include <caes/AudioFile/Signal.hpp>
#include <caes/AudioFile/WaveFiler.hpp>

#include "../Cfg/CfgEnv.hpp"
#include "../Cfg/CfgParticles.hpp"
#include "../Cfg/CfgStrings.hpp"

#include "../Ctl/CtlMsgDspch.hpp"

#include "PageFileRd.hpp"


class WinMain: public Gtk::Window {
  public:
                    WinMain           ( void );
    virtual        ~WinMain           ( void );
            void    OnFileSave        ( void );
            void    MenuMainHelpAbout ( void );
  protected:
            void    OnHelpAbout       ( void );
            void    OnQuit            ( void );
    virtual void    on_hide           ( void );



  private:
            void    BuildEnv          ( void );
            void    BuildMenus        ( void );
            void    BuildDialogs      ( void );
            void    BuildMain         ( void );
            void    Connect           ( void );
            void    Setup             ( void );

            bool    HndlReTitle       ( void *i_ch);
            bool    HndlStatWork        ( void *i_ch);
            bool    HndlStatCmpl        ( void *i_ch);
  public:
  protected:
    Gtk::Box                  vbx_Main;
    Gtk::Notebook             ntbMain;
    Gtk::Frame                frmMain;
    Gtk::Box                  hbxMainInner;


    //==========================================================
    // Menu-like things
    Gtk::MenuBar     *mbarMain;

    Gtk::Menu        *menuMainFile;
    Gtk::MenuItem    *mitmMainFile;

    Gtk::MenuItem    *mitmMainFileInSel;

    Gtk::MenuItem    *mitmMainFileQuit;

    Gtk::Menu        *menuMainConfig;
    Gtk::MenuItem    *mitmMainConfig;

    Gtk::Menu        *menuMainHelp;
    Gtk::MenuItem    *mitmMainHelp;
    Gtk::MenuItem    *mitmMainHelpAbout;


    //==========================================================
    // Toolbar-like things
    Gtk::Toolbar     *tbarMain;
    Gtk::ToolButton  *tbtnAppQuit;



    //==========================================================
    // Some day we'll have a rich Statusbar experience
    Gtk::Statusbar *sbarMain;
    Gtk::Frame      frmSbarL;
    Gtk::Box        hbxSbarL;
    Gtk::Label      lblSbarL;
    Gtk::Frame      frmSbarC;
    Gtk::Box        hbxSbarC;
    Gtk::Label      lblSbarC;
    Gtk::Frame      frmSbarR;
    Gtk::Box        hbxSbarR;
    Gtk::Label      lblSbarR;

    //==========================================================
    // The pages that we have made
    PageFileRd               *theFilePageRd;

  private:
    //==========================================================
    // The important machinery
    CfgEnv                   *ce;
    CfgStrings               *cs;
    CfgParticles             *cp;

    Signal                   *sigRaw;

    WaveFiler                *twi;

    CbT<WinMain>             *HnCbReTitle;
    CbT<WinMain>             *HnCbStatWork;
    CbT<WinMain>             *HnCbStatCmpl;

    CtlMsgDspch              *ctMd;

};

#endif // __WIN_MAIN_HPP_
