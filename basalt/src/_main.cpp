
// $Id: _main.cpp 693 2022-12-28 03:44:39Z duncang $

//=================================================================================================
// Original File Name : _main.cpp
// Original Author    : duncang
// Creation Date      : 2010-12-17
// Copyright          : Copyright © 2010 - 2022 by Catraeus and Duncan Gray
//
// Description        :
//    basalt is a signal generator.
//
//=================================================================================================

#include <gtkmm.h>
#include <stdio.h>
#include <string.h>



#include "Cfg/CfgEnv.hpp"
#include "Cfg/CfgStrings.hpp"
#include "Cfg/CfgParticles.hpp"

#include <caes/AudioFile/Signal.hpp>

#include "GUI/WinMain.hpp"

class MainConts { // total BS to shut up the warning about setting but not using.
  public:
    Signal         *sig;


    CfgEnv         *ce;
    CfgStrings     *cs;
    Glib::ustring  *ss;
    CfgParticles   *cp;
};

//=================================================================================================
int main(int i_argc, char *i_argv[], char *i_envp[]) {
  MainConts      m;
  WinMain       *theWinMain;


  setlocale(LC_NUMERIC, "");
  gtk_init(&i_argc, &i_argv);

  m.sig      = new Signal                             (                          );

  m.ce       =     CfgEnv             :: GetInstance  ( i_argc, i_argv, i_envp   );  // FIXME TODO WARNING MAGICK DANGER Dangerous Singleton  Be very glad it is done here in main before anything else.
  m.cs       =     CfgStrings         :: GetInstance  ( "English", m.ce->buildNo );  // Dangerous Singleton  Be very glad it is done here in main before anything else.
  m.ss       = new Glib               :: ustring      ( m.ce->appId              );
  auto app   =     Gtk::Application   :: create       ( i_argc, i_argv, *m.ss, Gio::APPLICATION_FLAGS_NONE);
  m.cp       =     CfgParticles       :: GetInstance  (                          );  // CfgParticles has GdkPixbufs in it so it has to go after app is created.
  theWinMain = new WinMain                            ( m.sig                    );

  if(!Glib::thread_supported())     Glib::thread_init(0);

  int    theResult = app->run(*theWinMain);

  delete theWinMain;


  return theResult;
  }

