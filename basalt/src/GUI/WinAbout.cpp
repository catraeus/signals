
// $Id: WinAbout.cpp 7 2014-10-16 01:36:47Z duncang $

//=================================================================================================
// Original File Name : WinAbout.cpp
// Original Author    : duncang
// Creation Date      : Dec 11, 2010
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//
//=================================================================================================

#include "WinAbout.hpp"
#include "../../src/Cfg/CfgEnv.hpp"

#include <gtkmm/main.h>
#include <stdio.h>
#include <string.h>

//=================================================================================================
     WinAbout::WinAbout(CfgStrings *i_as, CfgParticles *i_tp) {
  as = i_as;
  tp = i_tp;


//-----------
  set_icon(tp->pxbf_xIconApp);
  set_title(as->s[as->ABOUT_TITLE]);
  set_copyright(as->s[as->ABOUT_COPYRIGHT]);
  set_version(as->s[as->ABOUT_VERSION]);
  set_modal(true);
  set_size_request(400, 300);

  set_logo(tp->pxbf_xLogoApp);
  show_all();
  return;
  }
     WinAbout::~WinAbout() {
  fprintf(stderr, "WinAbout destroyed\n");
  }

// Event Handlers
     //=================================================================================================
void WinAbout::on_hide() {
  Gtk::Window::on_hide(); // thus passing back up the food chain.
  return;
  }
//=================================================================================================
bool WinAbout::on_delete_event(GdkEventAny *event) {
  return false; // thus passing the delete back up the food chain.  Funny, it's different for life defining events.
  }

