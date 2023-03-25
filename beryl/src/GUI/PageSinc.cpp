
// $Id: PageSinc.cpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : PageSinc.cpp
// Original Author    : duncang
// Creation Date      : 2017-04-16T15:57:59,514344111+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//    Pretty self descriptive, eh!?
//
//=================================================================================================

#include <caes/CaesString.hpp>

#include "PageSinc.hpp"

         PageSinc::PageSinc             ( Signal *i_sig  ) {
  MRU_SincRshAll = NULL;
  BuildEnv    ( i_sig );
  BuildMain   (       );
  Connect     (       );
  OnSincRshAll( NULL  );
}
         PageSinc::~PageSinc            ( void           ) {

}

void     PageSinc::BuildEnv            ( Signal *i_sig  ) {
  ctMd    = CtlMsgDspch :: GetInstance();
  ctWave  = CtlWave     :: GetInstance(i_sig);
  ctSinc  = CtlSinc     :: GetInstance(i_sig);
  return;
}
void     PageSinc::BuildMain           ( void           ) {
  this        ->set_orientation(Gtk::ORIENTATION_VERTICAL);

  hbxFreq      .set_orientation     (                      Gtk::ORIENTATION_HORIZONTAL   );
  lblFreqRel   .set_text            (                               " Cutoff (rel FS) "  );
  ebxFreqRel   .set_max_width_chars (                                                 9  );
  lblFreqAbs   .set_text            (                               "  (abs) "           );
  ebxFreqAbs   .set_max_width_chars (                                                 9  );


  this         ->pack_start          (  frmSig,            Gtk::PACK_SHRINK,          3  );
    frmSig      .add                 (  hbxFreq                                          );
      hbxFreq   .pack_start          (  lblFreqRel,        Gtk::PACK_SHRINK,          3  );
      hbxFreq   .pack_start          (  ebxFreqRel,        Gtk::PACK_SHRINK,          3  );
      hbxFreq   .pack_start          (  lblFreqAbs,        Gtk::PACK_SHRINK,          3  );
      hbxFreq   .pack_start          (  ebxFreqAbs,        Gtk::PACK_SHRINK,          3  );
  return;
}
void     PageSinc::Connect             ( void           ) {

  ebxFreqRel    .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageSinc::OnChangeFreqRel  ));
  ebxFreqAbs    .signal_focus_out_event  ().connect(sigc::mem_fun(*this, &PageSinc::OnChangeFreqAbs  ));


  MRU_SincRshAll = new CbT<PageSinc>();
  MRU_SincRshAll->SetCallback(this, &PageSinc::OnSincRshAll);
  ctMd->MSU_SincRshAll = MRU_SincRshAll;
  return;
}



bool     PageSinc::OnChangeFreqRel     ( GdkEventFocus  *i_e   ) {
  char   cc[32768];
  double dd;

  if(actionHoldoff) return false;
  strcpy(cc, (char *)ebxFreqRel.get_text().c_str());
  dd = ctSinc->GetFreq();
  if(IsDoubleFixed(cc))
    sscanf(cc, "%lf", &dd);
  ctSinc->SetFreq(dd);
  return false;
}
bool     PageSinc::OnChangeFreqAbs     ( GdkEventFocus  *i_e   ) {
  char  *cc;
  double dd;

  if(actionHoldoff) return false;
  cc = (char *)ebxFreqAbs.get_text().c_str();
  dd = ctSinc->GetFreq() * ctWave->GetFS();
  if(IsDoubleFixed(cc))
    sscanf(cc, "%lf", &dd);
  dd /= ctWave->GetFS();
  ctSinc->SetFreq(dd);
  return false;
}




bool     PageSinc::OnSincRshAll        ( void *i_d      ) {
  double dd;
  char   cc[32768];

  actionHoldoff = true;

  //fprintf(stderr, "PageSinc::OnSincRshAll()\n");fflush(stderr);
  //==
  dd = ctSinc->GetFreq();
  EngString(cc, dd, 6,  (char *)"");
  ebxFreqRel.set_text(cc);
  //==
  dd *= ctWave->GetFS();
  EngString(cc, dd, 6,  (char *)"");
  ebxFreqAbs.set_text(cc);

  if(ctWave->GetTypeSinc() || ctWave->GetTypeApSinc()) {
    ebxFreqRel .set_sensitive(true);
    ebxFreqAbs .set_sensitive(true);
  }
  else {
    ebxFreqRel .set_sensitive(false);
    ebxFreqAbs .set_sensitive(false);
  }


  actionHoldoff = false;
  return true;
}





