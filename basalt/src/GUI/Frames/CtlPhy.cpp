// $Id: CtlPhy.cpp 693 2022-12-28 03:44:39Z duncang $

//=================================================================================================
// Original File Name : CtlPhy.cpp
// Original Author    : duncang
// Creation Date      : Dec 25, 2011
// Copyright          : Copyright © 2011 - 2022 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include "CtlPhy.hpp"

        CtlPhy::CtlPhy           (const char *i_label, Alsa *i_theAlsa, AlsaStreamOut *i_mcAlsaStream, CtlArb *i_vcGenerator)
: Gtk::Frame(i_label)
, theAlsa(i_theAlsa)
, theStream(i_mcAlsaStream)
, vcGenerator(i_vcGenerator) {
  holdoff = true;
  Build();

  //=================================================================================================
  AlsaCardFill(); // TODO When we add ALSA change detection, this has to be pushed to a ReScan method.
  AlsaIfcFill();
  AlsaDevTxFill();
  holdoff = false;
  Connect();
  return;
}
        CtlPhy::~CtlPhy          (void) {
  return;
}

void    CtlPhy::Build            (void) {
  //=================================================================================================
  // Card
  lbl_FacCard = new Gtk::Label((const char *)("Card:"));
  lbl_FacCard->set_size_request(80,30);
  hbx_FacCard.pack_start(*lbl_FacCard, Gtk::PACK_SHRINK, 2);
  cbxt_FacCard = new Gtk::ComboBoxText();
  //cbxt_FacCard->set_size_request(250,30);
  cbxt_FacCard->set_tooltip_text("Choose the sound card you wish to use");
  hbx_FacCard.pack_start(*cbxt_FacCard, Gtk::PACK_EXPAND_WIDGET, 2);

  //=================================================================================================
  // Ifc
  lbl_FacIfc = new Gtk::Label((const char *)("Interface:"));
  lbl_FacIfc->set_size_request(80,30);
  hbx_FacIfc.pack_start(*lbl_FacIfc, Gtk::PACK_SHRINK, 2);
  cbxt_FacIfc = new Gtk::ComboBoxText();
  //cbxt_FacIfc->set_size_request(250,30);
  cbxt_FacIfc->set_tooltip_text("Choose the sound card you wish to use");
  hbx_FacIfc.pack_start(*cbxt_FacIfc, Gtk::PACK_EXPAND_WIDGET, 2);

 //=================================================================================================
  // TX Device
  lbl_FacDevTx = new Gtk::Label("TX Device:");
  lbl_FacDevTx->set_size_request(80,30);
  cbxt_FacDevTx = new Gtk::ComboBoxText();
  //cbxt_FacDevTx->set_size_request(250,30);
  cbxt_FacDevTx->set_tooltip_text("The output port on the card, the cleanest is hw");
  hbx_FacDevTx.pack_start(*lbl_FacDevTx, Gtk::PACK_SHRINK, 2);
  hbx_FacDevTx.pack_start(*cbxt_FacDevTx, Gtk::PACK_EXPAND_WIDGET, 2);

  //=================================================================================================
  // pcm Interface
  lbl_PcmSpec = new Gtk::Label("PCM Name:");
  lbl_PcmSpec->set_size_request(80,30);
  txt_PcmSpec = new Gtk::Entry();
  //txt_PcmSpec->set_size_request(240, 30);
  txt_PcmSpec->set_editable(false);
  txt_PcmSpec->set_can_focus(false);
  hbx_PcmSpec.pack_start(*lbl_PcmSpec, Gtk::PACK_SHRINK, 2);
  hbx_PcmSpec.pack_start(*txt_PcmSpec, Gtk::PACK_SHRINK, 2);

  //=================================================================================================
  // Capabilities First Row
  lbl_CapFmt = new Gtk::Label((const char *)("fmt:"));
  cbxt_CapFmt = new Gtk::ComboBoxText();
  cbxt_CapFmt->set_size_request(90, 30);
  cbxt_CapFmt->append("S16_LE");  // FIXME This populates AFTER choosing pcm Interface
  cbxt_CapFmt->append("S24_3LE");
  cbxt_CapFmt->append("S32_LE");
  cbxt_CapFmt->set_active_text("S32_LE");

  lbl_CapChan = new Gtk::Label((const char *)("ch:"));
  cbxt_CapChan = new Gtk::ComboBoxText();
  cbxt_CapChan->set_size_request(50, 30);
  cbxt_CapChan->append("2");  // FIXME This populates AFTER choosing pcm Interface
  cbxt_CapChan->set_active_text("2");

  hbx_Caps1.pack_start(*lbl_CapFmt,  Gtk::PACK_SHRINK, 2);
  hbx_Caps1.pack_start(*cbxt_CapFmt, Gtk::PACK_SHRINK, 2);
  hbx_Caps1.pack_start(*lbl_CapChan,  Gtk::PACK_SHRINK, 2);
  hbx_Caps1.pack_start(*cbxt_CapChan, Gtk::PACK_SHRINK, 2);

  //=================================================================================================
  // Capabilities Second Row
  lbl_CapFS = new Gtk::Label((const char *)("FS:"));
  cbxt_CapFS = new Gtk::ComboBoxText();
  cbxt_CapFS->set_size_request(90, 30);
  cbxt_CapFS->append("44100");  // FIXME This populates AFTER choosing pcm Interface
  cbxt_CapFS->append("48000");
  cbxt_CapFS->append("88200");
  cbxt_CapFS->append("96000");
  cbxt_CapFS->set_active_text("48000");

  hbx_Caps2.pack_start(*lbl_CapFS,  Gtk::PACK_SHRINK, 2);
  hbx_Caps2.pack_start(*cbxt_CapFS, Gtk::PACK_SHRINK, 2);

  //=================================================================================================
  // TX Buttons
  tbtn_TxCloseOpen = new Gtk::ToggleButton("Closed");
  tbtn_TxCloseOpen->set_size_request(80, 28);
  hbx_Control.pack_end(*tbtn_TxCloseOpen, Gtk::PACK_SHRINK, 2);
  hbx_Dummy.set_size_request(20,80);


//=================================================================================================
  vbx_AudioPort.pack_start(vbx_Facility, Gtk::PACK_SHRINK,        2);
  vbx_Facility .pack_start(hbx_FacCard,  Gtk::PACK_SHRINK,        2);
  vbx_Facility .pack_start(hbx_FacIfc,   Gtk::PACK_SHRINK,        2);
  vbx_Facility .pack_start(hbx_FacDevTx, Gtk::PACK_SHRINK,        2);
  vbx_Facility .pack_start(hbx_PcmSpec,  Gtk::PACK_SHRINK,        2);
  vbx_Facility .pack_start(hbx_Caps1,    Gtk::PACK_SHRINK,        2);
  vbx_Facility .pack_start(hbx_Caps2,    Gtk::PACK_SHRINK,        2);
  vbx_Facility .pack_start(hbx_Dummy,    Gtk::PACK_EXPAND_WIDGET, 2);
  vbx_Facility .pack_end  (hbx_Control,  Gtk::PACK_SHRINK,        2);

  add(vbx_AudioPort);
  return;
}

void    CtlPhy::Connect          (void) {
  conn_FacCardFill  = cbxt_FacCard     ->signal_changed().connect(sigc::mem_fun(*this, &CtlPhy::OnAlsaCardChange  ));
  conn_FacIfcFill   = cbxt_FacIfc      ->signal_changed().connect(sigc::mem_fun(*this, &CtlPhy::OnAlsaIfcChange   ));
  conn_FacDevTxFill = cbxt_FacDevTx    ->signal_changed().connect(sigc::mem_fun(*this, &CtlPhy::OnDevTxChanged    ));
  conn_CapFmt       = cbxt_CapFmt      ->signal_changed().connect(sigc::mem_fun(*this, &CtlPhy::OnFacFmtChanged   ));
  conn_CapFS        = cbxt_CapFS       ->signal_changed().connect(sigc::mem_fun(*this, &CtlPhy::OnFacFSChanged    ));
  conn_TxCloseOpen  = tbtn_TxCloseOpen ->signal_clicked().connect(sigc::mem_fun(*this, &CtlPhy::OnTxCloseOpen     ));
  return;
}


void    CtlPhy::AlsaCardFill     (void) {
  char   tStr[128];
  ullong numCards;

  cbxt_FacCard->remove_all();
  numCards = theAlsa->GetNoCards();
  for(uint cardDex=0; cardDex<numCards; cardDex++) {
    theAlsa->SetCard(cardDex);
    strcpy(tStr, theAlsa->GetCardNm());
    cbxt_FacCard->append(tStr);
    }
  if(!holdoff) conn_FacCardFill.disconnect(); // from under code, you don't know if it will trigger the event.
  cbxt_FacCard->set_active(0);
  OnAlsaCardChange();            // So, do it manually
  if(!holdoff) conn_FacCardFill = cbxt_FacIfc->signal_changed().connect(sigc::mem_fun(*this, &CtlPhy::OnAlsaCardChange));
  return;
}
void    CtlPhy::OnAlsaCardChange (void) {
  int    cardNo; // Because the combo box uses negatives to mean things.

  cardNo = cbxt_FacCard->get_active_row_number(); // MAGICK Yes, one again, the index on the combobox indexes into an array.
  if(cardNo >= 0) {
    theAlsa->SetCard(cardNo);
    AlsaIfcFill();
  }
  return;
}

void    CtlPhy::AlsaIfcFill      (void) {
  char   *tStr;
  ullong  numIfcs;
  ullong  ifcNo;

  //  The parent changed, time to fill the combo box, then cascade down to Device
  //  Since we'll set the Ifc number index on the combo list, that will cascade down into the Device filler
  cbxt_FacIfc->remove_all();
  numIfcs = theAlsa->GetNumIfcs(); // IMPORTANT, assumes theCard has been set above.
  ifcNo = theAlsa->GetIfcNo(); // Save it before the thrashing below
  for(uint ifcDex=0; ifcDex<numIfcs; ifcDex++) {
    theAlsa->SetIfc(ifcDex);
    tStr = theAlsa->GetIfcName();
    cbxt_FacIfc->append(tStr);
  }
  theAlsa->SetIfc(ifcNo); // And restore.
  if(!holdoff) conn_FacIfcFill.disconnect();
  cbxt_FacIfc->set_active(theAlsa->GetIfcNo());
  cbxt_FacIfc->set_active(ifcNo);
  OnAlsaIfcChange();
  if(!holdoff) conn_FacIfcFill = cbxt_FacIfc->signal_changed().connect(sigc::mem_fun(*this, &CtlPhy::OnAlsaIfcChange));
  return;
  }
void    CtlPhy::OnAlsaIfcChange  (void) {
  int    ifcNo;

  ifcNo = cbxt_FacIfc->get_active_row_number();
  theAlsa->SetIfc(ifcNo);
  // No need to protect against lack of interfaces, they are always enumerated even if they have no devices/
  if(ifcNo >= 0)
    AlsaDevTxFill();
  return;
}

void    CtlPhy::AlsaDevTxFill    (void) {
  char   *tStr = new char[MAX_LINE_LEN];
  char    nStr[16];
  ullong  devNo;
  ullong  numDevs;

  if(!holdoff) conn_FacDevTxFill.disconnect();
  cbxt_FacDevTx->remove_all();
  if(!theAlsa->IsIfcPresent()) {
    cbxt_FacDevTx->append("<empty>");
    theAlsa->SetIfc(0);
    cbxt_FacDevTx->set_active(0);
  }
  else {
    numDevs = theAlsa->GetNumDevs();
    devNo   = theAlsa->GetDevNo(); // Squirrel away before the following cycling through.
    for(ullong devDex=0; devDex<numDevs; devDex++) {
      theAlsa->SetDev(devDex);
      strcpy(tStr, (const char *)theAlsa->GetAADevNm());
      strcat(tStr, " - ");
      if(theAlsa->HasAADevNo()) {
        sprintf(nStr, " %Lu ", theAlsa->GetAADevNo());
        strcat(tStr, nStr);
      }
      else                      strcat(tStr, "[]");
      strcat(tStr, " - ");
      if(theAlsa->DevCanTX())   strcat(tStr, "<   TX>");
      else                      strcat(tStr, "<no TX>");
      if(theAlsa->DevCanRX())   strcat(tStr, "<   RX>");
      else                      strcat(tStr, "<no RX>");
      if(theAlsa->DevIsBusy())  strcat(tStr, "<busy!>");
      if(theAlsa->DevHasErr())  strcat(tStr, "<error!>");
      cbxt_FacDevTx->append(tStr);
    }
  }
  theAlsa->SetDev(devNo); // And restore
  cbxt_FacDevTx->set_active(devNo);
  OnDevTxChanged();
  if(!holdoff) conn_FacDevTxFill = cbxt_FacDevTx->signal_changed().connect(sigc::mem_fun(*this, &CtlPhy::OnDevTxChanged));
  delete tStr;
  return;
  }
void    CtlPhy::OnDevTxChanged   (void) {
  char  *pStr;
  int    devNo;

  if(theAlsa->IsIfcPresent()) {
    devNo = cbxt_FacDevTx->get_active_row_number();
    if(devNo >= 0) { // gotta love those magic numbers!
      theAlsa->SetDev(devNo);
      pStr = theAlsa->GetPcmSpec();
      txt_PcmSpec->set_text(pStr);
      AlsaFSFill();
    }
  }
  return;
}

void    CtlPhy::AlsaFSFill       (void) {
  char    tFSstr[64];
  ullong *tFSs;
  ullong  tNFSs;

  //return;
  if(!theAlsa->IsIfcPresent()) {
    cbxt_CapFS->append("<none>");
  }
  else {
    tFSs = NULL;
    tNFSs = theAlsa->GetFSs(&tFSs);
    cbxt_CapFS->clear();
    for(ullong FSdex=0; FSdex<tNFSs; FSdex++) {
      sprintf(tFSstr, "%Lu", tFSs[FSdex]);
      //strcpy(tFSstr, "012345");
      cbxt_CapFS->append(tFSstr);
    }
    if(tNFSs == 0)
      cbxt_CapFS->append("0");
    if(!holdoff) conn_CapFS.disconnect();
    cbxt_CapFS->set_active(0);
    if(!holdoff) conn_CapFS       = cbxt_CapFS      ->signal_changed().connect(sigc::mem_fun(*this, &CtlPhy::OnFacFSChanged   ));
  }
  return;
}
void    CtlPhy::OnFacFSChanged   (void) {
  int fsDex;
  fsDex = cbxt_CapFS->get_active_row_number();
  (void)fsDex;
  return;
}

void    CtlPhy::OnFacFmtChanged  (void) {
  if(strcmp(cbxt_CapFmt->get_active_text().c_str(), "S16_LE") == 0) {
    theStream->af->SetFmt(AlsaFormat::ADI_16);
  }
  else if(strcmp(cbxt_CapFmt->get_active_text().c_str(), "S24_3LE") == 0) {
    theStream->af->SetFmt(AlsaFormat::ADI_24);
  }
  else {
    theStream->af->SetFmt(AlsaFormat::ADI_32);
  }
  theStream->PushFormat();
  fprintf(stdout, "WinMain::OnFacFmtChanged found: %s\n", cbxt_CapFmt->get_active_text().c_str());
  return;
}


void    CtlPhy::OnTxCloseOpen    (void) {
  if(tbtn_TxCloseOpen->get_active()) {
    tbtn_TxCloseOpen->set_label("Opened");
    theStream->Open();
    if(theStream->err >= 0)
      theStream->Setup();;
    if(theStream->err >= 0)
      theStream->SetBufferFrames(1024);
    if(theStream->err >= 0)
      vcGenerator->theWave->Setup();
    if(theStream->err >= 0)
      theStream->Start();
    if(theStream->err < 0) {
      //theStream->Stop();
      //theStream->Close();
      conn_TxCloseOpen.disconnect();
      tbtn_TxCloseOpen->set_active(false);
      tbtn_TxCloseOpen->set_label("Closed");
      conn_TxCloseOpen = tbtn_TxCloseOpen->signal_clicked().connect(sigc::mem_fun(*this, &CtlPhy::OnTxCloseOpen));
      //stb_Main->pop();
      //stb_Main->push("Output is In Use, Please choose another port.", 0);
      }
    else {
      //stb_Main->pop();
      //stb_Main->push("PCM Output is Open", 0);
      }
    }
  else {
    tbtn_TxCloseOpen->set_label("Closed");
    theStream->Stop();
    theStream->Close();
    //stb_Main->pop();
    //stb_Main->push("PCM Output is Closed", 0);
    }
  return;
  }












void    CtlPhy::AlsaFmtFill      (void) {
  return;
}
