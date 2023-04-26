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
  OnRshAll      ( NULL );
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


  return;
}
void   FrmSaHor::BuildMain            ( void      ) {
  txtRsmp   = new Gtk:: ComboBoxText();
  txtFS     = new Gtk:: Entry       ();

  vbxCtlHoriz   .set_orientation      ( Gtk::ORIENTATION_VERTICAL                   );

  hbx0Config    .set_orientation      ( Gtk::ORIENTATION_HORIZONTAL                 );
  lblFS         .set_justify          ( Gtk::JUSTIFY_LEFT                           );
  lblFS         .set_text             (                        "FS:  "              );
  txtFS        ->set_width_chars      (                                         8   );
  txtFS        ->set_alignment        ( Gtk::ALIGN_END                              );
  btLogLin      .set_label            (                        "Log/Lin"            );
  btFftDft      .set_label            (                        "FFT/DFT"            );
  btLogLin      .set_tooltip_text     (                        "FFT only past 2048" );

  hbx1Gridng    .set_orientation      ( Gtk::ORIENTATION_HORIZONTAL                 );
  frmAnchor     .set_label            (                         "Anchor"            );
  hbxAnchor     .set_orientation      ( Gtk::ORIENTATION_HORIZONTAL                 );

  rbtAnchStrt   .set_group            ( grpRbHorAnch);
  rbtAnchCntr   .set_group            ( grpRbHorAnch);
  rbtAnchStop   .set_group            ( grpRbHorAnch);
  rbtAnchStrt   .set_label            (                         "Start"             );
  rbtAnchCntr   .set_label            (                         "Center"            );
  rbtAnchStop   .set_label            (                         "Stop   "           );
  btAnchGrid    .set_label            (                         "Grid on Anchor"    );
  lblCenPos     .set_text             (                         "Position:"         );
  txtCenPos     .set_width_chars      (                                         8   );

  hbx2FScale.set_orientation      ( Gtk::ORIENTATION_HORIZONTAL                 );
  lblFstart .set_text("Start: " ); lblFstart .set_justify(Gtk::JUSTIFY_RIGHT); lblFstart .set_margin_left(5); lblFstart .set_margin_right(5);
  lblFCen   .set_text("Center: "); lblFCen   .set_justify(Gtk::JUSTIFY_RIGHT); lblFCen   .set_margin_left(5); lblFCen   .set_margin_right(5);
  lblFstop  .set_text("Stop: "  ); lblFstop  .set_justify(Gtk::JUSTIFY_RIGHT); lblFstop  .set_margin_left(5); lblFstop  .set_margin_right(5);

  txtFstart .set_width_chars(9); txtFstart.set_alignment(Gtk::ALIGN_END);
  txtFCen   .set_width_chars(9); txtFCen  .set_alignment(Gtk::ALIGN_END);
  txtFstop  .set_width_chars(9); txtFstop .set_alignment(Gtk::ALIGN_END);

  hbx3Rsmp      .set_orientation      ( Gtk::ORIENTATION_HORIZONTAL                 );
  lblRsmp       .set_text             (                         "Resample Method: " );
  txtRsmp      ->append               (                         "Skip"              );
  txtRsmp      ->append               (                         "Smooth"            );
  txtRsmp      ->append               (                         "MinMax"            );
  txtRsmp      ->set_active_text      (                         "Skip"              );



  this               ->add          (  vbxCtlHoriz                                );
    vbxCtlHoriz       .pack_start   (  hbx0Config,    Gtk::PACK_SHRINK,        3  );
      hbx0Config      .pack_start   (  lblFS,         Gtk::PACK_SHRINK,        3  );
      hbx0Config      .pack_start   ( *txtFS,         Gtk::PACK_SHRINK,        3  );
      hbx0Config      .pack_start   (  btLogLin,      Gtk::PACK_SHRINK,        3  );
      hbx0Config      .pack_start   (  btFftDft,      Gtk::PACK_SHRINK,        3  );

    vbxCtlHoriz       .pack_start   (  hbx1Gridng,    Gtk::PACK_SHRINK,        3  );

      hbx1Gridng      .pack_start   (  frmAnchor,     Gtk::PACK_SHRINK,        3  );
        frmAnchor     .add          (  hbxAnchor                                  );
          hbxAnchor   .pack_start   (  rbtAnchStrt,   Gtk::PACK_SHRINK,        3  );
          hbxAnchor   .pack_start   (  rbtAnchCntr,   Gtk::PACK_SHRINK,        3  );
          hbxAnchor   .pack_start   (  rbtAnchStop,   Gtk::PACK_SHRINK,        3  );
          hbxAnchor   .pack_start   (  btAnchGrid,    Gtk::PACK_SHRINK,        3  );
          hbxAnchor   .pack_start   (  lblCenPos,     Gtk::PACK_SHRINK,        3  );
          hbxAnchor   .pack_start   (  txtCenPos,     Gtk::PACK_SHRINK,        3  );

    vbxCtlHoriz       .pack_start   (  hbx2FScale,    Gtk::PACK_SHRINK,        3  );
      hbx2FScale      .pack_start   (  lblFstart,     Gtk::PACK_SHRINK,        3  );
      hbx2FScale      .pack_start   (  txtFstart,     Gtk::PACK_SHRINK,        3  );
      hbx2FScale      .pack_start   (  lblFCen,       Gtk::PACK_SHRINK,        3  );
      hbx2FScale      .pack_start   (  txtFCen,       Gtk::PACK_SHRINK,        3  );
      hbx2FScale      .pack_start   (  lblFstop,      Gtk::PACK_SHRINK,        3  );
      hbx2FScale      .pack_start   (  txtFstop,      Gtk::PACK_SHRINK,        3  );
    vbxCtlHoriz       .pack_start   (  hbx3Rsmp,      Gtk::PACK_SHRINK,        3  );
      hbx3Rsmp        .pack_start   (  lblRsmp,       Gtk::PACK_SHRINK,        3  );
      hbx3Rsmp        .pack_start   ( *txtRsmp,       Gtk::PACK_SHRINK,        3  );
    vbxCtlHoriz       .pack_start   (  grdHorizNums,  Gtk::PACK_SHRINK,        3  );

  this->show_all();
  return;
}






void   FrmSaHor::SetDrwSa             ( DrwSa *v  ) {
  vwSaDrw = v;
  return;
}
void   FrmSaHor::IntraConnect         ( void      ) {
  btLogLin    .signal_clicked          ().connect(                         sigc::mem_fun(*this, &FrmSaHor::OnLogLin    )                );
  btFftDft    .signal_clicked          ().connect(                         sigc::mem_fun(*this, &FrmSaHor::OnFftDft    )                );

  rbtAnchStrt .signal_clicked          ().connect(                         sigc::mem_fun(*this, &FrmSaHor::OnAnchor    )                );
  rbtAnchCntr .signal_clicked          ().connect(                         sigc::mem_fun(*this, &FrmSaHor::OnAnchor    )                );
  rbtAnchStop .signal_clicked          ().connect(                         sigc::mem_fun(*this, &FrmSaHor::OnAnchor    )                );
  btAnchGrid  .signal_clicked          ().connect(                         sigc::mem_fun(*this, &FrmSaHor::OnAnchGrid  )                );

  txtCenPos   .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmSaHor::OnFaScale   ), &txtCenPos    ));
  txtFstart   .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmSaHor::OnFaScale   ), &txtFstart    ));
  txtFCen     .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmSaHor::OnFaScale   ), &txtFCen      ));
  txtFstop    .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmSaHor::OnFaScale   ), &txtFstop     ));

  txtNtime    .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmSaHor::OnFaScale   ), &txtNtime     ));
  txtDelFreq  .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmSaHor::OnFaScale   ), &txtDelFreq   ));
  txtNfreq    .signal_key_press_event  ().connect(sigc::bind<Gtk::Entry *>(sigc::mem_fun(*this, &FrmSaHor::OnFaScale   ), &txtNfreq     ));
  txtFS      ->set_sensitive           (false);
  return;
}
void   FrmSaHor::InterConnect         ( void      ) {
        CbHn_RshAll        = new CbT<FrmSaHor>();
        CbHn_RshAll       ->SetCallback(this, &FrmSaHor::OnRshAll);
  ctMd->CtHn_SaHorRshAll    =                             CbHn_RshAll;
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
  if(rshHoldOff) return;
  bool ll = btLogLin.get_active();
  if(ll)     ctSaHor->SetLog();
  else       ctSaHor->SetLin();
  return;
}

void   FrmSaHor::OnFftDft             ( void      ) {
  if(rshHoldOff) return;
  bool ll = btFftDft.get_active();
  if(ll)    mdSa->SetFFT();
  else      mdSa->SetDFT();
  return;
}

void   FrmSaHor::OnAnchor             ( void      ) {
       if(rbtAnchStrt.get_active())    mdSa->SetFAnchS();
  else if(rbtAnchCntr.get_active())    mdSa->SetFAnchC();
  else                                 mdSa->SetFAnchP();
  return;
}
void   FrmSaHor::OnAnchGrid           ( void      ) {
  mdSa->SetFAnchGrid(btAnchGrid.get_active());
  return;
}

bool   FrmSaHor::OnFaScale            (GdkEventKey   *i_v, Gtk::Entry *i_x) {
  if(rshHoldOff)
    return false;
  rshHoldOff = true;
  if(i_v != 0) {
    if((i_v->keyval != GDK_KEY_Return) && (i_v->keyval != GDK_KEY_Tab)) {
      return false;
    }
  }
  char   s[256];
  double d;
  ullong u;
  strcpy(s, i_x->get_text().c_str());
  StringEng(s, &d);
  u = (ullong) (d + DBL_EPS);
  if     (i_x ==                NULL       ) {                             rshHoldOff = false;   return false;  }
  else if(i_x ==               &txtCenPos  ) {    ctSaHor->SetFCenPos (d); rshHoldOff = false;   return false;  }
  else if(i_x ==               &txtFstart  ) {    ctSaHor->SetFStart  (d); rshHoldOff = false;   return false;  }
  else if(i_x ==               &txtFCen    ) {    ctSaHor->SetFCen    (d); rshHoldOff = false;   return false;  }
  else if(i_x ==               &txtFstop   ) {    ctSaHor->SetFStop   (d); rshHoldOff = false;   return false;  }

  else if(i_x ==               &txtNtime   ) {    ctSaHor->SetNtime   (u); rshHoldOff = false;   return false;  }
  else if(i_x ==               &txtNfreq   ) {    ctSaHor->SetNfreq   (u); rshHoldOff = false;   return false;  }
  else                                       {                             rshHoldOff = false;   return false;  }
                                                                           rshHoldOff = false;   return false;
}




bool   FrmSaHor::OnRshAll             ( void *i_d ) {
  rshHoldOff = true;
  char   s[256];
  double d;
  ullong l;
  bool   b;

  d  = sig   ->GetFS       ();  EngString    (s, d, 4, (char *)"Hz");  txtFS       ->set_text         (s);
  d /= mdSa  ->GetTvAna    ();  EngString    (s, d, 4, (char *)"Hz");  txtDelFreq   .set_text         (s);
  b  = mdSa  ->IsFLog      ();                                         btLogLin     .set_active       (b);
  d  = mdSa  ->GetFCenPos  ();  sprintf      (s,       "%1.4f",   d);  txtCenPos    .set_text         (s);
                                sprintf      (s,       "%15.11e", d);  txtCenPos    .set_tooltip_text (s);
  d  = mdSa  ->GetFStart   ();  EngString    (s, d, 4, (char *)"Hz");  txtFstart    .set_text         (s);
                                sprintf      (s,       "%15.11e", d);  txtFstart    .set_tooltip_text (s);
  d  = mdSa  ->GetFCen     ();  EngString    (s, d, 4, (char *)"Hz");  txtFCen      .set_text         (s);
                                sprintf      (s,       "%15.11e", d);  txtFCen      .set_tooltip_text (s);
  d  = mdSa  ->GetFStop    ();  EngString    (s, d, 4, (char *)"Hz");  txtFstop     .set_text         (s);
                                sprintf      (s,       "%15.11e", d);  txtFstop     .set_tooltip_text (s);
  l  = mdSa  ->GetTvAna    ();  IntWithComma (s, l                 );  txtNtime     .set_text         (s);
  l  = mdSa  ->GetFvAna    ();  IntWithComma (s, l                 );  txtNfreq     .set_text         (s);
  if(vwSaDrw != NULL) vwSaDrw->OnReGrid();
  rshHoldOff = false;
  return false;
}
