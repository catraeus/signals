// $Id: CtlOsVrt.cpp 497 2019-08-17 20:46:44Z duncang $

//=================================================================================================
// Original File Name : CtlOsVrt.cpp
// Original Author    : duncang
// Creation Date      : 2017-01-24T01:42:55,212117768+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================


#include "CtlOsVrt.hpp"
#include <stdio.h>
#include "../../Ctl/CtlMsgDspch.hpp"

CtlOsVrt *CtlOsVrt::ctOsVrt = NULL;

          CtlOsVrt::CtlOsVrt       ( Signal *i_sig )
: parent  ( NULL  ) {
  BuildEnv  ( i_sig );
  BuildMain (       );
  BuildSetup(       );
  Connect   (       );
}

          CtlOsVrt::~CtlOsVrt      ( void ) {
}
CtlOsVrt *CtlOsVrt::GetInstance    ( Signal *i_sig ) {
  if(ctOsVrt == NULL)
    ctOsVrt = new CtlOsVrt(i_sig);
  return ctOsVrt;
}

void   CtlOsVrt::BuildEnv          ( Signal *i_sig ) {
  mdOs = MdlOs       :: GetInstance( i_sig );
  ctMd = CtlMsgDspch :: GetInstance(       );
  return;
}
void   CtlOsVrt::BuildMain         ( void                     ) {
  return;
}
void   CtlOsVrt::BuildSetup        ( void                     ) {
  for(uint i=0; i<COVK_MAX_CH; i++) {
    en[i] = true;
  }
  (col[0]).set_rgba(1.0, 1.0, 0.0, 1.0); // yellow
  (col[1]).set_rgba(0.0, 1.0, 1.0, 1.0); // cyan
  (col[2]).set_rgba(0.0, 1.0, 0.0, 1.0); // green
  (col[3]).set_rgba(1.0, 0.0, 1.0, 1.0); // magenta
  mdOs->SetVoltVscr(1.0);
  return;
}
void   CtlOsVrt::Connect       ( void                     ) {
  return;
}





bool   CtlOsVrt::OnColChange(GdkEventButton *e, int i_ch, Gtk::Window *i_p) {
  Gtk::ColorChooserDialog dialog("Please choose a color");
  if(i_p != NULL) dialog.set_transient_for(*i_p);
  //Get the previously selected color:
  dialog.set_rgba(col[i_ch]);

  const int result = dialog.run();

  switch(result) {
    case Gtk::RESPONSE_OK:
      fprintf(stdout, "COL."); fflush(stdout);
      col[i_ch]          = dialog.get_rgba();
      ctMd->MRD_OsNewColors();
      break;
    case Gtk::RESPONSE_CANCEL:
      break;
    default:
      break;
    }

  return false;
  }

void   CtlOsVrt::SetVoltVscr(double i_dd) {
  mdOs->SetVoltVscr(i_dd);
  ctMd->MRD_OsVrtNumerics();
  return;
}
