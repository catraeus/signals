
// $Id: _main.cpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : _main.cpp -- for project beryl
// Original Author    : duncang
// Creation Date      : 2013-08-15
// Copyright          : Copyright © 2013 - 2017 by Catraeus and Duncan Gray
//
// Description        :
//     beryl produces a wave file that contains an apodization windowing function.
//
/*

 1.) just plain.  To investigate other tools with pure ... noise, sine, apodization, Remez shapes
 * multiply
 + add
 # convolve
 2.) sine * apod  = band-pass filter
 3.) sine * noise = interesting, maybe. Strangely correlated noise ! ?
 4.) sine * Remez = interesting, probably not, since Remez can do bandpass already
 5.) sine + apod  = not very iteresting
 6.) sine + noise = very interesting for signal recognition algorithm research.
 7.) sine + Remez = not very interesting
 8.) sine # apod  = not very interesting
 9.) sine # noise = fundimentally not interesting, but it would be worth checking
10.) sine # Remez = not very interesting
11.) apod + noise = not very interesting
12.) apod + Remez = not very interesting
13.) apod * noise = fundimentally not interesting, but it would be worth checking Time Constrained Noise ! ?
14.) apod * Remez = not very interesting
15.) apod # noise = DC baseband noise

*/
//=================================================================================================

#include <gtkmm.h>
#include <string.h>

#include <caes/AudioFile/Signal.hpp>



#include "Cfg/CfgEnv.hpp"
#include "Cfg/CfgStrings.hpp"
#include "Cfg/CfgParticles.hpp"



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
  MainConts m;
  WinMain  *theWinMain;

  setlocale(LC_NUMERIC, "");
  gtk_init(&i_argc, &i_argv);

  m.sig      = new Signal                             (                          );


  m.ce       =     CfgEnv             :: GetInstance  ( i_argc, i_argv, i_envp   );  // Dangerous Singleton  Be very glad it is done here in main before anything else.
  m.cs       =     CfgStrings         :: GetInstance  ( "English"                );  // Dangerous Singleton  Be very glad it is done here in main before anything else.
  m.ss       = new Glib               :: ustring      ( m.ce->appId              );
  auto app   =     Gtk::Application   :: create       ( i_argc, i_argv, *m.ss, Gio::APPLICATION_FLAGS_NONE);
  m.cp       =     CfgParticles       :: GetInstance  (                          ); // has GtkPixmaps so it has to be done after the app is built (which initializes the Gdk framework.)
  theWinMain = new WinMain                            ( m.sig                    );

  if(!Glib::thread_supported())     Glib::thread_init(0);

  int    theResult = app->run(*theWinMain);
  delete theWinMain;

  return theResult;
  }

