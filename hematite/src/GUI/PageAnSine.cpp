
// $Id: PageAnSine.cpp 757 2023-03-25 01:15:02Z duncang $

//=================================================================================================
// Original File Name : PageAnSine.cpp
// Original Author    : duncang
// Creation Date      : Aug 18, 2012
// Copyright          : Copyright © 2011 - 2019 by Catraeus and Duncan Gray
//
// Description        :
//    The page for the Sinusoid Analyzer.
//
//=================================================================================================

#include <math.h>

#include <caes/CaesString.hpp>

#include "PageAnSine.hpp"
#include "WinMain.hpp"

        PageAnSine::PageAnSine        ( Signal *i_sigRaw, Signal *i_sigNorm, Signal *i_sigCarr, Signal *i_sigBase, Signal *i_sigDem, AnSine *i_anSine )
: sigRaw    ( i_sigRaw   )
, sigNorm   ( i_sigNorm  )
, sigCarr   ( i_sigCarr  )
, sigBase   ( i_sigBase  )
, sigDem    ( i_sigDem   )
, anSine   ( i_anSine  ) {
  BuildEnv ();
  BuildMain();
  Connect  ();
  return;
  }
        PageAnSine::~PageAnSine       ( void         ) {
  }
void    PageAnSine::FillStats          ( void         ) {
  char   tStr[256];
  double ddd;
  dirty = false;

  ddd =         1.0 / anSine->GetMean (0);        sprintf  (tStr, "%lf"  , ddd                  );  ebxZerFrq0    .set_text(tStr);
  ddd = ConvertJitUi (anSine->GetStDev(0));       EngString(tStr,          ddd, 3, (char *)" ui");  ebxZerRmsUi0  .set_text(tStr);
  ddd = ConvertJitSec(anSine->GetStDev(0));       EngString(tStr,          ddd, 3, (char *)"s"  );  ebxZerRmsSec0 .set_text(tStr);
                                                  sprintf  (tStr, "%lf"  , 0.0                  );  ebxZerAmpCar0 .set_text(tStr);
                                                  sprintf  (tStr, "%lf"  , 0.0                  );  ebxZeraPk0    .set_text(tStr);
  ddd =               anSine->GetPhase(0) ;       EngString(tStr,          ddd, 3, (char *)"º"  );  ebxZeraPh0    .set_text(tStr);

  if(sigNorm->GetCh() == 2) {
    sprintf(tStr, "%lf", 0.0);    ebxPrr.set_text(tStr);

    ddd =         1.0 / anSine->GetMean (1);        sprintf  (tStr, "%lf"  , ddd                  );  ebxZerFrq1    .set_text(tStr);
    ddd = ConvertJitUi (anSine->GetStDev(1));       EngString(tStr,          ddd, 3, (char *)" ui");  ebxZerRmsUi1  .set_text(tStr);
    ddd = ConvertJitSec(anSine->GetStDev(1));       EngString(tStr,          ddd, 3, (char *)"s"  );  ebxZerRmsSec1 .set_text(tStr);
                                                    sprintf  (tStr, "%lf",   0.0                  );  ebxZerAmpCar1 .set_text(tStr);
                                                    sprintf  (tStr, "%lf",   0.0                  );  ebxZeraPk1    .set_text(tStr);
    ddd =               anSine->GetPhase(1) ;       EngString(tStr,          ddd, 3, (char *)"º"  );  ebxZeraPh1    .set_text(tStr);
  }
  else {
    ebxPrr          .set_text("");
    ebxZerFrq1      .set_text("");
    ebxZerRmsUi1    .set_text("");
    ebxZerRmsSec1   .set_text("");
    ebxZerRmsSec1   .set_text("");
    ebxZerAmpCar1   .set_text("");
    ebxZeraPk1      .set_text("");
    ebxZeraPh1      .set_text("");
  }

  return;
}
double  PageAnSine::ConvertJitUi       ( llong   i_ch ) {
  return anSine->GetStDev(i_ch) / anSine->GetMean(i_ch);
}
double  PageAnSine::ConvertJitSec      ( llong   i_ch ) {
  return anSine->GetStDev(i_ch);
}
void    PageAnSine::OnEstZerXrs        ( void         ) {
  anSine->EstZerXcr();
  dirty = true;
  FillStats();
  return;
}
void    PageAnSine::OnFilter           ( void         ) {
  anSine->DemFiltCarr();
  return;
}
void    PageAnSine::OnDemod            ( void         ) {
  anSine->DemCmplx();
  return;
}
void    PageAnSine::OnBaseFilt         ( void         ) {
  anSine->DemFiltBase();
  return;
}
void    PageAnSine::OnDemDecim         ( void         ) {
  anSine->DemDecimate();
  return;
}

void    PageAnSine::OnIndIQ            ( void         ) {
  eAnType newAnType;
  if     (rbtAnTypeIndep->get_active()) {
    newAnType = NT_INDEP;
    rbtCh0->set_sensitive(0);
    rbtCh1->set_sensitive(0);
    ebxCarrFreq.set_sensitive(0);
    ebxCarrAnBW.set_sensitive(0);
    hasCarr = false;
    ebxCarrFreq.set_editable(false);
    ebxCarrFreq.set_sensitive(0);
    evSetCarrFreq.disconnect();
    ebxCarrFreq.set_text("");
    ebxCarrAnBW.set_editable(false);
    ebxCarrAnBW.set_sensitive(0);
    evSetCarrAnBW.disconnect();
    ebxCarrAnBW.set_text("");
  }
  else if(rbtAnTypeIQ->get_active()) { // WARNING this and Indep are very close to identical settings, keep them tracking.
    newAnType = NT_IQ;
    rbtCh0->set_sensitive(0);
    rbtCh1->set_sensitive(0);
    hasCarr = false;
    ebxCarrFreq.set_editable(false);
    ebxCarrFreq.set_sensitive(0);
    evSetCarrFreq.disconnect();
    ebxCarrFreq.set_text("");
    ebxCarrAnBW.set_editable(false);
    ebxCarrAnBW.set_sensitive(0);
    evSetCarrAnBW.disconnect();
    ebxCarrAnBW.set_text("");
  }
  else if(rbtAnTypeCarr->get_active()) {
    newAnType = NT_CARR;
    rbtCh0->set_sensitive(1);
    rbtCh1->set_sensitive(1);
    hasCarr = true;
    ebxCarrFreq.set_editable(true);
    ebxCarrFreq.set_sensitive(1);
    evSetCarrFreq = ebxCarrFreq.signal_focus_out_event().connect(sigc::mem_fun(*this,  &PageAnSine    ::OnSetCarrFreq    ));
    ebxCarrFreq.set_text("1k00");
    ebxCarrAnBW.set_editable(true);
    ebxCarrAnBW.set_sensitive(1);
    evSetCarrAnBW = ebxCarrAnBW.signal_focus_out_event().connect(sigc::mem_fun(*this,  &PageAnSine    ::OnSetAnBW        ));
    ebxCarrAnBW.set_text("1k00");
  }
  else
    newAnType = NT_INVALID;

  if(newAnType == anType) {
    if(!dirty)
      return;
    }
  anType = newAnType;
  return;
}
void    PageAnSine::OnCarrChChoose     ( void        ) {
  eChCh newIqCh;
  if     (rbtCh0->get_active())
    newIqCh = CT_CH0;
  else if(rbtCh1->get_active())
    newIqCh = CT_CH1;
  else
    newIqCh = CT_INVALID;

  if(newIqCh == iqCh) {
    if(!dirty)
      return;
    }
  iqCh = newIqCh;
  return;
}
bool    PageAnSine::OnSetCarrFreq      ( GdkEventFocus *i_theEvent ) {
  char tStr[32];
  bool isGoodNum;

  (void)i_theEvent;
  strcpy(tStr, ebxCarrFreq.get_text().c_str());
  if(!ebxCarrFreq.has_focus()) {
    double dT;
    isGoodNum = StringEng(tStr, &dT);
    if(!isGoodNum) {
      dT = anSine->GetCarrFreq();
      fprintf(stderr, "No Good  %s\n", tStr); fflush(stderr);
    }
    else {
      anSine->SetCarrFreq(dT);
    }
    fprintf(stderr, "Setting Carrier Frequency  %s   %lf\n", tStr, dT); fflush(stderr);
  }
  ClearStats();
  return true;
}
bool    PageAnSine::OnSetAnBW          ( GdkEventFocus *i_theEvent ) {
  char tStr[32];
  double tD;

  (void)i_theEvent;
  strcpy(tStr, ebxCarrAnBW.get_text().c_str());
  if(ebxCarrAnBW.has_focus()) {
    fprintf(stderr, "AnBW Phantom\n"); fflush(stderr);
  }
  else {
    fprintf(stderr, "AnBW For Us:  %s\n", tStr); fflush(stderr);
    bool looksGood = StringEng(tStr, &tD);
    if(looksGood) {
      anSine->SetAnBW(tD);
      if(tD == anSine->GetAnBW()) {
        fprintf(stderr, "AnBW Looks Good  %lf\n", tD); fflush(stderr);
      }
      else {
        fprintf(stderr, "AnBW Needed Adjustment from %lf  to  %lf\n", tD, anSine->GetAnBW()); fflush(stderr);
        tD = anSine->GetAnBW();
      }
    }
  }
  ClearStats();
  return true;
}


bool    PageAnSine::HndlSineVoid      ( void   *     ) {
  SetDirty();
  ClearStats();
  return true;
}

void    PageAnSine::ReScale            ( void         ) {
  FillStats();
  return;
}
void    PageAnSine::ClearStats         ( void         ) {

  if(!dirty)
    return;
  dirty = false;

  ebxPrr          .set_text("");

  ebxZerFrq0      .set_text("");
  ebxZerFrq1      .set_text("");
  ebxZerRmsUi0    .set_text("");
  ebxZerRmsUi1    .set_text("");
  ebxZerRmsSec0   .set_text("");
  ebxZerRmsSec1   .set_text("");
  ebxZerAmpCar0   .set_text("");
  ebxZerAmpCar1   .set_text("");
  ebxZeraPk0      .set_text("");
  ebxZeraPk1      .set_text("");



  return;
  }
void    PageAnSine::BuildEnv           ( void         ) {
  dirty      = true;
  ctMd       = CtlMsgDspch::GetInstance();
  iqCh       = CT_INVALID;
  return;
}
void    PageAnSine::BuildMain          ( void         ) {

  HnCbSineVoid = new CbT<PageAnSine>;


  set_orientation(Gtk::ORIENTATION_VERTICAL);
  //========================================================================
  //========================================================================
  //  Set up the whole shebang of the File vertical box

  btCalcEstZerXrs = new Gtk::Button("Est Zer Cross");
  btCalcFilter    = new Gtk::Button("Filter");
  btCalcDemod     = new Gtk::Button("Demod");
  btCalcBaseFilt  = new Gtk::Button("Base Band Filter");
  btCalcDemDecim  = new Gtk::Button("Decimate");


//============== Vertical for Analysis Setup and Action
  vbxAnSetup      .  set_orientation     ( Gtk::ORIENTATION_VERTICAL        );

  frmAnType       .  set_label           ( "Analysis"                       );
  vbxAnType       .  set_orientation     ( Gtk::ORIENTATION_VERTICAL        );

  frmAnCarr       .  set_label           ( "Carrier"                       );
  vbxAnCarr       .  set_orientation     ( Gtk::ORIENTATION_VERTICAL        );
  hbxAnTypePad    .  set_orientation     ( Gtk::ORIENTATION_HORIZONTAL      );




  rbtAnTypeIndep  = new Gtk::RadioButton ("Independent"                     );
  rbtAnTypeIQ     = new Gtk::RadioButton ("Complex IQ"                      );
  rbtAnTypeCarr   = new Gtk::RadioButton ("Demodulate"                      );

  hbxChChoose     .  set_orientation     ( Gtk::ORIENTATION_HORIZONTAL      );
  rbtCh0          = new Gtk::RadioButton ("ch1");
  rbtCh1          = new Gtk::RadioButton ("ch2");
  rbtCh0          -> set_sensitive(0);
  rbtCh1          -> set_sensitive(0);

  rbgpChChoose    =  rbtCh0->get_group();
  rbtCh1          -> set_group(rbgpChChoose);
  lblCarrFreq     .  set_text            ("Carrier Freq."                   );
  ebxCarrFreq     .  set_width_chars     (13                                );
  ebxCarrFreq     .  set_editable        (false                             );
  ebxCarrFreq     .  set_sensitive       (0                                 );
  lblCarrAnBW     .  set_text            ("Analysis BW"                     );
  ebxCarrAnBW     .  set_width_chars     (13                                );
  ebxCarrAnBW     .  set_editable        (false                             );
  ebxCarrAnBW     .  set_sensitive       (0                                 );


  rbgpAnType      =  rbtAnTypeIndep->get_group();
  rbtAnTypeIQ     -> set_group(rbgpAnType);
  rbtAnTypeCarr   -> set_group(rbgpAnType);

  hbxSine      .set_orientation ( Gtk::ORIENTATION_HORIZONTAL );
  vbxCtlOv      .set_orientation ( Gtk::ORIENTATION_VERTICAL   );
  hbxSine      .set_orientation ( Gtk::ORIENTATION_HORIZONTAL );
  vbxZer0       .set_orientation ( Gtk::ORIENTATION_VERTICAL   );
  vbxZer1       .set_orientation ( Gtk::ORIENTATION_VERTICAL   );
  hbxZerFrq0    .set_orientation ( Gtk::ORIENTATION_HORIZONTAL );
  hbxZerFrq1    .set_orientation ( Gtk::ORIENTATION_HORIZONTAL );
  hbxZerRmsUi0  .set_orientation ( Gtk::ORIENTATION_HORIZONTAL );
  hbxZerRmsUi1  .set_orientation ( Gtk::ORIENTATION_HORIZONTAL );
  hbxZerRmsSec0 .set_orientation ( Gtk::ORIENTATION_HORIZONTAL );
  hbxZerRmsSec1 .set_orientation ( Gtk::ORIENTATION_HORIZONTAL );
  hbxZerAmpCar0 .set_orientation ( Gtk::ORIENTATION_HORIZONTAL );
  hbxZerAmpCar1 .set_orientation ( Gtk::ORIENTATION_HORIZONTAL );
  hbxZeraPk0    .set_orientation ( Gtk::ORIENTATION_HORIZONTAL );
  hbxZeraPk1    .set_orientation ( Gtk::ORIENTATION_HORIZONTAL );
  hbxZeraPh0    .set_orientation ( Gtk::ORIENTATION_HORIZONTAL );
  hbxZeraPh1    .set_orientation ( Gtk::ORIENTATION_HORIZONTAL );

  frmZer0       .set_label ("Channel 0 - ZC" );
  frmZer1       .set_label ("Channel 1 - ZC" );

  lblPrr        .set_text  ("A/P RR:"        );   lblPrr     .set_width_chars ( 13 );   lblPrr     .set_alignment ( Gtk::ALIGN_START );
  lblFrq        .set_text  ("Freq:"          );   lblFrq     .set_width_chars ( 10 );   lblFrq     .set_alignment ( Gtk::ALIGN_END   );
  lblRmsUi      .set_text  ("RMS(ui):"       );   lblRmsUi   .set_width_chars ( 10 );   lblRmsUi   .set_alignment ( Gtk::ALIGN_END   );
  lblRmsSec     .set_text  ("RMS(sec):"      );   lblRmsSec  .set_width_chars ( 10 );   lblRmsSec  .set_alignment ( Gtk::ALIGN_END   );
  lblAmpCar     .set_text  ("Am Jit (c):"    );   lblAmpCar  .set_width_chars ( 10 );   lblAmpCar  .set_alignment ( Gtk::ALIGN_END   );
  lblaPk        .set_text  ("Pk ch 0:"       );   lblaPk     .set_width_chars ( 10 );   lblaPk     .set_alignment ( Gtk::ALIGN_END   );
  lblaPh        .set_text  ("Φ ch 0:"        );   lblaPh     .set_width_chars ( 10 );   lblaPh     .set_alignment ( Gtk::ALIGN_END   );

  ebxPrr        .set_width_chars ( 13 );   ebxPrr        .set_editable ( false );
  ebxZerFrq0    .set_width_chars ( 13 );   ebxZerFrq0    .set_editable ( false );
  ebxZerFrq1    .set_width_chars ( 13 );   ebxZerFrq1    .set_editable ( false );
  ebxZerRmsUi0  .set_width_chars ( 13 );   ebxZerRmsUi0  .set_editable ( false );
  ebxZerRmsUi1  .set_width_chars ( 13 );   ebxZerRmsUi1  .set_editable ( false );
  ebxZerRmsSec0 .set_width_chars ( 13 );   ebxZerRmsSec0 .set_editable ( false );
  ebxZerRmsSec1 .set_width_chars ( 13 );   ebxZerRmsSec1 .set_editable ( false );
  ebxZerAmpCar0 .set_width_chars ( 13 );   ebxZerAmpCar0 .set_editable ( false );
  ebxZerAmpCar1 .set_width_chars ( 13 );   ebxZerAmpCar1 .set_editable ( false );
  ebxZeraPk0    .set_width_chars ( 13 );   ebxZeraPk0    .set_editable ( false );
  ebxZeraPk1    .set_width_chars ( 13 );   ebxZeraPk1    .set_editable ( false );
  ebxZeraPh0    .set_width_chars ( 13 );   ebxZeraPh0    .set_editable ( false );
  ebxZeraPh1    .set_width_chars ( 13 );   ebxZeraPh1    .set_editable ( false );



//==  Now put it all together
  this                   ->pack_start (  hbxSine          , Gtk::PACK_SHRINK, 3 );
  hbxSine                .pack_start (  vbxCtlOv          , Gtk::PACK_SHRINK, 3 );
    vbxCtlOv              .pack_start ( *btCalcEstZerXrs   , Gtk::PACK_SHRINK, 3 );
    vbxCtlOv              .pack_start ( *btCalcFilter      , Gtk::PACK_SHRINK, 3 );
    vbxCtlOv              .pack_start ( *btCalcDemod       , Gtk::PACK_SHRINK, 3 );
    vbxCtlOv              .pack_start ( *btCalcBaseFilt    , Gtk::PACK_SHRINK, 3 );
    vbxCtlOv              .pack_start ( *btCalcDemDecim    , Gtk::PACK_SHRINK, 3 );
    vbxCtlOv              .pack_start (  lblPrr            , Gtk::PACK_SHRINK, 3 );
    vbxCtlOv              .pack_start (  ebxPrr            , Gtk::PACK_SHRINK, 3 );
  hbxSine                .pack_start (  frmZer0           , Gtk::PACK_SHRINK, 3 );
    frmZer0               .add        (  vbxZer0                                 );
      vbxZer0             .pack_start (  hbxZerFrq0        , Gtk::PACK_SHRINK, 3 );
        hbxZerFrq0        .pack_start (  lblFrq            , Gtk::PACK_SHRINK, 3 );
        hbxZerFrq0        .pack_start (  ebxZerFrq0        , Gtk::PACK_SHRINK, 3 );
      vbxZer0             .pack_start (  hbxZerRmsUi0      , Gtk::PACK_SHRINK, 3 );
        hbxZerRmsUi0      .pack_start (  lblRmsUi          , Gtk::PACK_SHRINK, 3 );
        hbxZerRmsUi0      .pack_start (  ebxZerRmsUi0      , Gtk::PACK_SHRINK, 3 );
      vbxZer0             .pack_start (  hbxZerRmsSec0     , Gtk::PACK_SHRINK, 3 );
        hbxZerRmsSec0     .pack_start (  lblRmsSec         , Gtk::PACK_SHRINK, 3 );
        hbxZerRmsSec0     .pack_start (  ebxZerRmsSec0     , Gtk::PACK_SHRINK, 3 );
      vbxZer0             .pack_start (  hbxZerAmpCar0     , Gtk::PACK_SHRINK, 3 );
        hbxZerAmpCar0     .pack_start (  lblAmpCar         , Gtk::PACK_SHRINK, 3 );
        hbxZerAmpCar0     .pack_start (  ebxZerAmpCar0     , Gtk::PACK_SHRINK, 3 );
      vbxZer0             .pack_start (  hbxZeraPk0        , Gtk::PACK_SHRINK, 3 );
        hbxZeraPk0        .pack_start (  lblaPk            , Gtk::PACK_SHRINK, 3 );
        hbxZeraPk0        .pack_start (  ebxZeraPk0        , Gtk::PACK_SHRINK, 3 );
      vbxZer0             .pack_start (  hbxZeraPh0        , Gtk::PACK_SHRINK, 3 );
        hbxZeraPh0        .pack_start (  lblaPh            , Gtk::PACK_SHRINK, 3 );
        hbxZeraPh0        .pack_start (  ebxZeraPh0        , Gtk::PACK_SHRINK, 3 );
  hbxSine                .pack_start (  frmZer1           , Gtk::PACK_SHRINK, 3 );
    frmZer1               .add        (  vbxZer1                                 );
      vbxZer1             .pack_start (  hbxZerFrq1        , Gtk::PACK_SHRINK, 3 );
        hbxZerFrq1        .pack_start (  ebxZerFrq1        , Gtk::PACK_SHRINK, 3 );
      vbxZer1             .pack_start (  hbxZerRmsUi1      , Gtk::PACK_SHRINK, 3 );
        hbxZerRmsUi1      .pack_start (  ebxZerRmsUi1      , Gtk::PACK_SHRINK, 3 );
      vbxZer1             .pack_start (  hbxZerRmsSec1     , Gtk::PACK_SHRINK, 3 );
        hbxZerRmsSec1     .pack_start (  ebxZerRmsSec1     , Gtk::PACK_SHRINK, 3 );
      vbxZer1             .pack_start (  hbxZerAmpCar1     , Gtk::PACK_SHRINK, 3 );
        hbxZerAmpCar1     .pack_start (  ebxZerAmpCar1     , Gtk::PACK_SHRINK, 3 );
      vbxZer1             .pack_start (  hbxZeraPk1        , Gtk::PACK_SHRINK, 3 );
        hbxZeraPk1        .pack_start (  ebxZeraPk1        , Gtk::PACK_SHRINK, 3 );
      vbxZer1             .pack_start (  hbxZeraPh1        , Gtk::PACK_SHRINK, 3 );
        hbxZeraPh1        .pack_start (  ebxZeraPh1        , Gtk::PACK_SHRINK, 3 );
  hbxSine                .pack_start (  frmAnType         , Gtk::PACK_SHRINK, 3 );
    frmAnType             .add        (  vbxAnSetup                              );
      vbxAnSetup          .pack_start (  vbxAnType         , Gtk::PACK_SHRINK, 3 );
        vbxAnType         .pack_start ( *rbtAnTypeIndep    , Gtk::PACK_SHRINK, 3 );
        vbxAnType         .pack_start ( *rbtAnTypeIQ       , Gtk::PACK_SHRINK, 3 );
        vbxAnType         .pack_start ( *rbtAnTypeCarr     , Gtk::PACK_SHRINK, 3 );
        vbxAnType         .pack_start (  hbxAnTypePad      , Gtk::PACK_SHRINK, 3 );
        hbxAnTypePad      .pack_start (  frmAnCarr         , Gtk::PACK_SHRINK, 3 );
        frmAnCarr         .add        (  hbxAnCarrPad                            );
          hbxAnCarrPad    .pack_start (  vbxAnCarr         , Gtk::PACK_SHRINK, 3 );
          vbxAnCarr       .pack_start (  hbxChChoose       , Gtk::PACK_SHRINK, 3 );
            hbxChChoose   .pack_start ( *rbtCh0            , Gtk::PACK_SHRINK, 3 );
            hbxChChoose   .pack_start ( *rbtCh1            , Gtk::PACK_SHRINK, 3 );
          vbxAnCarr       .pack_start (  lblCarrFreq       , Gtk::PACK_SHRINK, 3 );
          vbxAnCarr       .pack_start (  ebxCarrFreq       , Gtk::PACK_SHRINK, 3 );
          vbxAnCarr       .pack_start (  lblCarrAnBW       , Gtk::PACK_SHRINK, 3 );
          vbxAnCarr       .pack_start (  ebxCarrAnBW       , Gtk::PACK_SHRINK, 3 );


  return;
}
void    PageAnSine::Connect            ( void         ) {
  btCalcEstZerXrs -> signal_clicked().connect(sigc::mem_fun(*this, &PageAnSine   ::OnEstZerXrs    ));
  btCalcFilter    -> signal_clicked().connect(sigc::mem_fun(*this, &PageAnSine   ::OnFilter       ));
  btCalcDemod     -> signal_clicked().connect(sigc::mem_fun(*this, &PageAnSine   ::OnDemod        ));
  btCalcBaseFilt  -> signal_clicked().connect(sigc::mem_fun(*this, &PageAnSine   ::OnBaseFilt     ));
  btCalcDemDecim  -> signal_clicked().connect(sigc::mem_fun(*this, &PageAnSine   ::OnDemDecim     ));

  rbtAnTypeIndep  -> signal_clicked().connect(sigc::mem_fun(*this, &PageAnSine   ::OnIndIQ        ));
  rbtAnTypeIQ     -> signal_clicked().connect(sigc::mem_fun(*this, &PageAnSine   ::OnIndIQ        ));

  rbtCh0          -> signal_clicked().connect(sigc::mem_fun(*this, &PageAnSine   ::OnCarrChChoose ));
  rbtCh1          -> signal_clicked().connect(sigc::mem_fun(*this, &PageAnSine   ::OnCarrChChoose ));

  HnCbSineVoid         ->SetCallback(this, &PageAnSine::HndlSineVoid);
  ctMd->HCB_AnSineVoid = HnCbSineVoid;

  return;
}
