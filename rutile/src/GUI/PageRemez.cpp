
// $Id: PageRemez.cpp 588 2021-08-28 23:45:50Z duncang $

//=================================================================================================
// Original File Name : PageRemez.cpp
// Original Author    : duncang
// Creation Date      : 2017-03-12T14:56:47,226221993+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//    Pretty self descriptive, eh!?
//
//=================================================================================================

#include "PageRemez.hpp"

#include <caes/CaesString.hpp>

         PageRemez::PageRemez            ( Signal *i_sig  ) {
  MRU_RemezRshAll = NULL;
  BuildEnv     ( i_sig );
  BuildMain    (       );
  Connect      (       );
  OnRemezRshAll( NULL  );
}
         PageRemez::~PageRemez           ( void           ) {

}

void     PageRemez::BuildEnv             ( Signal *i_sig  ) {
  ctWave   = CtlWave     :: GetInstance(i_sig);
  ctRemez  = CtlRemez    :: GetInstance(i_sig);
  ctMd     = CtlMsgDspch :: GetInstance();
  return;
}
void     PageRemez::BuildMain            ( void           ) {
  char *tStr;
  tStr = new char[1024];

  this         ->set_orientation(Gtk::ORIENTATION_VERTICAL);

  grdBands    = new Gtk::Grid();
  lblBandBn  .set_text ( "b"      ); frmBandBnHd  .add(lblBandBn);
  lblBandSa  .set_text ( "Start"  ); frmBandSaHd  .add(lblBandSa);
  lblBandSr  .set_text ( "rel FS" ); frmBandSrHd  .add(lblBandSr);
  lblBandPa  .set_text ( "Stop"   ); frmBandPaHd  .add(lblBandPa);
  lblBandPr  .set_text ( "rel FS" ); frmBandPrHd  .add(lblBandPr);
  lblBandWa  .set_text ( "Weight" ); frmBandWaHd  .add(lblBandWa);
  lblBandWd  .set_text ( "dB"     ); frmBandWdHd  .add(lblBandWd);

  grdBands->insert_column(0);
  grdBands->insert_column(0);
  grdBands->insert_column(0);
  grdBands->insert_column(0);
  grdBands->insert_column(0);
  grdBands->insert_column(0);
  grdBands->insert_column(0);
  grdBands->insert_row(0);
  grdBands->attach(frmBandBnHd    , 0, 0, 1, 1);
  grdBands->attach(frmBandSaHd    , 1, 0, 1, 1);
  grdBands->attach(frmBandSrHd    , 2, 0, 1, 1);
  grdBands->attach(frmBandPaHd    , 3, 0, 1, 1);
  grdBands->attach(frmBandPrHd    , 4, 0, 1, 1);
  grdBands->attach(frmBandWaHd    , 5, 0, 1, 1);
  grdBands->attach(frmBandWdHd    , 6, 0, 1, 1);
  grdBands->set_column_homogeneous(true);

  lblBn = new Gtk::Label[NUM_BANDS];
  frmBn = new Gtk::Frame[NUM_BANDS];
  frmSa = new Gtk::Frame[NUM_BANDS];
  for(ullong i=0; i<NUM_BANDS; i++) {
    frmBn[i].set_border_width(0); sprintf(tStr, "%Ld", i); lblBn[i].set_text(tStr); frmBn[i].add(lblBn[i]);
    grdBands->attach(frmBn[i], 0, i+1, 1, 1);
    frmSa[i].set_border_width(0);
    grdBands->attach(frmSa[i], 1, i+1, 1, 1);
  }
  frmSa[0].add(ebxBandSa0);
  frmSa[1].add(ebxBandSa1);
  frmSa[2].add(ebxBandSa2);
  frmSa[3].add(ebxBandSa3);
  frmSa[4].add(ebxBandSa4);
  frmPband      .set_label           (                    " Passband Edge "              );
  hbxPband      .set_orientation     (                      Gtk::ORIENTATION_HORIZONTAL  );
  lblPbandRel   .set_text            (                    " PB Edge (rel FS) "           );
  ebxPbandRel   .set_max_width_chars (                                                9  );
  lblPbandAbs   .set_text            (                    " PB Edge (abs) "              );
  ebxPbandAbs   .set_max_width_chars (                                                9  );

  frmXband      .set_label           (                    " Transition Band Width "      );
  hbxXband      .set_orientation     (                      Gtk::ORIENTATION_HORIZONTAL  );
  lblXbandRel   .set_text            (                    " XB Width (rel FS) "          );
  ebxXbandRel   .set_max_width_chars (                                                9  );
  lblXbandAbs   .set_text            (                    " XB Width (abs) "             );
  ebxXbandAbs   .set_max_width_chars (                                                9  );


  frmSbWt       .set_label           (                    " Stopband Weighting "         );
  hbxSbWt       .set_orientation     (                      Gtk::ORIENTATION_HORIZONTAL  );
  lblSbWtLin    .set_text            (                    " SB Weight "                  );
  ebxSbWtLin    .set_max_width_chars (                                                9  );
  lblSbWtDb     .set_text            (                    " SB Weight (dB) "             );
  ebxSbWtDb     .set_max_width_chars (                                                8  );

  this         ->pack_start          ( *grdBands,          Gtk::PACK_EXPAND_WIDGET,   3  );
  this         ->pack_start          (  frmPband,          Gtk::PACK_SHRINK,          3  );
  this         ->pack_start          (  frmXband,          Gtk::PACK_SHRINK,          3  );
  this         ->pack_start          (  frmSbWt,           Gtk::PACK_SHRINK,          3  );
    frmPband    .add                 (  hbxPband                                         );
      hbxPband  .pack_start          (  lblPbandRel,       Gtk::PACK_SHRINK,          3  );
      hbxPband  .pack_start          (  ebxPbandRel,       Gtk::PACK_SHRINK,          3  );
      hbxPband  .pack_start          (  lblPbandAbs,       Gtk::PACK_SHRINK,          3  );
      hbxPband  .pack_start          (  ebxPbandAbs,       Gtk::PACK_SHRINK,          3  );
    frmXband    .add                 (  hbxXband                                         );
      hbxXband  .pack_start          (  lblXbandRel,       Gtk::PACK_SHRINK,          3  );
      hbxXband  .pack_start          (  ebxXbandRel,       Gtk::PACK_SHRINK,          3  );
      hbxXband  .pack_start          (  lblXbandAbs,       Gtk::PACK_SHRINK,          3  );
      hbxXband  .pack_start          (  ebxXbandAbs,       Gtk::PACK_SHRINK,          3  );
    frmSbWt     .add                 (  hbxSbWt                                          );
      hbxSbWt   .pack_start          (  lblSbWtLin,        Gtk::PACK_SHRINK,          3  );
      hbxSbWt   .pack_start          (  ebxSbWtLin,        Gtk::PACK_SHRINK,          3  );
      hbxSbWt   .pack_start          (  lblSbWtDb,         Gtk::PACK_SHRINK,          3  );
      hbxSbWt   .pack_start          (  ebxSbWtDb,         Gtk::PACK_SHRINK,          3  );
  return;
}
void     PageRemez::Connect              ( void           ) {

  ebxBandSa0     .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageRemez::OnChangeBandSa0  ));
  ebxBandSa1     .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageRemez::OnChangeBandSa1  ));
  ebxBandSa2     .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageRemez::OnChangeBandSa2  ));
  ebxBandSa3     .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageRemez::OnChangeBandSa3  ));
  ebxBandSa4     .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageRemez::OnChangeBandSa4  ));
  ebxPbandAbs    .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageRemez::OnChangePbandAbs  ));
  ebxXbandRel    .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageRemez::OnChangeXbandRel  ));
  ebxXbandAbs    .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageRemez::OnChangeXbandAbs  ));

  ebxSbWtLin     .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageRemez::OnChangeSbWtLin   ));
  ebxSbWtDb      .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageRemez::OnChangeSbWtDb    ));

  MRU_RemezRshAll = new CbT<PageRemez>();
  MRU_RemezRshAll->SetCallback(this, &PageRemez::OnRemezRshAll);
  ctMd->MSU_RemezRshAll = MRU_RemezRshAll;
  return;
}

void     PageRemez::OnChangeBandSa       ( llong i_b, char *i_cc) {
  double dd;

  dd = ctRemez->GetPbEdge();
  if(IsDoubleFixed(i_cc))
    sscanf(i_cc, "%lf", &dd);
  ctRemez->SetPbEdge(i_b, dd);
  ctMd->MRD_RemezRshAll();
  return;
}
bool     PageRemez::OnChangeBandSa0      ( GdkEventFocus  *i_e   ) {
  char   cc[32768];

  if(actionHoldoff) return false;
   strcpy(cc, (char *)ebxBandSa0.get_text().c_str());
  OnChangeBandSa(0, cc);
  return false;
}
bool     PageRemez::OnChangeBandSa1      ( GdkEventFocus  *i_e   ) {
  char   cc[32768];

  if(actionHoldoff) return false;
   strcpy(cc, (char *)ebxBandSa1.get_text().c_str());
  OnChangeBandSa(1, cc);
  return false;
}
bool     PageRemez::OnChangeBandSa2      ( GdkEventFocus  *i_e   ) {
  char   cc[32768];

  if(actionHoldoff) return false;
   strcpy(cc, (char *)ebxBandSa2.get_text().c_str());
  OnChangeBandSa(2, cc);
  return false;
}
bool     PageRemez::OnChangeBandSa3      ( GdkEventFocus  *i_e   ) {
  char   cc[32768];

  if(actionHoldoff) return false;
   strcpy(cc, (char *)ebxBandSa3.get_text().c_str());
  OnChangeBandSa(3, cc);
  return false;
}
bool     PageRemez::OnChangeBandSa4      ( GdkEventFocus  *i_e   ) {
  char   cc[32768];

  if(actionHoldoff) return false;
   strcpy(cc, (char *)ebxBandSa4.get_text().c_str());
  OnChangeBandSa(4, cc);
  return false;
}
bool     PageRemez::OnChangePbandAbs     ( GdkEventFocus  *i_e   ) {
  char  *cc;
  double dd;

  if(actionHoldoff) return false;
  cc = (char *)ebxPbandAbs.get_text().c_str();
  dd = 71.4;
  if(IsDoubleFixed(cc))
    sscanf(cc, "%lf", &dd);
  return false;
}

bool     PageRemez::OnChangeXbandRel     ( GdkEventFocus  *i_e   ) {
  char   cc[32768];
  double dd;

  if(actionHoldoff) return false;
  strcpy(cc, (char *)ebxXbandRel.get_text().c_str());
  dd = 53;
  if(IsDoubleFixed(cc))
    sscanf(cc, "%lf", &dd);
  dd = dd * 48000.0;
  return false;
}
bool     PageRemez::OnChangeXbandAbs     ( GdkEventFocus  *i_e   ) {
  char  *cc;
  double dd;

  if(actionHoldoff) return false;
  cc = (char *)ebxXbandAbs.get_text().c_str();
  dd = 71.4;
  if(IsDoubleFixed(cc))
    sscanf(cc, "%lf", &dd);
  return false;
}


bool     PageRemez::OnChangeSbWtLin      ( GdkEventFocus  *i_e   ) {
  char  *cc;
  double dd;

  if(actionHoldoff) return false;
  cc = (char *)ebxSbWtLin.get_text().c_str();
  dd = ctRemez->GetSbWeight();
  if(IsDoubleFixed(cc))
    sscanf(cc, "%lf", &dd);
  ctRemez->SetSbWeight(dd);
  return false;
}
bool     PageRemez::OnChangeSbWtDb       ( GdkEventFocus  *i_e   ) {
  char  *cc;
  double dd;

  if(actionHoldoff) return false;
  cc = (char *)ebxSbWtDb.get_text().c_str();
  dd = ctRemez->GetSbWeight();
  dd = 20.0 * log10(dd);
  if(IsDoubleFixed(cc))
    sscanf(cc, "%lf", &dd);
  dd = pow10(dd / 20.0);
  ctRemez->SetSbWeight(dd);
  return false;
}




bool     PageRemez::OnRemezRshAll        ( void *i_d      ) {
  double dd;
  double FS;
  char   cc[32768];

  actionHoldoff = true;
  FS = ctWave->GetFS();

  //fprintf(stderr, "PageRemez::OnRemezRshAll()\n");fflush(stderr);
  //==
  dd = ctRemez->GetPbEdge();
  EngString(cc, dd, 6,  (char *)"");
  ebxPbandRel.set_text(cc);
  //==
  dd *= FS;
  EngString(cc, dd, 6,  (char *)"");
  ebxPbandAbs.set_text(cc);
  //==
  dd = ctRemez->GetXbWidth();
  EngString(cc, dd, 6,  (char *)"");
  ebxXbandRel.set_text(cc);
  //==
  dd *= FS;
  EngString(cc, dd, 6,  (char *)"");
  ebxXbandAbs.set_text(cc);
  //==
  dd = ctRemez->GetSbWeight();
  EngString(cc, dd, 6,  (char *)"");
  ebxSbWtLin.set_text(cc);
  //==
  dd = 20.0 * log10(dd);
  sprintf(cc, "%7.4lf", dd);
  ebxSbWtDb.set_text(cc);


  actionHoldoff = false;
  return true;
}





