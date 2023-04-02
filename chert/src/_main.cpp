
// $Id: _main.cpp 697 2023-01-08 21:38:54Z duncang $

//=================================================================================================
// Original File Name : _main.cpp -- for project chert
// Original Author    : duncang
// Creation Date      : 2011-12-17
// Copyright          : Copyright © 2011-2017 by Catraeus and Duncan Gray
//
// Description        :
//     chert is an oscilloscope/specan combo to shuttle through a wave file.
//
//=================================================================================================

#include <gtkmm.h>
#include <stdio.h>
#include <string.h>

#include <caes/AudioFile/Signal.hpp>

#include "Ctl/CtlMsgDspch.hpp"

#include "Cfg/CfgSettings.hpp"
#include "Cfg/CfgEnv.hpp"
#include "Cfg/CfgStrings.hpp"
#include "Cfg/CfgParticles.hpp"

#include "Ctl/Os/CtlOsHor.hpp"

#include "GUI/WinMain.hpp"

class MainConts { // total BS to shut up the warning about setting but not using.
  public:
    Signal         *sig;
    CtlOsHor       *ctOsHor;
    CtlMsgDspch    *ctMh;
    CfgEnv         *ce;
    CfgSettings    *ct;
    CfgStrings     *cs;
    Glib::ustring  *ss;
    CfgParticles   *cp;
};

//=================================================================================================
int main(int i_argc, char *i_argv[], char *i_envp[]) {
  MainConts      m;
  WinMain       *theWinMain;
  int            dd_argc;


  m.sig      = new Signal                             (                          );
  m.ctOsHor  =     CtlOsHor           :: GetInstance  ( m.sig                    );
  m.ctMh     =     CtlMsgDspch        :: GetInstance  (                          );
  m.ce       =     CfgEnv             :: GetInstance  ( i_argc, i_argv, i_envp   );  // Dangerous Singleton  Be very glad it is done here in main before anything else.
  if(m.ce->GetFatal()) {
    fprintf(stderr, "FATAL at startup after CfgEnv.\n"); fflush(stderr);
    return -1;
  }
  m.ct       =     CfgSettings        :: GetInstance  (                          );
  m.cs       =     CfgStrings         :: GetInstance  ( "English", m.ce->buildNo );  // Dangerous Singleton  Be very glad it is done here in main before anything else.
  m.ss       = new Glib               :: ustring      ( m.ce->appId              );
  dd_argc    = 1;
  auto app   =     Gtk::Application   :: create       ( dd_argc, i_argv, *(m.ss), Gio::APPLICATION_FLAGS_NONE);
  m.cp       =     CfgParticles       :: GetInstance  (                          );  // CfgParticles has GdkPixbufs in it so it has to go after app is created.
  theWinMain = new WinMain                            ( m.sig                    );

  if(!Glib::thread_supported())     Glib::thread_init(0);

  int    theResult = app->run(*theWinMain);
  m.ce->CloseFileUser();

  delete theWinMain;


  return theResult;
}

