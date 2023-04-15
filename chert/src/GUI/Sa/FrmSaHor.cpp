// $Id: FrmSaHor.cpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : FrmSaHor.cpp
// Original Author    : duncang
// Creation Date      : Oct 23, 2013
// Copyright          : Copyright © 2013 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include <caes/CaesString.hpp>

#include "FrmSaHor.hpp"

       FrmSaHor::FrmSaHor             ( Signal *i_sig )
: vwSaDrw( NULL)
, sig (i_sig) {
  BuildEnv      (      );
  BuildContnGrid(      );
  BuildTimeGrid (      );
  BuildMain     (      );
  IntraConnect  (      );
  InterConnect  (      );
  SaHorRshAll   ( NULL );
}
       FrmSaHor::~FrmSaHor            ( void      ) {
}

void   FrmSaHor::BuildEnv             ( void      ) {
  ctSaHor  = CtlSaHor     :: GetInstance( sig );
  ctMd     = CtlMsgDspch  :: GetInstance(     );
  mdSa     = MdlSa        :: GetInstance(     );
  return;
}
void   FrmSaHor::BuildContnGrid       ( void      ) {
  lblFmin.set_text("Start: ");
  lblFmax.set_text("Stop: ");

  lblFmin.set_justify(Gtk::JUSTIFY_RIGHT);
  lblFmax.set_justify(Gtk::JUSTIFY_RIGHT);

  lblFmin.set_margin_left(5);
  lblFmax.set_margin_left(5);

  lblFmin.set_margin_right(5);
  lblFmax.set_margin_right(5);

  txtFmin.set_width_chars(9);
  txtFmax.set_width_chars(9);

  txtFmin.set_alignment(Gtk::ALIGN_END);
  txtFmax.set_alignment(Gtk::ALIGN_END);

  grdHorizContn.set_border_width(3);
  grdHorizContn.set_row_homogeneous(true);
  grdHorizContn.set_column_homogeneous(false);

  grdHorizContn.attach(lblFmin, 0, 0, 1, 1);
  grdHorizContn.attach(txtFmin, 1, 0, 1, 1);
  grdHorizContn.attach(lblFmax, 2, 0, 1, 1);
  grdHorizContn.attach(txtFmax, 3, 0, 1, 1);

  return;
  }
void   FrmSaHor::BuildMain            ( void      ) {
  txtTerp   = new Gtk:: ComboBoxText();
  txtFS     = new Gtk:: Entry       ();
  txtTRfsh  = new Gtk:: ComboBoxText();

  hbxCtlH0       .set_orientation     (  Gtk::ORIENTATION_HORIZONTAL              );
  lblFS           .set_justify        (  Gtk::JUSTIFY_LEFT                        );
  lblFS           .set_text           (                        "FS:  "            );
  txtFS          ->set_width_chars    (                                         8 );
  txtFS          ->set_alignment      ( Gtk::ALIGN_END                            );
  lblTRfsh        .set_text           (                        "T Rfsh: "         );
  txtTRfsh       ->append             (                        "20 ms"            );
  txtTRfsh       ->append             (                        "50 ms"            );
  txtTRfsh       ->append             (                        "100 ms"           );
  txtTRfsh       ->append             (                        "200 ms"           );
  txtTRfsh       ->append             (                        "500 ms"           );
  txtTRfsh       ->append             (                        "1 s"              );
  txtTRfsh       ->append             (                        "2 s"              );
  txtTRfsh       ->set_active_text    ("                        20 ms"            );
  btLog           .set_label          (                        "Log/Lin"          );

  vbxCtlHoriz     .set_orientation    ( Gtk::ORIENTATION_VERTICAL                 );

  hbxTerp         .set_orientation    ( Gtk::ORIENTATION_HORIZONTAL               );
  lblTerp.         set_text           (                        "Resample Method: ");
  txtTerp        ->append             (                        "Skip"             );
  txtTerp        ->append             (                        "Smooth"           );
  txtTerp        ->append             (                        "MinMax"           );
  txtTerp        ->set_active_text    (                        "Skip"             );





  this               ->add          (  vbxCtlHoriz                              );
    vbxCtlHoriz       .pack_start   (  hbxCtlH0,      Gtk::PACK_SHRINK,        3);
      hbxCtlH0        .pack_start   (  lblFS,         Gtk::PACK_SHRINK,        3);
      hbxCtlH0        .pack_start   ( *txtFS,         Gtk::PACK_SHRINK,        3);
      hbxCtlH0        .pack_start   (  lblTRfsh,      Gtk::PACK_SHRINK,        3);
      hbxCtlH0        .pack_start   ( *txtTRfsh,      Gtk::PACK_SHRINK,        3);
      hbxCtlH0        .pack_start   (  btLog,         Gtk::PACK_SHRINK,        3);
    vbxCtlHoriz       .pack_start   (  grdHorizContn, Gtk::PACK_SHRINK,        3);
    vbxCtlHoriz       .pack_start   (  hbxTerp,       Gtk::PACK_SHRINK,        3);
      hbxTerp         .pack_start   (  lblTerp,       Gtk::PACK_SHRINK,        3);
      hbxTerp         .pack_start   ( *txtTerp,       Gtk::PACK_EXPAND_WIDGET   );
    vbxCtlHoriz       .pack_start   (  grdHorizNums,  Gtk::PACK_SHRINK,        3);

    this->show_all();
  return;
}






void   FrmSaHor::SetDrwSa             ( DrwSa *v  ) {
  vwSaDrw = v;
  return;
}
void   FrmSaHor::IntraConnect         ( void      ) {
  btLog       .signal_clicked          ().connect(                         sigc::mem_fun(*this, &FrmSaHor::OnLogLin    )                );
  txtFmin     .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmSaHor::OnFaScale   ), &txtFmin     ));
  txtFmax     .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmSaHor::OnFaScale   ), &txtFmax     ));
  txtNtime    .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmSaHor::OnFaScale   ), &txtNtime    ));
  txtDelFreq  .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmSaHor::OnFaScale   ), &txtDelFreq  ));
  txtNfreq    .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmSaHor::OnFaScale   ), &txtNfreq    ));
  txtFS          ->set_sensitive      (false);
  return;
}
void   FrmSaHor::InterConnect         ( void      ) {
        MRU_SaHorRshAll        = new CbT<FrmSaHor>();
        MRU_SaHorRshAll       ->SetCallback(this, &FrmSaHor::SaHorRshAll);
  ctMd->MSU_SaHorRshAll    =                             MRU_SaHorRshAll;
  return;
}
void   FrmSaHor::BuildTimeGrid        ( void      ) {

  lblNtime  .set_text("Samples"   );
  lblDelFreq.set_text("RBW"       );
  lblNfreq  .set_text("Freq Bins" );

  lblNtime  .set_justify(Gtk::JUSTIFY_RIGHT);
  lblDelFreq.set_justify(Gtk::JUSTIFY_RIGHT);
  lblNfreq  .set_justify(Gtk::JUSTIFY_RIGHT);

  lblNtime  .set_margin_left(5);
  lblDelFreq.set_margin_left(5);
  lblNfreq  .set_margin_left(5);

  lblNtime  .set_margin_right(5);
  lblDelFreq.set_margin_right(5);
  lblNfreq  .set_margin_right(5);

  txtNtime  .set_width_chars(9);
  txtDelFreq.set_width_chars(9);
  txtNfreq  .set_width_chars(9);

  txtNtime  .set_alignment(Gtk::ALIGN_END);
  txtDelFreq.set_alignment(Gtk::ALIGN_END);
  txtNfreq  .set_alignment(Gtk::ALIGN_END);

  grdHorizNums.set_border_width(3);
  grdHorizNums.set_row_homogeneous(true);
  grdHorizNums.set_column_homogeneous(false);

  grdHorizNums.attach(lblNtime,       0, 0, 1, 1);
  grdHorizNums.attach(txtNtime,       1, 0, 1, 1);
  grdHorizNums.attach(lblDelFreq,     2, 0, 1, 1);
  grdHorizNums.attach(txtDelFreq,     3, 0, 1, 1);
  grdHorizNums.attach(lblNfreq,       0, 1, 1, 1);
  grdHorizNums.attach(txtNfreq,       1, 1, 1, 1);

  return;
  }
void   FrmSaHor::BuildSetup           ( void      ) {
  rshHoldOff = false;
  ctSaHor->SetLog();
  return;
}

void   FrmSaHor::OnLogLin             ( void      ) {
  fprintf(stderr, "in\n"); fflush(stderr);
  if(rshHoldOff) return;
  fprintf(stderr, "past\n"); fflush(stderr);
  bool ll;
  ll = btLog.get_active();
  if(ll) {
    fprintf(stderr, "todolog\n"); fflush(stderr);
    ctSaHor->SetLog();
    fprintf(stderr, "didlog\n"); fflush(stderr);
  }
  else {
    fprintf(stderr, "todolin\n"); fflush(stderr);
    ctSaHor->SetLin();
    fprintf(stderr, "didlin\n"); fflush(stderr);
  }
  return;
}

bool   FrmSaHor::OnFaScale            (GdkEventKey   *i_v, Gtk::Entry *i_x) {
  if(i_v != 0) {
    if((i_v->keyval != GDK_KEY_Return) && (i_v->keyval != GDK_KEY_Tab))
      return false;
    }
  char   s[256];
  double d;
  ullong u;
   strcpy(s, i_x->get_text().c_str());
   StringEng(s, &d);
   fprintf(stdout, "    s: %6s    d: %lf\n", s, d); fflush(stdout);
   u = (ullong) (d + DBL_EPS);
   if     (i_x ==                NULL     ) {                             return false;  }
   else if(i_x ==               &txtFmin  ) {    ctSaHor->SetFmin (d);    return false;  }
   else if(i_x ==               &txtFmax  ) {    ctSaHor->SetFmax (d);    return false;  }
   else if(i_x ==               &txtNtime ) {    ctSaHor->SetNtime(u);    return false;  }
   else if(i_x ==               &txtNfreq ) {    ctSaHor->SetNfreq(u);    return false;  }
   else                                                                   return false;
   return false;
}




bool   FrmSaHor::SaHorRshAll          ( void *i_d ) {
  rshHoldOff = true;
  char   s[256];
  double d;
  ullong l;
  bool   b;

  d  = sig   ->GetFS       ();  EngString    (s, d, 4, (char *)"Hz");  txtFS       ->set_text   (s);
  d /= mdSa  ->GetSmpVana  ();  EngString    (s, d, 4, (char *)"Hz");  txtDelFreq   .set_text   (s);
  b  = mdSa  ->IsLogX      ();                                         btLog        .set_active (b);
  d  = mdSa  ->GetFmin     ();  EngString    (s, d, 4, (char *)"Hz");  txtFmin      .set_text   (s);
  d  = mdSa  ->GetFmax     ();  EngString    (s, d, 4, (char *)"Hz");  txtFmax      .set_text   (s);
  l  = mdSa  ->GetSmpVana  ();  IntWithComma (s, l                 );  txtNtime     .set_text   (s);
  l  = mdSa  ->GetFrqVana  ();  IntWithComma (s, l                 );  txtNfreq     .set_text   (s);
  if(vwSaDrw != NULL) vwSaDrw->ReGrid();
  rshHoldOff = false;
  return false;
}
