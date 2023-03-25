/*
 * PageNoise.cpp
 *
 *  Created on: Mar 7, 2017
 *      Author: duncang
 */

#include <caes/CaesString.hpp>

#include "PageNoise.hpp"

         PageNoise::PageNoise             ( Signal *i_sig  ) {
  MRU_NoiseRshAll = NULL;
  BuildEnv(i_sig);
  BuildMain();
  Connect();
  OnNoiseRshAll(NULL);
}
         PageNoise::~PageNoise            ( void           ) {

}

void     PageNoise::BuildEnv             ( Signal *i_sig  ) {
  ctWave  = CtlWave     :: GetInstance(i_sig);
  ctNoise = CtlNoise    :: GetInstance(i_sig);
  ctMd    = CtlMsgDspch :: GetInstance();
  return;
}
void     PageNoise::BuildMain            ( void          ) {
  set_orientation(Gtk::ORIENTATION_VERTICAL);

  hbxDist      .set_orientation     (                      Gtk::ORIENTATION_HORIZONTAL   );
  rbtDistGauss  = Gtk::manage       (new Gtk::RadioButton(rbgDistType, " Gaussian "     ));
  rbtDistRect   = Gtk::manage       (new Gtk::RadioButton(rbgDistType, " Rectangular "  ));
  lblRR        .set_text            (                               " Pearson's RR "     );
  ebxRR        .set_max_width_chars (                                                 8  );
  hbxDist      .pack_start          ( *rbtDistGauss,       Gtk::PACK_SHRINK,          3  );
  hbxDist      .pack_start          ( *rbtDistRect,        Gtk::PACK_SHRINK,          3  );
  hbxDist      .pack_start          (  lblRR,              Gtk::PACK_SHRINK,          3  );
  hbxDist      .pack_start          (  ebxRR,              Gtk::PACK_SHRINK,          3  );
  frmDist      .add                 (  hbxDist                                           );

  hbxAmp       .set_orientation     (                      Gtk::ORIENTATION_HORIZONTAL   );
  lblAmpLin    .set_text            (                               " Amplitude "        );
  ebxAmpLin    .set_max_width_chars (                                                18  );
  lblAmpDb     .set_text            (                               " Amplitude (dB)"    );
  ebxAmpDb     .set_max_width_chars (                                                 8  );
  hbxAmp       .pack_start          (  lblAmpLin,          Gtk::PACK_SHRINK,          3  );
  hbxAmp       .pack_start          (  ebxAmpLin,          Gtk::PACK_SHRINK,          3  );
  hbxAmp       .pack_start          (  lblAmpDb,           Gtk::PACK_SHRINK,          3  );
  hbxAmp       .pack_start          (  ebxAmpDb,           Gtk::PACK_SHRINK,          3  );
  frmAmp       .add                 (  hbxAmp                                            );

                pack_start          (  frmDist,            Gtk::PACK_SHRINK,          3  );
                pack_start          (  frmAmp,             Gtk::PACK_SHRINK,          3  );

  return;
}
void     PageNoise::Connect              ( void          ) {

  rbtDistGauss ->signal_toggled          ().connect(sigc::mem_fun(*this, &PageNoise::OnChangeShape    ));

  ebxRR         .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageNoise::OnChangeRR       ));

  ebxAmpLin     .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageNoise::OnChangeAmpLin   ));
  ebxAmpDb      .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageNoise::OnChangeAmpDb    ));

  MRU_NoiseRshAll = new CbT<PageNoise>();
  MRU_NoiseRshAll->SetCallback(this, &PageNoise::OnNoiseRshAll);
  ctMd->MSU_NoiseRshAll = MRU_NoiseRshAll;
  return;
}


void     PageNoise::OnChangeShape        ( void          ) {
  if(actionHoldoff) return;
  if(rbtDistGauss->get_active())
    ctNoise->SetShapeGauss();
  else
    ctNoise->SetShapeRect();
  return;
}

bool     PageNoise::OnChangeRR          ( GdkEventFocus  *i_e   ) {
  char  *cc;
  double dd;

  if(actionHoldoff) return false;
  actionHoldoff = true;
  cc = (char *)ebxRR.get_text().c_str();
  dd = ctNoise->GetRR();
  if(IsDoubleFixed(cc))
    sscanf(cc, "%lf", &dd);
  ctNoise->SetRR(dd);
  actionHoldoff = false;
  return false;
}

bool     PageNoise::OnChangeAmpLin      ( GdkEventFocus  *i_e   ) {
  char  *cc;
  double dd;

  if(actionHoldoff) return false;
  cc = (char *)ebxAmpLin.get_text().c_str();
  dd = ctNoise->GetLevel();
  if(IsDoubleFixed(cc))
    sscanf(cc, "%lf", &dd);
  ctNoise->SetLevel(dd);
  return false;
}
bool     PageNoise::OnChangeAmpDb       ( GdkEventFocus  *i_e   ) {
  char  *cc;
  double dd;

  if(actionHoldoff) return false;
  cc = (char *)ebxAmpDb.get_text().c_str();
  dd = 20.0 * log10(ctNoise->GetLevel());
  if(IsDoubleFixed(cc))
    sscanf(cc, "%lf", &dd);
  dd = pow10(dd / 20.0);
  ctNoise->SetLevel(dd);
  return false;
}





bool     PageNoise::OnNoiseRshAll    ( void *i_d     ) {
  double dd;
  char   cc[32768];

  actionHoldoff = true;


  //fprintf(stderr, "PageNoise::OnNoiseRshAll()\n");fflush(stderr);
  //==
  if(ctNoise->ShapeIsGauss())
    rbtDistGauss->set_active(true);
  else
    rbtDistRect->set_active(true);
  //==
  dd = ctNoise->GetRR();
  EngString(cc, dd, 6,  (char *)"");
  ebxRR.set_text(cc);
  //==
  dd = ctNoise->GetLevel();
  EngString(cc, dd, 6,  (char *)"");
  ebxAmpLin.set_text(cc);
  //==
  dd = 20.0 * log10(dd);
  sprintf(cc, "%7.4lf", dd);
  ebxAmpDb.set_text(cc);

  if(ctWave->GetTypeSource() || ctWave->GetTypeApSrc()) {
    rbtDistGauss ->set_sensitive(true);
    rbtDistRect  ->set_sensitive(true);
    ebxRR         .set_sensitive(true);
    ebxAmpLin     .set_sensitive(true);
    ebxAmpDb      .set_sensitive(true);
  }
  else {
    rbtDistGauss ->set_sensitive(false);
    rbtDistRect  ->set_sensitive(false);
    ebxRR         .set_sensitive(false);
    ebxAmpLin     .set_sensitive(false);
    ebxAmpDb      .set_sensitive(false);
  }

    actionHoldoff = false;
  return true;
}





