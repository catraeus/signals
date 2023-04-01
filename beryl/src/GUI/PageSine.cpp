
// $Id: PageSine.cpp 696 2022-12-29 02:46:51Z duncang $

//=================================================================================================
// Original File Name : PageSine.cpp
// Original Author    : duncang
// Creation Date      : 2017-03-12T14:56:47,226221993+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//    Pretty self descriptive, eh!?
//
//=================================================================================================

#include <caes/CaesString.hpp>

#include "PageSine.hpp"

         PageSine::PageSine            ( Signal *i_sig  )
: sig (i_sig) {
  MRU_SineRshAll = NULL;
  BuildEnv     (      );
  BuildMain    (      );
  Connect      (      );
  OnSineRshAll ( NULL );
}
         PageSine::~PageSine           ( void           ) {

}

void     PageSine::BuildEnv            ( void           ) {
  ctWave  = CtlWave     :: GetInstance(sig);
  ctSine  = CtlSine     :: GetInstance(sig);
  ctMd    = CtlMsgDspch :: GetInstance();
  return;
}
void     PageSine::BuildMain           ( void           ) {
  set_orientation(Gtk::ORIENTATION_VERTICAL);

  hbxFreq      .set_orientation     (                      Gtk::ORIENTATION_HORIZONTAL   );
  lblFS        .set_text            (                               " FS "               );
  ebxFS        .set_max_width_chars (                                                 9  );
  ebxFS        .set_sensitive       (  false                                             );
  lblFreqRel   .set_text            (                               " F (FS) "           );
  ebxFreqRel   .set_max_width_chars (                                                 9  );
  lblFreqAbs   .set_text            (                               " Freq (abs) "       );
  ebxFreqAbs   .set_max_width_chars (                                                 9  );
  lblFreqN     .set_text            (                               " Freq (N) "         );
  ebxFreqN     .set_max_width_chars (                                                 9  );
  hbxFreq      .pack_start          (  lblFS,              Gtk::PACK_SHRINK,          3  );
  hbxFreq      .pack_start          (  ebxFS,              Gtk::PACK_SHRINK,          3  );
  hbxFreq      .pack_start          (  lblFreqRel,         Gtk::PACK_SHRINK,          3  );
  hbxFreq      .pack_start          (  ebxFreqRel,         Gtk::PACK_SHRINK,          3  );
  hbxFreq      .pack_start          (  lblFreqAbs,         Gtk::PACK_SHRINK,          3  );
  hbxFreq      .pack_start          (  ebxFreqAbs,         Gtk::PACK_SHRINK,          3  );
  hbxFreq      .pack_start          (  lblFreqN,           Gtk::PACK_SHRINK,          3  );
  hbxFreq      .pack_start          (  ebxFreqN,           Gtk::PACK_SHRINK,          3  );
  frmFreq      .add                 (  hbxFreq                                           );

  hbxAmp       .set_orientation     (                      Gtk::ORIENTATION_HORIZONTAL   );
  lblAmpLin    .set_text            (                               " Amplitude "        );
  ebxAmpLin    .set_max_width_chars (                                                18  );
  lblAmpDb     .set_text            (                                " Amplitude (dB)"   );
  ebxAmpDb     .set_max_width_chars (                                                 8  );
  rbtSelSinCosSin   = Gtk::manage   (new Gtk::RadioButton(rbgSinCos, "sin "             ));
  rbtSelSinCosCos   = Gtk::manage   (new Gtk::RadioButton(rbgSinCos, "cos "             ));
  rbtSelSinCosIQ    = Gtk::manage   (new Gtk::RadioButton(rbgSinCos, "IQ "              ));
  lblSinSep    .set_text            (                                "|"                 );
  rbtZeroStart      = Gtk::manage   (new Gtk::RadioButton(rbgZero,   "Start "           ));
  rbtZeroCenter     = Gtk::manage   (new Gtk::RadioButton(rbgZero,   "Center "          ));
  hbxAmp       .pack_start          (  lblAmpLin,          Gtk::PACK_SHRINK,          3  );
  hbxAmp       .pack_start          (  ebxAmpLin,          Gtk::PACK_SHRINK,          3  );
  hbxAmp       .pack_start          (  lblAmpDb,           Gtk::PACK_SHRINK,          3  );
  hbxAmp       .pack_start          (  ebxAmpDb,           Gtk::PACK_SHRINK,          3  );
  hbxAmp       .pack_start          ( *rbtSelSinCosSin,    Gtk::PACK_SHRINK,          3  );
  hbxAmp       .pack_start          ( *rbtSelSinCosCos,    Gtk::PACK_SHRINK,          3  );
  hbxAmp       .pack_start          ( *rbtSelSinCosIQ,    Gtk::PACK_SHRINK,          3  );
  hbxAmp       .pack_start          (  lblSinSep,          Gtk::PACK_SHRINK,          3  );
  hbxAmp       .pack_start          ( *rbtZeroStart,       Gtk::PACK_SHRINK,          3  );
  hbxAmp       .pack_start          ( *rbtZeroCenter,      Gtk::PACK_SHRINK,          3  );
  frmAmp       .add                 (  hbxAmp                                            );

                pack_start          (  frmFreq,            Gtk::PACK_SHRINK,          3  );
                pack_start          (  frmAmp,             Gtk::PACK_SHRINK,          3  );

  return;
}
void     PageSine::Connect             ( void           ) {

  ebxFreqRel    .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageSine::OnChangeFreqRel  ));
  ebxFreqAbs    .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageSine::OnChangeFreqAbs  ));
  ebxFreqN      .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageSine::OnChangeFreqN    ));

  ebxAmpLin     .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageSine::OnChangeAmpLin   ));
  ebxAmpDb      .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageSine::OnChangeAmpDb    ));

  rbtSelSinCosSin      ->signal_toggled  ().connect(sigc::mem_fun(*this, &PageSine::OnChangeSinCosSin  ));
  rbtSelSinCosCos      ->signal_toggled  ().connect(sigc::mem_fun(*this, &PageSine::OnChangeSinCosCos  ));
  rbtSelSinCosIQ       ->signal_toggled  ().connect(sigc::mem_fun(*this, &PageSine::OnChangeSinCosIQ   ));

  rbtZeroStart         ->signal_toggled  ().connect(sigc::mem_fun(*this, &PageSine::OnChangeZeroStart  ));
  rbtZeroCenter        ->signal_toggled  ().connect(sigc::mem_fun(*this, &PageSine::OnChangeZeroCenter ));

  MRU_SineRshAll = new CbT<PageSine>();
  MRU_SineRshAll->SetCallback(this, &PageSine::OnSineRshAll);
  ctMd->MSU_SineRshAll = MRU_SineRshAll;
  return;
}



bool     PageSine::OnChangeFreqRel     ( GdkEventFocus  *i_e   ) {
  char   cc[128];
  double fSet;

  if(actionHoldoff) return false;
  strcpy(cc, (char *)ebxFreqRel.get_text().c_str());
  fSet = ctSine->GetFreqSine(1);
  if(IsDoubleFixed(cc)) {
    sscanf(cc, "%lf", &fSet);
  }
  fprintf(stderr, "\n\nPageSine::OnChangeFreqRel(f: %lf)\n\n", fSet); fflush(stderr);
  actionHoldoff = true;
  ctSine->SetFreqSine(1, fSet);
  actionHoldoff = false;
  return false;
}
bool     PageSine::OnChangeFreqAbs     ( GdkEventFocus  *i_e   ) {
  char  *cc;
  double fSet;
  double fFS;

  if(actionHoldoff) return false;
  cc  = (char *)ebxFreqAbs.get_text().c_str();
  fSet = ctSine->GetFreqSine(1);
  fFS = sig->GetFS();
  if(IsDoubleFixed(cc)) {
    sscanf(cc, "%lf", &fSet);
    fSet /= fFS;
  }
  fprintf(stderr, "\n\nPageSine::OnChangeFreqAbs(f: %lf)\n\n", fSet); fflush(stderr);
  actionHoldoff = true;
  ctSine->SetFreqSine(1, fSet);
  actionHoldoff = false;
  return false;
}
bool     PageSine::OnChangeFreqN       ( GdkEventFocus  *i_e   ) {
  char  *cc;
  double fSet;

  if(actionHoldoff) return false;
  cc = (char *)ebxFreqN.get_text().c_str();
  fSet = ctSine->GetFreqSine(1);
  if(IsDoubleFixed(cc)) {
    sscanf(cc, "%lf", &fSet);
    fSet = 1.0 / fSet;
  }
  fprintf(stderr, "\n\nPageSine::OnChangeFreqN(f: %lf)\n\n", fSet); fflush(stderr);
  actionHoldoff = true;
  ctSine->SetFreqSine(1, fSet);
  actionHoldoff = false;
  return false;
}
bool     PageSine::OnChangeAmpLin      ( GdkEventFocus  *i_e   ) {
  char  *cc;
  double dd;

  if(actionHoldoff) return false;
  cc = (char *)ebxAmpLin.get_text().c_str();
  dd = ctSine->GetLvlPhasor(1);
  if(IsDoubleFixed(cc))
    sscanf(cc, "%lf", &dd);
  if(rbtSelSinCosSin->get_active()) {
    ctSine->SetLvlCos(1, dd);
    ctSine->SetLvlSin(1, 0.0);
  }
  else {
    ctSine->SetLvlCos(1, 0.0);
    ctSine->SetLvlSin(1, dd);
  }
  return false;
}
bool     PageSine::OnChangeAmpDb       ( GdkEventFocus  *i_e   ) {
  char  *cc;
  double dd;

  if(actionHoldoff) return false;
  cc = (char *)ebxAmpDb.get_text().c_str();
  dd = 20.0 * log10(ctSine->GetLvlCos(1));
  if(IsDoubleFixed(cc))
    sscanf(cc, "%lf", &dd);
  dd = pow10(dd / 20.0);
  if(rbtSelSinCosSin->get_active()) {
    ctSine->SetLvlCos(1, dd);
    ctSine->SetLvlSin(1, 0.0);
  }
  else {
    ctSine->SetLvlCos(1, 0.0);
    ctSine->SetLvlSin(1, dd);
  }
  return false;
}
void     PageSine::OnChangeSinCosSin   ( void                  ) {
  double dd;
  if(actionHoldoff) return;
  actionHoldoff = true;
  if(rbtSelSinCosSin->get_active()) {
    dd = ctSine->GetLvlPhasor(1);
    ctSine->SetLvlCos(1, 0.0);
    ctSine->SetLvlSin(1, dd);
    ctSine->SetQuadrature(false);
    fprintf(stderr, "boink\n");
  }
  actionHoldoff = false;
  return;
}
void     PageSine::OnChangeSinCosCos   ( void                  ) {
  double dd;
  if(actionHoldoff) return;
  actionHoldoff = true;
  if(rbtSelSinCosCos->get_active()) {
    dd = ctSine->GetLvlPhasor(1);
    ctSine->SetLvlCos(1, dd);
    ctSine->SetLvlSin(1, 0.0);
    ctSine->SetQuadrature(false);
    fprintf(stderr, "doink\n");
  }
  actionHoldoff = false;
  return;
}
void     PageSine::OnChangeSinCosIQ    ( void                  ) {
  double dd;
  if(actionHoldoff) return;
  actionHoldoff = true;
  if(rbtSelSinCosIQ->get_active()) {
    dd = ctSine->GetLvlPhasor(1);
    dd *= SQv2;
    ctSine->SetLvlCos(1, dd);
    ctSine->SetLvlSin(1, dd);
    ctSine->SetQuadrature(true);
    fprintf(stderr, "doink\n");
  }
  actionHoldoff = false;
  return;
}
void     PageSine::OnChangeZeroStart   ( void                  ) {
  if(actionHoldoff) return;
  actionHoldoff = true;
  if(rbtZeroStart->get_active()) {
    ctSine->SetCentered(false);
  }
  actionHoldoff = false;
  return;
}
void     PageSine::OnChangeZeroCenter  ( void                  ) {
  if(actionHoldoff) return;
  actionHoldoff = true;
  if(rbtZeroCenter->get_active()) {
    ctSine->SetCentered(true);
  }
  actionHoldoff = false;
  return;
}


bool     PageSine::OnSineRshAll        ( void *i_d      ) {
  double dd;
  double fFS;
  double fRelFS;
  double fAbs;
  double fN;
  char   cc[128];

  actionHoldoff = true;

  fFS    = sig->GetFS();
  fRelFS = ctSine->GetFreqSine(1);
  fAbs   = fRelFS * fFS;
  fN     = 1.0 / fRelFS;

  //fprintf(stderr, "PageSine::OnSineRshAll()\n");fflush(stderr);
  //==
  EngString(cc, fFS, 6,  (char *)"");
  ebxFS.set_text(cc);
  //==
  EngString(cc, fRelFS, 6,  (char *)"");
  ebxFreqRel.set_text(cc);
  //==
  EngString(cc, fAbs, 6,  (char *)"");
  ebxFreqAbs.set_text(cc);
  //==
  EngString(cc, fN, 6,  (char *)"");
  ebxFreqN.set_text(cc);
  //==
  dd = ctSine->GetLvlPhasor(1);
  EngString(cc, dd, 6,  (char *)"");
  ebxAmpLin.set_text(cc);
  //==
  dd = abs(dd);
  dd = 20.0 * log10(dd);
  sprintf(cc, "%7.4lf", dd);
  ebxAmpDb.set_text(cc);

  if(ctWave->GetTypeSource() || ctWave->GetTypeApSrc()) {
    ebxFS      .set_sensitive(false); // FIXME Make this work.  Call to ctWave->SetFS()
    ebxFreqRel .set_sensitive(true);
    ebxFreqAbs .set_sensitive(true);
    ebxAmpLin  .set_sensitive(true);
    ebxAmpDb   .set_sensitive(true);
  }
  else {
    ebxFS      .set_sensitive(false);
    ebxFreqRel .set_sensitive(false);
    ebxFreqAbs .set_sensitive(false);
    ebxAmpLin  .set_sensitive(false);
    ebxAmpDb   .set_sensitive(false);
  }


  actionHoldoff = false;
  return true;
}





