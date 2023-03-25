// $Id: FrmOsVrt.cpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : FrmOsVrt.cpp
// Original Author    : duncang
// Creation Date      : Oct 16, 2013
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include <caes/CaesString.hpp>

#include "FrmOsVrt.hpp"

     FrmOsVrt::FrmOsVrt        ( Gtk::Window *i_p, Signal *i_sig  )
: parent (i_p) {
  BuildEnv(i_sig);

  BuildChannels();
  BuildMain();
  IntraConnect();
  InterConnect();

  ReSkin(NULL);
  OnRshAll(NULL);
  }
     FrmOsVrt::~FrmOsVrt       ( void       ) {
  }
void FrmOsVrt::BuildEnv        ( Signal *i_sig ) {
  ctMd    = CtlMsgDspch::GetInstance(       );
  ctOsVrt = CtlOsVrt   ::GetInstance( i_sig );
  mdOs    = MdlOs      ::GetInstance( i_sig );
  return;
}
void FrmOsVrt::BuildChannels   ( void       ) {
  grdVert.set_border_width(3);
  grdVert.set_row_homogeneous(true);
  grdVert.set_column_homogeneous(false);


  for(int i=0; i<CtlOsVrt::COVK_MAX_CH; i++) {
    char cc[2];
    rb[i].set_group(grpRbVertCh);

    sprintf(cc, "%d", i);
    lb[i].set_text(cc);
    lb[i].set_width_chars(3);
    cb[i].set_events(Gdk::BUTTON_RELEASE_MASK);

    eb[i].set_active(true);

    cb[i].add(lb[i]);
    grdVert.attach(rb[i], 0, i, 1, 1);
    grdVert.attach(cb[i], 1, i, 1, 1);
    grdVert.attach(eb[i], 2, i, 1, 1);
    }
  return;
  }
void FrmOsVrt::BuildMain       ( void       ) {
  set_border_width(5);
 // set_size_request(-1, -1);

  hbxOsVert.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  vbxCtlVert.set_orientation(Gtk::ORIENTATION_VERTICAL);

  adjChan = Gtk::Adjustment::create(1.0, 1.0, 4.0, 1.0, 1.0, 0.0);
  adjChan->set_lower(0.0);
  adjChan->set_upper(4.0);

  etxChan = new Gtk::SpinButton(adjChan, 1, 0);
  etxChan->set_range(1, 4);
  etxChan->set_wrap(true);

  hbxChan   .pack_start(*etxChan,      Gtk::PACK_SHRINK,        3);
  hbxChan   .pack_start( hbxChanFill,  Gtk::PACK_SHRINK,        0);
  vbxCtlVert.pack_start( hbxChan,      Gtk::PACK_SHRINK,        3);
  vbxCtlVert.pack_start( grdVert,      Gtk::PACK_SHRINK,        3);

  lblVoltVscr.set_text("Volts per Screen");
  txtVoltVscr.set_width_chars(9);
  vbxVoltGrid.set_orientation(Gtk::ORIENTATION_VERTICAL);
  vbxVoltGrid.pack_start(lblVoltVscr,    Gtk::PACK_SHRINK,        3);
  vbxVoltGrid.pack_start(txtVoltVscr,    Gtk::PACK_SHRINK,        3);

  hbxOsVert.pack_start(vbxCtlVert,     Gtk::PACK_SHRINK,        3);
  hbxOsVert.pack_start(vbxVoltGrid,    Gtk::PACK_SHRINK,        3);

  add(hbxOsVert);
  return;
}
void FrmOsVrt::IntraConnect    ( void       ) {
  cb[0].signal_button_release_event().connect(sigc::bind<int, Gtk::Window *>(sigc::mem_fun(*ctOsVrt, &CtlOsVrt::OnColChange), 0, parent   ));
  cb[1].signal_button_release_event().connect(sigc::bind<int, Gtk::Window *>(sigc::mem_fun(*ctOsVrt, &CtlOsVrt::OnColChange), 1, parent    ));
  cb[2].signal_button_release_event().connect(sigc::bind<int, Gtk::Window *>(sigc::mem_fun(*ctOsVrt, &CtlOsVrt::OnColChange), 2, parent    ));
  cb[3].signal_button_release_event().connect(sigc::bind<int, Gtk::Window *>(sigc::mem_fun(*ctOsVrt, &CtlOsVrt::OnColChange), 3, parent    ));

  eb[0].signal_toggled().connect(sigc::bind<int>(sigc::mem_fun(*this, &FrmOsVrt::OnChEn), 0));
  eb[1].signal_toggled().connect(sigc::bind<int>(sigc::mem_fun(*this, &FrmOsVrt::OnChEn), 1));
  eb[2].signal_toggled().connect(sigc::bind<int>(sigc::mem_fun(*this, &FrmOsVrt::OnChEn), 2));
  eb[3].signal_toggled().connect(sigc::bind<int>(sigc::mem_fun(*this, &FrmOsVrt::OnChEn), 3));

  txtVoltVscr.signal_focus_out_event().connect(sigc::mem_fun(*this, &FrmOsVrt::OnVoltVscr));
//  txtVoltVscr.signal_changed().connect(sigc::mem_fun(*this, &FrmOsVrt::OnVoltVscr));
  return;
}
void FrmOsVrt::InterConnect    ( void       ) {
  MRU_OsVrtReSkin = new CbT<FrmOsVrt>();
  MRU_OsVrtReSkin->SetCallback(this, &FrmOsVrt::ReSkin);
  ctMd->MSU_OsVrtReSkin = MRU_OsVrtReSkin;


  MRU_RshAll = new CbT<FrmOsVrt>();
  MRU_RshAll->SetCallback(this, &FrmOsVrt::OnRshAll);
  ctMd->MSU_OsVrtRshAll = MRU_RshAll;

  ctMd->MRD_OsNewColors();
  return;
}
bool FrmOsVrt::ReSkin          ( void *i_d  ) {
  for(int i=0; i<4; i++)
    lb[i].override_background_color(ctOsVrt->GetCol(i), Gtk::STATE_FLAG_NORMAL);
  return false;
  }
bool FrmOsVrt::OnVoltVscr      ( GdkEventFocus* gdk_event) {
  char ss[32768];
  double dd;
  strcpy(ss, txtVoltVscr.get_text().c_str());
  if(IsDoubleFixed(ss))
    sscanf(ss, "%lf", &dd);
  else
    dd = mdOs->GetVoltVscr();
  ctOsVrt->SetVoltVscr(dd);
  return false;
}
void FrmOsVrt::OnChEn          ( int   i_ch ) {
  fprintf(stdout, "FCE.\n"); fflush(stdout);
  bool isEn;
  isEn = eb[i_ch].get_active();
  ctOsVrt->SetEn(isEn, i_ch);
  ctMd->MRD_OsNewColors();
  return;
}
bool FrmOsVrt::OnRshAll        ( void *i_d  ) {
  double dd;
  char   ss[32768];

  dd = mdOs->GetVoltVscr();
  EngString(ss, dd, 3, (char *)"V" );
  txtVoltVscr.set_text((const char *)ss);

  return true;
}
