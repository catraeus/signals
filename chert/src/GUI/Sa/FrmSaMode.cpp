// $Id: FrmSaMode.cpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : FrmSaMode.cpp
// Original Author    : duncang
// Creation Date      : Aug 28, 2013
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include <caes/CaesTypes.hpp>
#include <caes/CaesString.hpp>

#include "FrmSaMode.hpp"

     FrmSaMode::FrmSaMode(Signal *i_sig) {
  BuildEnv   ( i_sig );
  BuildSetup (       );
  BuildMain  (       );
  Connect    (       );
  }
     FrmSaMode::~FrmSaMode() {
  }

void FrmSaMode::BuildEnv (Signal *i_sig) {
  ctSaHor   = CtlSaHor    ::GetInstance( i_sig );
  ctMd      = CtlMsgDspch ::GetInstance(       );
  return;
}
void FrmSaMode::BuildSetup(void) {
  return;
}
void FrmSaMode::BuildMain(void) {
  this       ->set_label         ("Spectrum Display Mode");
  hbxMain     .set_orientation   ( Gtk::ORIENTATION_HORIZONTAL);

  vbxSaMode   .set_orientation   ( Gtk::ORIENTATION_VERTICAL  );
  rbModeTrack      = Gtk::manage(new Gtk::RadioButton(rbgSaMode, "Track Oscilloscope"));
  rbModeAvg        = Gtk::manage(new Gtk::RadioButton(rbgSaMode, "Average Entire Signal"));


  this          ->add        (  hbxMain                            );
    hbxMain      .pack_start (  vbxSaMode,     Gtk::PACK_SHRINK, 2 );
      vbxSaMode  .pack_start ( *rbModeTrack,   Gtk::PACK_SHRINK, 2 );
      vbxSaMode  .pack_start ( *rbModeAvg,     Gtk::PACK_SHRINK, 2 );


  show_all();
  return;
}
void FrmSaMode::Connect(void) {
  rbModeTrack->signal_toggled().connect( sigc::mem_fun(*this, &FrmSaMode::ChangedMode) );
  rbModeAvg  ->signal_toggled().connect( sigc::mem_fun(*this, &FrmSaMode::ChangedMode) );
  return;
}
void FrmSaMode::ChangedMode(void) {
  fprintf(stderr, ".\n"); fflush(stderr);
  if(rbModeTrack->get_active())
    ctSaHor->SetModeTrack();
  else
    ctSaHor->SetModeAvg();
  return;
  }
void FrmSaMode::MRU_ModeRsh(void) {
  return;
  }
