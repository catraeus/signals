// $Id: FrmSaVrt.cpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : FrmSaVrt.cpp
// Original Author    : duncang
// Creation Date      : Oct 23, 2013
// Copyright          : Copyright © 2013 - 2017 by Catraeus and Duncan Gray
//
// Description        :
//   Go see the .hpp file.
//
//=================================================================================================

#include <caes/CaesString.hpp>

#include "FrmSaVrt.hpp"

        FrmSaVrt::FrmSaVrt        ( Signal *i_sig ) {
  BuildEnv     ( i_sig );
  BuildGrid    (       );
  BuildMain    (       );
  InterConnect (       );
  IntraConnect (       );
  SaVrtRshAll  ( NULL  );
}
        FrmSaVrt::~FrmSaVrt       ( void       ) {
  }
void    FrmSaVrt::BuildEnv        ( Signal *i_sig ) {
  ctSaVrt  = CtlSaVrt    :: GetInstance( i_sig );
  mdSa     = MdlSa       :: GetInstance(       );
  ctMd     = CtlMsgDspch :: GetInstance(       );
  return;
}
void    FrmSaVrt::BuildGrid       ( void       ) {
  grdVert.set_border_width(3);
  grdVert.set_row_homogeneous(true);
  grdVert.set_column_homogeneous(false);


  for(int i=0; i<4; i++) {
    char cc[2];
    rb[i].set_group(grpRbVertCh);

    sprintf(cc, "%d", i);
    lb[i].set_text(cc);
    lb[i].set_width_chars(3);
    eb[i].set_events(Gdk::BUTTON_RELEASE_MASK);

    cb[i].set_active(true);

    eb[i].add(lb[i]);
    grdVert.attach(rb[i], 0, i, 1, 1);
    grdVert.attach(eb[i], 1, i, 1, 1);
    grdVert.attach(cb[i], 2, i, 1, 1);
    }

  return;
  }
void    FrmSaVrt::BuildMain       ( void       ) {
  vbxCtlVert .set_orientation   ( Gtk::ORIENTATION_VERTICAL     );

  hbxSpan    .set_orientation   ( Gtk::ORIENTATION_HORIZONTAL   );
  hbxSpan    .set_border_width  (                             3 );

  etxSpanTop .set_alignment     ( Gtk::ALIGN_END                );
  etxSpanTop .set_text          ( "20"                          );

  cbxBasis = new Gtk::ComboBoxText();
  cbxBasis->set_size_request(100, -1);
  //WARNING The unordered set of Vertical Scaling Modes is now a straight-line integer.
  for(ullong i=0; i<mdSa->GetVrtModeN(); i++) {
    cbxBasis->append(mdSa->GetVrtModeStr(i));
  }
  cbxBasis->set_active_text(mdSa->GetVrtModeStr(0));

  hbxScale   .set_orientation   ( Gtk::ORIENTATION_HORIZONTAL   );
  hbxScale   .set_border_width  (                             3 );
  btLog      .set_label         ( "Log/Lin"                     );

  this               ->add         (  vbxCtlVert                    );
    vbxCtlVert        .pack_start  (  hbxScale,    Gtk::PACK_EXPAND_WIDGET );
      hbxScale        .pack_end    (  btLog,       Gtk::PACK_SHRINK        );
    vbxCtlVert        .pack_start  (  hbxSpan,     Gtk::PACK_SHRINK        );
      hbxSpan         .pack_start  ( *cbxBasis,    Gtk::PACK_SHRINK        );
      hbxSpan         .pack_start  (  etxSpanTop,  Gtk::PACK_SHRINK        );
    vbxCtlVert        .pack_start  (  grdVert,     Gtk::PACK_SHRINK        );

  return;
}

void    FrmSaVrt::InterConnect    ( void       ) {
  rshHoldOff = false;

  MRU_SaVrtRshAll = new CbT<FrmSaVrt>();
  MRU_SaVrtRshAll->SetCallback(this, &FrmSaVrt::SaVrtRshAll);
  ctMd->MSU_SaVrtRshAll = MRU_SaVrtRshAll;
  return;
}
void    FrmSaVrt::IntraConnect    ( void       ) {
  btLog.signal_clicked().connect(sigc::mem_fun(*this, &FrmSaVrt::OnLogLin));
  cbxBasis->signal_changed().connect( sigc::mem_fun(*this, &FrmSaVrt::OnBasis) );
  etxSpanTop.signal_focus_out_event().connect(sigc::mem_fun(*this, &FrmSaVrt::OnVoltTop));
  return;
}


void    FrmSaVrt::OnLogLin        ( void       ) {
  bool ll;
  if(rshHoldOff) return;
  ll = btLog.get_active();
  if(ll)
    ctSaVrt->SetLog();
  else
    ctSaVrt->SetLin();

  return;
}
void    FrmSaVrt::OnBasis         ( void       ) {
  ullong dex = this->cbxBasis->get_active_row_number();
  fprintf(stdout, "%s\n", mdSa->GetVrtModeStr(dex));
  return;
}
bool    FrmSaVrt::SaVrtRshAll     ( void *i_d  ) {
  rshHoldOff = true;
  //  for(int i=0; i<4; i++)
  //    lb[i].override_background_color(ctSaVrt->GetCol(i), Gtk::STATE_FLAG_NORMAL);
  //
  bool bb;
  bb = mdSa->IsALog();
  btLog.set_active(bb);
  rshHoldOff = false;
  return true;
}
bool    FrmSaVrt::OnVoltTop       ( GdkEventFocus* gdk_event) {
  char ss[32768];
  double dd;
  strcpy(ss, etxSpanTop.get_text().c_str());
  if(IsDoubleFixed(ss))
    sscanf(ss, "%lf", &dd);
  else
    dd = mdSa->GetAATop();
  ctSaVrt->SetVmax(dd);
  return false;
}
