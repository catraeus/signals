
//============================================================================
// Original Name      : _main.cpp
// Original Author    : duncang
// Creation Date      : 2012-03-18
// Copyright          : Copyright © 2012 - 2023 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include <gtkmm.h>
#include <stdio.h>
#include <string.h>

#include <caes/AudioFile/Signal.hpp>



#include "Cfg/CfgEnv.hpp"
#include "Cfg/CfgStrings.hpp"
#include "Cfg/CfgParticles.hpp"



#include "GUI/WinMain.hpp"

class MainConts { // total BS to shut up the warning about setting but not using.
  public:
    CfgEnv         *ce;
    CfgStrings     *cs;
    Glib::ustring  *ss;
    CfgParticles   *cp;
};

//=================================================================================================
int main(int i_argc, char *i_argv[], char *i_envp[]) {
  MainConts      m;
  WinMain       *theWinMain;
  int            dd_argc; // WTF ?


  m.ce       =     CfgEnv             :: GetInstance  ( i_argc, i_argv, i_envp   );  // Dangerous Singleton  Be very glad it is done here in main before anything else.
  m.cs       =     CfgStrings         :: GetInstance  ( "English", m.ce->buildNo );  // Dangerous Singleton  Be very glad it is done here in main before anything else.

  m.ss       = new Glib               :: ustring      ( m.ce->appId              );
  dd_argc    = 1;
  auto app   =     Gtk::Application   :: create       ( dd_argc, i_argv, *(m.ss), Gio::APPLICATION_FLAGS_NONE);
  m.cp       =     CfgParticles       :: GetInstance  (                          );  // CfgParticles has GdkPixbufs in it so it has to go after app is created.
  theWinMain = new WinMain                            (                          );


  if(!Glib::thread_supported())     Glib::thread_init(0);

  int    theResult = app->run((Gtk::Window &)(*theWinMain));

  delete theWinMain;


  return theResult;
  }

