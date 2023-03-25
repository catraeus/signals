// $Id: FrmOsHor.cpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : FrmOsHor.cpp
// Original Author    : duncang
// Creation Date      : Oct 21, 2013
// Copyright          : Copyright © 2013 - 2017 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include "FrmOsHor.hpp"
#include <caes/CaesString.hpp>

       FrmOsHor::FrmOsHor           ( Gtk::Window *i_p, Signal *i_sig)
: parent (i_p)
, sig    (i_sig) {
  BuildEnv       (      );
  BuildContnGrid (      );
  BuildTimeGrid  (      );
  BuildMain      (      );
  IntraConnect   (      );
  InterConnect   (      );
  OsHorRshAll    ( NULL );
  }
       FrmOsHor::~FrmOsHor          (             ) {
  }
void   FrmOsHor::BuildEnv           ( void        ) {
  ctOsHor = CtlOsHor   ::GetInstance( sig );
  ctMd    = CtlMsgDspch::GetInstance(     );
  mdOs    = MdlOs      ::GetInstance( sig );
  return;
}
void   FrmOsHor::BuildContnGrid     ( void        ) {
  //== Column Labels
  lblCPrsh.set_text("Refresh: ");
  lblCPrsh.set_halign(Gtk::ALIGN_END);
  lblCPrsh.set_margin_left(5);
  lblCPrsh.set_margin_right(5);
  lblCPrsh.set_width_chars(9);

  lblCPpbkRto.set_text("Play Ratio: ");
  lblCPpbkRto.set_halign(Gtk::ALIGN_END);
  lblCPpbkRto.set_margin_left(5);
  lblCPpbkRto.set_margin_right(5);
  lblCPpbkRto.set_width_chars(9);

  lblCPsrd.set_text("Stride: ");
  lblCPsrd.set_halign(Gtk::ALIGN_END);
  lblCPsrd.set_margin_left(5);
  lblCPsrd.set_margin_right(5);
  lblCPsrd.set_width_chars(9);

  lblCPsrlRto.set_text("Scrl Ratio: ");
  lblCPsrlRto.set_halign(Gtk::ALIGN_END);
  lblCPsrlRto.set_margin_left(5);
  lblCPsrlRto.set_margin_right(5);
  lblCPsrlRto.set_width_chars(9);

  lblCPscr.set_text("Screen: ");
  lblCPscr.set_halign(Gtk::ALIGN_END);
  lblCPscr.set_margin_left(5);
  lblCPscr.set_margin_right(5);
  lblCPscr.set_width_chars(9);

  //== Row Labels
  lblRPtim.set_text("Time: ");
  lblRPtim.set_halign(Gtk::ALIGN_END);
  lblRPtim.set_margin_left(5);
  lblRPtim.set_margin_right(5);
  lblRPtim.set_width_chars(9);

  lblRPsmp.set_text("Sample: ");
  lblRPsmp.set_halign(Gtk::ALIGN_END);
  lblRPsmp.set_margin_left(5);
  lblRPsmp.set_margin_right(5);
  lblRPsmp.set_width_chars(9);

  lblRPrto.set_text("Ratio: ");
  lblRPrto.set_halign(Gtk::ALIGN_END);
  lblRPrto.set_margin_left(5);
  lblRPrto.set_margin_right(5);
  lblRPrto.set_width_chars(9);

  //== Time   row
  txtTimPrsh.set_text("1.000u");
  txtTimPrsh.set_width_chars(9);
  txtTimPrsh.set_halign(Gtk::ALIGN_END);

  txtTimPsrd.set_text("1.000u");
  txtTimPsrd.set_width_chars(9);
  txtTimPsrd.set_halign(Gtk::ALIGN_END);

  txtTimPscr.set_text("1.000u");
  txtTimPscr.set_width_chars(9);
  txtTimPscr.set_halign(Gtk::ALIGN_END);

  //== Sample row
  txtSmpPrsh.set_text("1.000u");
  txtSmpPrsh.set_width_chars(9);
  txtSmpPrsh.set_halign(Gtk::ALIGN_END);

  txtSmpPsrd.set_text("1.000u");
  txtSmpPsrd.set_width_chars(9);
  txtSmpPsrd.set_halign(Gtk::ALIGN_END);

  txtSmpPscr.set_text("1.000u");
  txtSmpPscr.set_width_chars(9);
  txtSmpPscr.set_halign(Gtk::ALIGN_END);

  //== Ratio  row
  txtPbkRto.set_text("1.000");
  txtPbkRto.set_width_chars(9);
  txtPbkRto.set_halign(Gtk::ALIGN_END);

  txtSrlRto.set_text("1.000");
  txtSrlRto.set_width_chars(9);
  txtSrlRto.set_halign(Gtk::ALIGN_END);

  //== Set up the grid
  grdHorizContn.set_border_width(3);
  grdHorizContn.set_row_homogeneous(true);
  grdHorizContn.set_column_homogeneous(false);

  //== Fill the Grid
  //== Column Labels Top Side
  //                                 /-------------left   = horizongal position
  //                                 |  /----------top    = vertical   postition
  //                                 |  |  /-------width  = Number of cells in width  for merged cell spans
  //                                 |  |  |  /----height = Number of cells in height for merged cell spans
  grdHorizContn.attach(lblCPrsh,     1, 0, 1, 1);
  grdHorizContn.attach(lblCPpbkRto,  2, 0, 1, 1);
  grdHorizContn.attach(lblCPsrd,     3, 0, 1, 1);
  grdHorizContn.attach(lblCPsrlRto,  4, 0, 1, 1);
  grdHorizContn.attach(lblCPscr,     5, 0, 1, 1);
  //== Ratio Row
  grdHorizContn.attach(lblRPrto,     0, 1, 1, 1);
  grdHorizContn.attach(txtPbkRto,    2, 1, 1, 1);
  grdHorizContn.attach(txtSrlRto,    4, 1, 1, 1);
  //== Time Row
  grdHorizContn.attach(lblRPtim,     0, 2, 1, 1);
  grdHorizContn.attach(txtTimPrsh,   1, 2, 1, 1);
  grdHorizContn.attach(txtTimPsrd,   3, 2, 1, 1);
  grdHorizContn.attach(txtTimPscr,   5, 2, 1, 1);
  //== Sample Row
  grdHorizContn.attach(lblRPsmp,     0, 3, 1, 1);
  grdHorizContn.attach(txtSmpPrsh,   1, 3, 1, 1);
  grdHorizContn.attach(txtSmpPsrd,   3, 3, 1, 1);
  grdHorizContn.attach(txtSmpPscr,   5, 3, 1, 1);

  //== Sorry guys, I'll figure you out later
  //grdHorizContn.attach(ckbRshTim,  2, 0, 1, 1);
  //grdHorizContn.attach(ckbPbkRto,  2, 1, 1, 1);
  //grdHorizContn.attach(ckbSrlRto,  2, 2, 1, 1);
  //grdHorizContn.attach(ckbTimVdiv, 2, 3, 1, 1);

  return;
  }
void   FrmOsHor::BuildTimeGrid      ( void        ) {

  lblHNSec.set_text("Time");
  lblHNSec.set_justify(Gtk::JUSTIFY_RIGHT);
  lblHNSec.set_margin_left(5);
  lblHNSec.set_margin_right(5);

  lblHNSmp.set_text("Sample");
  lblHNSmp.set_justify(Gtk::JUSTIFY_RIGHT);
  lblHNSmp.set_margin_left(5);
  lblHNSmp.set_margin_right(5);

  lblHNPxl.set_text("Pixel");
  lblHNPxl.set_justify(Gtk::JUSTIFY_RIGHT);
  lblHNPxl.set_margin_left(5);
  lblHNPxl.set_margin_right(5);

  lblHNDiv.set_text("Division");
  lblHNDiv.set_justify(Gtk::JUSTIFY_RIGHT);
  lblHNDiv.set_margin_left(5);
  lblHNDiv.set_margin_right(5);

  lblHNScr.set_text("Screen");
  lblHNScr.set_justify(Gtk::JUSTIFY_RIGHT);
  lblHNScr.set_margin_left(5);
  lblHNScr.set_margin_right(5);


  txtTimVpxl.set_text("4.0μs");
  txtTimVpxl.set_halign(Gtk::ALIGN_END);
  txtTimVpxl.set_width_chars(9);

  txtTimVdiv.set_text("4.0μs");
  txtTimVdiv.set_halign(Gtk::ALIGN_END);
  txtTimVdiv.set_width_chars(9);

  txtTimVscr.set_text("4.0μs");
  txtTimVscr.set_halign(Gtk::ALIGN_END);
  txtTimVscr.set_width_chars(9);

  txtSmpVpxl.set_text("4.0μs");
  txtSmpVpxl.set_halign(Gtk::ALIGN_END);
  txtSmpVpxl.set_width_chars(9);

  txtSmpVdiv.set_text("4.0μs");
  txtSmpVdiv.set_halign(Gtk::ALIGN_END);
  txtSmpVdiv.set_width_chars(9);

  txtSmpVscr.set_text("4.0μs");
  txtSmpVscr.set_halign(Gtk::ALIGN_END);
  txtSmpVscr.set_width_chars(9);



  grdCtlH3_Numeric.set_border_width(3);
  grdCtlH3_Numeric.set_row_homogeneous(true);
  grdCtlH3_Numeric.set_column_homogeneous(false);

  grdCtlH3_Numeric.attach(lblHNSec,   0, 0, 1, 1);
  grdCtlH3_Numeric.attach(txtTimVpxl, 1, 0, 1, 1);
  grdCtlH3_Numeric.attach(txtTimVdiv, 2, 0, 1, 1);
  grdCtlH3_Numeric.attach(txtTimVscr, 3, 0, 1, 1);
  grdCtlH3_Numeric.attach(lblHNSmp,   0, 1, 1, 1);
  grdCtlH3_Numeric.attach(txtSmpVpxl, 1, 1, 1, 1);
  grdCtlH3_Numeric.attach(txtSmpVdiv, 2, 1, 1, 1);
  grdCtlH3_Numeric.attach(txtSmpVscr, 3, 1, 1, 1);
  grdCtlH3_Numeric.attach(lblHNBlank, 0, 2, 1, 1);
  grdCtlH3_Numeric.attach(lblHNPxl,   1, 2, 1, 1);
  grdCtlH3_Numeric.attach(lblHNDiv,   2, 2, 1, 1);
  grdCtlH3_Numeric.attach(lblHNScr,   3, 2, 1, 1);

  return;
  }
void   FrmOsHor::BuildMain          ( void        ) {
  set_border_width(5);
//  set_size_request(-1, -1);


  //==  The top box, big picture stuff, FS and interpolation method
  frmCtlH0_Signal.set_label("Signal");
  frmCtlH0_Signal.set_border_width(4);
  hbxCtlH0_Signal.set_orientation    (Gtk::ORIENTATION_HORIZONTAL);

  lblFrmVsec.set_justify(Gtk::JUSTIFY_LEFT);
  lblFrmVsec.set_text("FS:  ");
  txtSmpVsec.set_width_chars(8);
  txtSmpVsec.set_halign(Gtk::ALIGN_END);
  txtSmpVsec.set_sensitive(false);

  lblTerp.set_text("Resample Method: ");
  txtTerp = new Gtk::ComboBoxText();
  txtTerp->append("Skip");
  txtTerp->append("Smooth");
  txtTerp->append("MinMax");
  txtTerp->set_active_text("Skip");

  hbxCtlH0_Signal.set_border_width(4);
  hbxCtlH0_Signal.pack_start( lblFrmVsec, Gtk::PACK_SHRINK,        3);
  hbxCtlH0_Signal.pack_start( txtSmpVsec, Gtk::PACK_SHRINK,        3);
  hbxCtlH0_Signal.pack_start( lblTerp,    Gtk::PACK_SHRINK,        3);
  hbxCtlH0_Signal.pack_start(*txtTerp,    Gtk::PACK_SHRINK,        3);
  frmCtlH0_Signal.add(hbxCtlH0_Signal);

  //== The second box, Time Hold
  frmCtlH1_Hold.set_label("Time Setting Hold");
  frmCtlH1_Hold.set_border_width(4);
  hbxCtlH1_Hold    .set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  vbxDummyHoldR  .set_orientation(Gtk::ORIENTATION_VERTICAL  );
  vbxDummyHoldR  .set_size_request(10, -1);





  vbxRbgScrSize  .set_orientation(Gtk::ORIENTATION_VERTICAL  );
  rbScrDiv      = Gtk::manage(new Gtk::RadioButton(rbgScrSize, "Time per Division"));
  rbScrScr      = Gtk::manage(new Gtk::RadioButton(rbgScrSize, "Time per Screen"));
  vbxRbgScrSize .pack_start(*rbScrDiv,    Gtk::PACK_SHRINK, 3       );
  vbxRbgScrSize .pack_start(*rbScrScr,    Gtk::PACK_SHRINK, 3       );

  vbxRbgScroll.set_orientation(Gtk::ORIENTATION_VERTICAL  );
  rbSrlRatio    = Gtk::manage(new Gtk::RadioButton(rbgScroll, "Scroll Ratio"));
  rbSrlScrTime  = Gtk::manage(new Gtk::RadioButton(rbgScroll, "Screen Time"));
  rbSrlSrdTime  = Gtk::manage(new Gtk::RadioButton(rbgScroll, "Stride Time"));
  vbxRbgScroll .pack_start(*rbSrlRatio,    Gtk::PACK_SHRINK, 3       );
  vbxRbgScroll .pack_start(*rbSrlScrTime,    Gtk::PACK_SHRINK, 3       );
  vbxRbgScroll .pack_start(*rbSrlSrdTime,    Gtk::PACK_SHRINK, 3       );

  vbxRbgPlayback .set_orientation(Gtk::ORIENTATION_VERTICAL  );
  rbPbkRatio    = Gtk::manage(new Gtk::RadioButton(rbgPlayback, "Playback Ratio"));
  rbPbkRshTim   = Gtk::manage(new Gtk::RadioButton(rbgPlayback, "Refresh Time"));
  rbPbkSrdTim   = Gtk::manage(new Gtk::RadioButton(rbgPlayback, "Stride Time"));
  vbxRbgPlayback .pack_start(*rbPbkRatio,    Gtk::PACK_SHRINK, 3       );
  vbxRbgPlayback .pack_start(*rbPbkRshTim,    Gtk::PACK_SHRINK, 3       );
  vbxRbgPlayback .pack_start(*rbPbkSrdTim,    Gtk::PACK_SHRINK, 3       );




  hbxCtlH1_Hold.set_border_width(2);
  hbxCtlH1_Hold    .pack_start(vbxRbgScrSize,    Gtk::PACK_SHRINK, 3       );
  hbxCtlH1_Hold    .pack_start(vbxRbgScroll,   Gtk::PACK_SHRINK, 3);
  hbxCtlH1_Hold    .pack_start(vbxRbgPlayback,   Gtk::PACK_SHRINK, 3);
  frmCtlH1_Hold.add(hbxCtlH1_Hold);

  //== The third box, Time Continuity
  frmCtlH2_Contn.set_label("Time Continuity");
  frmCtlH2_Contn.set_border_width(4);
  hbxCtlH2_Contn    .set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  vbxDummyContnR  .set_orientation(Gtk::ORIENTATION_VERTICAL  );
  vbxDummyContnR  .set_size_request(10, -1);

  hbxCtlH2_Contn.set_border_width(2);
  hbxCtlH2_Contn    .pack_start(grdHorizContn,    Gtk::PACK_SHRINK, 3       );
  hbxCtlH2_Contn    .pack_start(vbxDummyContnR,   Gtk::PACK_SHRINK, 3);
  frmCtlH2_Contn.add(hbxCtlH2_Contn);

  //==
  frmCtlH3_Numeric.set_label("Numeric Time Scale Control");
  frmCtlH3_Numeric.set_border_width(4);

  hbxCtlH3_Numeric  .set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  vbxDummyNumericR.set_orientation(Gtk::ORIENTATION_VERTICAL  );
  vbxDummyNumericR.set_size_request(10, -1);

  hbxCtlH3_Numeric.set_border_width(2);
  hbxCtlH3_Numeric  .pack_start(grdCtlH3_Numeric,     Gtk::PACK_SHRINK, 3       );
  hbxCtlH3_Numeric  .pack_start(vbxDummyNumericR, Gtk::PACK_SHRINK, 3);
  frmCtlH3_Numeric.add(hbxCtlH3_Numeric);

  //==  Now put it all together
  vbxCtlHoriz.set_orientation (Gtk::ORIENTATION_VERTICAL);
  vbxCtlHoriz.pack_start(frmCtlH0_Signal,  Gtk::PACK_SHRINK, 1);
  vbxCtlHoriz.pack_start(frmCtlH1_Hold,   Gtk::PACK_SHRINK, 1);
  vbxCtlHoriz.pack_start(frmCtlH2_Contn,   Gtk::PACK_SHRINK, 1);
  vbxCtlHoriz.pack_start(frmCtlH3_Numeric,   Gtk::PACK_SHRINK, 1);

  add(vbxCtlHoriz);

  return;
}

void   FrmOsHor::IntraConnect       ( void        ) {

  txtTimPrsh  .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmOsHor::OnTcScale   ), &txtTimPrsh    ));
  txtTimPsrd  .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmOsHor::OnTcScale   ), &txtTimPsrd    ));
  txtTimPscr  .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmOsHor::OnTcScale   ), &txtTimPscr    ));

  txtSmpPscr  .signal_key_release_event().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmOsHor::OnTcScale   ), &txtSmpPscr    ));
  txtSmpPsrd  .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmOsHor::OnTcScale   ), &txtSmpPsrd    ));
  txtSmpPscr  .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmOsHor::OnTcScale   ), &txtSmpPscr    ));

  txtPbkRto   .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmOsHor::OnTcScale   ), &txtPbkRto     ));
  txtSrlRto   .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmOsHor::OnTcScale   ), &txtSrlRto     ));

  txtTimVpxl  .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmOsHor::OnTcScale   ), &txtTimVpxl    ));
  txtTimVdiv  .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmOsHor::OnTcScale   ), &txtTimVdiv    ));
  txtTimVscr  .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmOsHor::OnTcScale   ), &txtTimVscr    ));

  txtSmpVpxl  .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmOsHor::OnTcScale   ), &txtSmpVpxl    ));
  txtSmpVdiv  .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmOsHor::OnTcScale   ), &txtSmpVdiv    ));
  txtSmpVscr  .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmOsHor::OnTcScale   ), &txtSmpVscr    ));

  return;
}
void   FrmOsHor::InterConnect       ( void        ) {

        MRU_OsHorRshAll        = new CbT<FrmOsHor>();
        MRU_OsHorRshAll       ->SetCallback(this, &FrmOsHor::OsHorRshAll);;
  ctMd->MSU_OsHorRshAll        =                         MRU_OsHorRshAll;
  return;
}


void   FrmOsHor::OnTimeGrp          ( void        ) {
  return;
  }
bool   FrmOsHor::OnTcScale          ( GdkEventKey *i_e, Gtk::Entry *i_txt) {
 if(i_e != 0) {
   if((i_e->keyval != GDK_KEY_Return) && (i_e->keyval != GDK_KEY_Tab))
     return false;
   }
  char   s[256];
  double d;
  strcpy(s, i_txt->get_text().c_str());
  StringEng(s, &d);
  if     (i_txt ==                NULL       ) {                               return false;  }

  else if(i_txt ==               &txtTimPrsh ) {    ctOsHor->SetTimVrsh(d);    return false;  }
  else if(i_txt ==               &txtTimPsrd ) {    ctOsHor->SetTimVsrd(d);    return false;  }
  else if(i_txt ==               &txtTimPscr ) {    ctOsHor->SetTimVscr(d);    return false;  }

  else if(i_txt ==               &txtSmpPrsh ) {    ctOsHor->SetSmpVrsh(d);    return false;  }
  else if(i_txt ==               &txtSmpPsrd ) {    ctOsHor->SetSmpVsrd(d);    return false;  }
  else if(i_txt ==               &txtSmpPscr ) {    ctOsHor->SetSmpVscr(d);    return false;  }

  else if(i_txt ==               &txtPbkRto  ) {    ctOsHor->SetPbkRto (d);    return false;  }
  else if(i_txt ==               &txtSrlRto  ) {    ctOsHor->SetSrlRto (d);    return false;  }

  else if(i_txt ==               &txtTimVpxl ) {    ctOsHor->SetTimVpxl(d);    return false;  }
  else if(i_txt ==               &txtTimVdiv ) {    ctOsHor->SetTimVdiv(d);    return false;  }
  else if(i_txt ==               &txtTimVscr ) {    ctOsHor->SetTimVscr(d);    return false;  }

  else if(i_txt ==               &txtSmpVpxl ) {    ctOsHor->SetSmpVpxl(d);    return false;  }
  else if(i_txt ==               &txtSmpVdiv ) {    ctOsHor->SetSmpVdiv(d);    return false;  }
  else if(i_txt ==               &txtSmpVscr ) {    ctOsHor->SetSmpVscr(d);    return false;  }

  else                                                                         return false;
  return false;
  }



bool   FrmOsHor::OsHorRshAll        ( void   *i_ddd ) {
  char   s[256];
  double d;

  d = sig ->GetFS           ();  EngString(s, d, 4, (char *)"Hz");  txtSmpVsec.set_text(s);

  d = mdOs->GetTimVrsh      ();  EngString(s, d, 5, (char *)"s");   txtTimPrsh.set_text(s);
  d = mdOs->GetTimVsrd      ();  EngString(s, d, 5, (char *)"s");   txtTimPsrd.set_text(s);
                                                                  //txtTimPscr done below by its duplicate in the V section

  d = mdOs->GetSmpVrsh      ();  EngString(s, d, 5, (char *)"F");   txtSmpPrsh.set_text(s);
  d = mdOs->GetSmpVsrd      ();  EngString(s, d, 5, (char *)"F");   txtSmpPsrd.set_text(s);
                                                                  //txtSmpPScr done below in its duplicate in the V section

  d = mdOs->GetPbkRto       ();  EngString(s, d, 5, (char *)"");    txtPbkRto.set_text(s);
  d = mdOs->GetSrlRto       ();  EngString(s, d, 5, (char *)"");    txtSrlRto.set_text(s);

  d = mdOs->GetTimVpxl      ();  EngString(s, d, 5, (char *)"s");   txtTimVpxl.set_text(s);
  d = mdOs->GetTimVdiv      ();  EngString(s, d, 5, (char *)"s");   txtTimVdiv.set_text(s);
  d = mdOs->GetTimVscr      ();  EngString(s, d, 5, (char *)"s");   txtTimVscr.set_text(s);
                                                                    txtTimPscr.set_text(s);

  d = mdOs->GetSmpVpxl      ();  EngString(s, d, 5, (char *)"F");   txtSmpVpxl.set_text(s);
  d = mdOs->GetSmpVdiv      ();  EngString(s, d, 5, (char *)"F");   txtSmpVdiv.set_text(s);
  d = mdOs->GetSmpVscr      ();  EngString(s, d, 5, (char *)"F");   txtSmpVscr.set_text(s);
                                                                    txtSmpPscr.set_text(s);

  txtTimPrsh  .set_sensitive(true);
  txtTimPsrd  .set_sensitive(true);
  txtTimPscr  .set_sensitive(true);

  txtSmpPscr  .set_sensitive(true);
  txtSmpPsrd  .set_sensitive(true);
  txtSmpPscr  .set_sensitive(true);

  txtPbkRto   .set_sensitive(true);
  txtSrlRto   .set_sensitive(true);

  txtTimVpxl  .set_sensitive(true);
  txtTimVdiv  .set_sensitive(true);
  txtTimVscr  .set_sensitive(true);

  txtSmpVpxl  .set_sensitive(true);
  txtSmpVdiv  .set_sensitive(true);
  txtSmpVscr  .set_sensitive(true);

  return false;
}
