
// $Id: PageRemez.cpp 634 2022-11-19 22:52:03Z duncang $

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

#include <caes/CaesString.hpp>

#include "PageRemez.hpp"

         PageRemez::PageRemez             ( Signal *i_sig  ) {
  MRU_RemezRshAll = NULL;
  BuildEnv     ( i_sig );
  BuildMain    (       );
  Connect      (       );
  OnRemezRshAll( NULL  );
}
         PageRemez::~PageRemez            ( void           ) {

}

void     PageRemez::BuildEnv            ( Signal *i_sig  ) {
  ctWave   = CtlWave     :: GetInstance(i_sig);
  ctRemez  = CtlRemez    :: GetInstance(i_sig);
  ctMd     = CtlMsgDspch :: GetInstance();
  return;
}
void     PageRemez::BuildMain           ( void           ) {
  this         ->set_orientation(Gtk::ORIENTATION_VERTICAL);

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
void     PageRemez::Connect             ( void           ) {

  ebxPbandRel    .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageRemez::OnChangePbandRel  ));
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

bool     PageRemez::OnChangePbandRel     ( GdkEventFocus  *i_e   ) {
  char   cc[32768];
  double dd;

  if(actionHoldoff) return false;
  strcpy(cc, (char *)ebxPbandRel.get_text().c_str());
  dd = ctRemez->GetPbEdge();
  if(IsDoubleFixed(cc))
    sscanf(cc, "%lf", &dd);
  ctRemez->SetPbEdge(dd);
  ctMd->MRD_RemezRshAll();
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

  if(ctWave->GetTypeRemez()) {
    ebxPbandRel .set_sensitive(true);
    ebxPbandAbs .set_sensitive(true);
    ebxXbandRel .set_sensitive(true);
    ebxXbandAbs .set_sensitive(true);
    ebxSbWtLin  .set_sensitive(true);
    ebxSbWtDb   .set_sensitive(true);
  }
  else {
    ebxPbandRel .set_sensitive(false);
    ebxPbandAbs .set_sensitive(false);
    ebxXbandRel .set_sensitive(false);
    ebxXbandAbs .set_sensitive(false);
    ebxSbWtLin  .set_sensitive(false);
    ebxSbWtDb   .set_sensitive(false);
 }


  actionHoldoff = false;
  return true;
}





