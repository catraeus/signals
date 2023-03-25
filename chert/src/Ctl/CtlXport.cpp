// $Id: CtlXport.cpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : CtlXport.cpp
// Original Author    : duncang
// Creation Date      : 2016-12-26T23:14:46,862519570+00:00
// Copyright          : Copyright © 2016 - 2017 by Catraeus and Duncan Gray
//
//
//=================================================================================================

#include <gtkmm.h>
#include <stdio.h>

#include <caes/CaesString.hpp>

#include "CtlXport.hpp"

CtlXport *CtlXport::ctXp = NULL;  // Singleton Pattern

          CtlXport::CtlXport    ( Signal *i_sig )
: sig (i_sig) {
  BuildEnv   ();
  BuildSetup ();
  Connect    ();
}
          CtlXport::~CtlXport   ( void ) {
}
CtlXport *CtlXport::GetInstance ( Signal *i_sig ) {  // Singleton Pattern
  if(ctXp == NULL)
    ctXp = new CtlXport(i_sig);
  return ctXp;
}
void      CtlXport::BuildEnv    ( void ) {
  ctMd           = CtlMsgDspch ::GetInstance(     );
  ctRsmp         = CtlRsmp     ::GetInstance( sig );
  ctOsHor        = CtlOsHor    ::GetInstance( sig ); // i_ctOsHor is not singleton, because creation order might matter.
  mdOs           = MdlOs       ::GetInstance( sig );
  return;
}
void      CtlXport::BuildSetup  ( void ) {
  running        = false;
  lastRunning    = false;
  buttonKill     = false;
  hitByButton    = true;
  buttonMask     = XA_NONE;
  return;
}
void      CtlXport::Connect     ( void ) {

                        MRU_XpStop = new CbT<CtlXport>();
                        MRU_XpStop->SetCallback(this, &CtlXport::OnStop);
  ctMd->MSU_XpStop    = MRU_XpStop;

                        MRU_RshTime = new CbT<CtlXport>();
                        MRU_RshTime->SetCallback(this, &CtlXport::OnStop);
  ctMd->MSU_XpRshTime = MRU_RshTime;
  return;
}
bool      CtlXport::OnRshTime   ( void *i_d ) {
  double tRshTim;

  tRshTim = mdOs->GetTimVrsh();
  if(running) {
    tt_DrawItNow.disconnect();
    tt_DrawItNow = Glib::signal_timeout().connect(sigc::mem_fun(*this, &CtlXport::OnXpDataHit), (uint)(tRshTim*1000.0), Glib::PRIORITY_DEFAULT);
  }
  return true;
}


bool      CtlXport::OnFirst    ( void  *i_dummy) {
  if(buttonKill) return false;
  buttonKill = true;
//  fprintf(stderr, "BtFirst"); fflush(stderr);
//  if(buttonKill) {
//    fprintf(stderr, ".\n"); fflush(stderr);
//    return false;
//  }
//  buttonKill = true;
//  fprintf(stderr, "+\n"); fflush(stderr);
  tt_DrawItNow.disconnect();
  running = false;
  mdOs->GoFirst();
  mdOs->SetDirFwd();
  hitByButton = true;
  ButExtro();
  hitByButton = false;
  return false;
}
bool      CtlXport::OnPrev     ( void  *i_dummy ) {
  if(buttonKill) return false;
  buttonKill = true;
  tt_DrawItNow.disconnect();
  running = false;
  mdOs->SetDirRev();
  mdOs->Advance();
  hitByButton = true;
  ButExtro();
  hitByButton = false;
  return false;
}
bool      CtlXport::OnStop     ( void  *i_dummy ) {
  if(buttonKill) return false;
  buttonKill = true;
  running = false;
  hitByButton = true;
  ButExtro();
  hitByButton = false;
  return false;
}
bool      CtlXport::OnStart    ( void  *i_dummy ) {
  if(buttonKill) return false;
  buttonKill = true;
  running = true;
  hitByButton = true;
  ButExtro();
  hitByButton = false;
  return false;
}
bool      CtlXport::OnNext     ( void  *i_dummy ) {
  if(buttonKill) return false;
  buttonKill = true;
  tt_DrawItNow.disconnect();
  running = false;
  mdOs->SetDirFwd();
  mdOs->Advance();
  hitByButton = true;
  ButExtro();
  hitByButton = false;
  return false;
}
bool      CtlXport::OnLast     ( void  *i_dummy ) {
  if(buttonKill) return false;
  buttonKill = true;
  tt_DrawItNow.disconnect();
  running = false;
  mdOs->GoLast();
  mdOs->SetDirRev();
  hitByButton = true;
  ButExtro();
  hitByButton = false;
  return false;
}
bool      CtlXport::OnWhole    ( void  *i_dummy ) {
  if(buttonKill) return false;
  buttonKill = true;
  tt_DrawItNow.disconnect();
  running = false;
  mdOs->SetDirWhole();
  hitByButton = true;
  ButExtro();
  hitByButton = false;
  return false;
}
void      CtlXport::ButExtro   ( void           ) {
  double tRshTim;
  uint   butMask;

  tRshTim = mdOs->GetTimVrsh();

  //Handle run/stop
       if(  running && !lastRunning )
                                      tt_DrawItNow = Glib::signal_timeout().connect(sigc::mem_fun(*this, &CtlXport::OnXpDataHit), (uint)(tRshTim*1000.0), Glib::PRIORITY_DEFAULT);
  else if( !running )
                                      tt_DrawItNow.disconnect();
  if(mdOs->GetPegged()) {
    tt_DrawItNow.disconnect();
    running      = false;
    lastRunning  = running;
    butMask      = 0;
    butMask     += eAct::XA_STOP;
    ctMd->MRD_XpButSet(&butMask);
  }
  OnXpDataHit();

  lastRunning = running;
  butMask = 0;
  if(running)
    butMask += eAct::XA_START;
  else
    butMask += eAct::XA_STOP;


  if(mdOs->DirIsFwd()) {
    butMask += eAct::XA_NEXT;
    if(mdOs->GetPegged()) {
      butMask += eAct::XA_FIRST;
    }
  }
  else if(mdOs->DirIsRev()) {
    butMask += eAct::XA_PREV;
    if(mdOs->GetPegged())
      butMask += eAct::XA_LAST;
  }
  else if(mdOs->DirIsWhole())
    butMask += eAct::XA_WHOLE;
  ctMd->MRD_XpButSet(&butMask);
  ctMd->MRD_OsHorNumerics();
  buttonKill = false;
  return;
}


bool      CtlXport::OnChangeN   ( GdkEventButton *i_event) {
  if(i_event->button != 1)    return false;
  if(running)                 return false;
  Gtk::MessageDialog *numDlg;
  Gtk::Entry          txtNum;
  Gtk::Box           *hbxDlg;
  char    stringN[] = "Please enter the Frame No\n";
  char    newV[265];
  char   *tStr;
  bool    keepGoing;
  llong  numN;
  int     result;

  tStr    =   0   ;
  newV[0] = '\0'  ;
  numN    =   0   ;
  // ================== Set up the dialog, conditionally based on which label was clicked
  tStr = stringN;
  sprintf(newV, "%llu", numN);


  txtNum.set_text(newV);
  txtNum.set_activates_default(true);

  numDlg = new Gtk::MessageDialog ((const char*)tStr, false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL);
  numDlg->set_transient_for(*parentWin);
  numDlg->set_default_response(Gtk::RESPONSE_OK);
  numDlg->set_secondary_text("");
  txtNum.set_width_chars(25);
  hbxDlg = numDlg->get_content_area(); // Get the box that we will manually add the Gtk::Entry into.
  hbxDlg->pack_start(txtNum);
  txtNum.show();                       // WTF MAN!  We have to show this?!?!
  keepGoing = true;
  while(keepGoing) {
    result = numDlg->run();            // Here is where we block and pop up the dialog
    if(result == Gtk::RESPONSE_OK) {
      int numcon;
      strcpy(newV, txtNum.get_text().c_str());

      numcon = sscanf(newV, "%lld", &numN);
      if(numcon == 1) {
        if(numN > sig->GetN())
          numDlg->set_secondary_text("Attempt to set past end, please try again.");
        else {
          keepGoing = false;
          mdOs->SetPosN(numN);
          OnXpDataHit();
          }
        }
      else
        numDlg->set_secondary_text("Invalid entry, please try again.");

      }
    else
      keepGoing = false;
    numDlg->hide();
    }
  delete numDlg;

  return false;
  }
bool      CtlXport::OnChangeT   ( GdkEventButton *i_event) {
  if(i_event->button != 1)    return false;
  if(running)                 return false;
  Gtk::MessageDialog *numDlg;
  Gtk::Entry          txtNum;
  Gtk::Box           *hbxDlg;
  char                stringT[] = "Please enter Time\n";
  char                newV[265];
  char               *tStr;
  bool                keepGoing;
  double              numT;
  llong              numN;
  int                 result;

  tStr    =   0   ;
  newV[0] = '\0'  ;
  numN    =   0   ;
  numT    =   0.0 ;
  // ================== Set up the dialog, conditionally based on which label was clicked
  tStr = stringT;
  sprintf(newV, "%f", numT);



  txtNum.set_text(newV);
  txtNum.set_activates_default(true);

  numDlg = new Gtk::MessageDialog ((const char*)tStr, false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL);
  numDlg->set_transient_for(*parentWin);
  numDlg->set_default_response(Gtk::RESPONSE_OK);
  numDlg->set_secondary_text("");
  txtNum.set_width_chars(25);
  hbxDlg = numDlg->get_content_area(); // Get the box that we will manually add the Gtk::Entry into.
  hbxDlg->pack_start(txtNum);
  txtNum.show();                       // WTF MAN!  We have to show this?!?!
  keepGoing = true;
  while(keepGoing) {
    result = numDlg->run();            // Here is where we block and pop up the dialog
    if(result == Gtk::RESPONSE_OK) {
      int numcon;
      strcpy(newV, txtNum.get_text().c_str());

      numcon = HMStoSec(&numT, newV);
      numN = (llong)(numT * sig->GetFS());
      if(numcon == 1) {
        if(numN > sig->GetN()) {
          //fprintf(stdout, "BAD     frames    %16s    %9d  %6.6f  numcon: %d\n", newV, numN, numT, numcon); fflush(stdout);
          numDlg->set_secondary_text("Attempt to set past end, please try again.");
          }
        else {
          keepGoing = false;
          mdOs->SetPosT(numT);
          OnXpDataHit();
          }
        }
      else {
        numDlg->set_secondary_text("Invalid entry, please try again.");
        }

      }
    else
      keepGoing = false;
    numDlg->hide();
    }
  delete numDlg;

  return false;
  }
void      CtlXport::OnTimeSlide ( double i_scalePos) {
  double numT;
  //running = false;

  numT = i_scalePos;
  numT = numT * mdOs->GetDurT();
  mdOs->SetPosT(numT);
  OnXpDataHit();
  return;
  }


bool      CtlXport::OnXpDataHit(void) {
  if(!hitByButton) {
    mdOs->Advance();
  }
  ctRsmp->GrabHere();
  ctRsmp->RsmpOsAcq(NULL);
  ctRsmp->RsmpSaAcq(NULL);
  ctMd->MRD_XpTimN();
  ctMd->MRD_TraceDataHit();
  return true;
  }
