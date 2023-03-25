
// $Id: PageFileWr.cpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : PageFileWr.cpp
// Original Author    : duncang
// Creation Date      : Oct 17, 2012
// Copyright          : Copyright © 2011 - 2017 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include <string.h>

#include <caes/CaesString.hpp>
#include <caes/AudioFile/NumSys.hpp>

#include <caes/CaesMath.hpp>

#include "WinMain.hpp"
#include "PageFileWr.hpp"

         PageFileWr::PageFileWr          ( Gtk::Window *i_parent, Signal *i_sig, WaveFiler *i_two   )
: sig    ( i_sig    )
, two    ( i_two    )
, parent ( i_parent ) {
  BuildEnv();
  BuildMain();
  Connect();
  SetupWave();
  OnFileRshAll(NULL);
  OnWaveRshAll(NULL);
}
         PageFileWr::~PageFileWr         ( void                  ) {
}
void     PageFileWr::BuildEnv            ( void                  ) {
  ce        = CfgEnv      ::GetInstance();
  tns       = two->GetNumSys();
  trf       = two->GetRiffMgr();
  taf       = two->GetAudioFiler();
  ctMd      = CtlMsgDspch ::GetInstance();
  ctWave    = CtlWave     ::GetInstance(sig);
  return;
}
void     PageFileWr::BuildMain           ( void                  ) {
  set_orientation(Gtk::ORIENTATION_VERTICAL);
  BuildFile();

  tbtnFileOpen = new Gtk::ToolButton(Gtk::Stock::OPEN);


  this               ->pack_start  (  frmCtlFileName,        Gtk::PACK_SHRINK, 3 );
    frmCtlFileName    .add         (  hbxCtlFileName                             );
      hbxCtlFileName  .pack_start  (  lblCtlFileName,        Gtk::PACK_SHRINK, 3 );
      hbxCtlFileName  .pack_start  (  ebxCtlFileName,        Gtk::PACK_SHRINK    );
      hbxCtlFileName  .pack_start  ( *tbtnFileOpen,          Gtk::PACK_SHRINK    );

  this               ->pack_start  (  frmCtlWaveSpec,        Gtk::PACK_SHRINK, 3 );
    frmCtlWaveSpec    .add         (  hbxCtlWaveSpec                             );
      hbxCtlWaveSpec  .pack_start  (  lblSetCh,              Gtk::PACK_SHRINK, 3 );
      hbxCtlWaveSpec  .pack_start  (  ebxSetCh,              Gtk::PACK_SHRINK    );
      hbxCtlWaveSpec  .pack_start  (  lblSetFS,              Gtk::PACK_SHRINK, 3 );
      hbxCtlWaveSpec  .pack_start  (  ebxSetFS,              Gtk::PACK_SHRINK    );
      hbxCtlWaveSpec  .pack_start  (  lblSetFmt,             Gtk::PACK_SHRINK, 3 );
      hbxCtlWaveSpec  .pack_start  ( *cbxSetFmt,             Gtk::PACK_SHRINK    );
  this               ->pack_start  (  frmCtlStream,          Gtk::PACK_SHRINK, 3 );
    frmCtlStream      .add         (  hbxCtlStream                               );
      hbxCtlStream    .pack_start  (  lblWaveNumByte,        Gtk::PACK_SHRINK, 3 );
      hbxCtlStream    .pack_start  (  ebxFileSize,           Gtk::PACK_SHRINK, 3 );
      hbxCtlStream    .pack_start  (  lblWaveNumFrms,        Gtk::PACK_SHRINK, 3 );
      hbxCtlStream    .pack_start  (  ebxWaveNumFrms,        Gtk::PACK_SHRINK, 3 );
      hbxCtlStream    .pack_start  (  lblWaveTimeDur,        Gtk::PACK_SHRINK, 3 );
      hbxCtlStream    .pack_start  (  ebxWaveTimeDur,        Gtk::PACK_SHRINK, 3 );

  return;
}
void     PageFileWr::BuildFile           ( void                  ) {
  llong gg = tns->GetType();
  char *tStr;


  hbxCtlWaveSpec .set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  hbxCtlStream   .set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  hbxCtlFileName .set_orientation(Gtk::ORIENTATION_HORIZONTAL);

  tStr = ce->GetFileNameAbs();  // only at startup
  lblCtlFileName .set_text("File Name:"  );  lblCtlFileName .set_alignment(Gtk::ALIGN_END  );
  ebxCtlFileName .set_text(tStr          );  ebxCtlFileName .set_alignment(Gtk::ALIGN_START);  ebxCtlFileName .set_width_chars(80);
  lblSetCh       .set_text("ch:"         );  lblSetCh       .set_alignment(Gtk::ALIGN_END  );
  ebxSetCh       .set_text(    "1"       );  ebxSetCh       .set_alignment(Gtk::ALIGN_END  );  ebxSetCh       .set_width_chars( 3);  ebxSetCh       .set_editable(true );
  lblSetFS       .set_text("FS:"         );  lblSetFS       .set_alignment(Gtk::ALIGN_END  );
  ebxSetFS       .set_text("48000"       );  ebxSetFS       .set_alignment(Gtk::ALIGN_END  );  ebxSetFS       .set_width_chars(12);  ebxSetFS       .set_editable(true );
  lblWaveNumByte .set_text("File Size:"  );  lblWaveNumByte .set_alignment(Gtk::ALIGN_END  );
                                             ebxFileSize    .set_alignment(Gtk::ALIGN_END  );  ebxFileSize    .set_width_chars(13);  ebxFileSize    .set_editable(false);
  lblWaveNumFrms .set_text("Frames:"     );  lblWaveNumFrms .set_alignment(Gtk::ALIGN_END  );
                                             ebxWaveNumFrms .set_alignment(Gtk::ALIGN_END  );  ebxWaveNumFrms .set_width_chars(13);  ebxWaveNumFrms .set_editable(true );
  lblWaveTimeDur .set_text("Duration:"   );  lblWaveTimeDur .set_alignment(Gtk::ALIGN_END  );
                                             ebxWaveTimeDur .set_alignment(Gtk::ALIGN_END  );  ebxWaveTimeDur .set_width_chars(20);  ebxWaveTimeDur .set_editable(true );
  lblSetFmt      .set_text("Format:"     );
  cbxSetFmt = new Gtk::ComboBoxText();
  for(llong i=0; i<NumSys::numNames; i++) { tStr = NumSys::typeNames[i]; cbxSetFmt->append(tStr);  }
  cbxSetFmt->set_active(3);
  cbxSetFmt->set_active_text(NumSys::typeNames[gg]);
  return;
}
void     PageFileWr::Connect             ( void                  ) {
  holdOffAction = true;

            ebxCtlFileName   .signal_focus_out_event     ().connect(sigc::mem_fun(*this, &PageFileWr::OnChangeFileName   ));
            ebxCtlFileName   .signal_key_release_event   ().connect(sigc::mem_fun(*this, &PageFileWr::OnKeyFileName      ));
            ebxCtlFileName   .signal_button_press_event  ().connect(sigc::mem_fun(*this, &PageFileWr::OnFileChooseT      ));
            tbtnFileOpen    ->signal_button_release_event().connect(sigc::mem_fun(*this, &PageFileWr::OnFileChooseB      ));
            ebxSetCh         .signal_focus_out_event     ().connect(sigc::mem_fun(*this, &PageFileWr::OnChangeCh         ));
            ebxSetCh         .signal_key_release_event   ().connect(sigc::mem_fun(*this, &PageFileWr::OnKeyCh            ));
            ebxSetFS         .signal_focus_out_event     ().connect(sigc::mem_fun(*this, &PageFileWr::OnChangeFs         ));
            ebxSetFS         .signal_key_release_event   ().connect(sigc::mem_fun(*this, &PageFileWr::OnKeyFs            ));
            cbxSetFmt       ->signal_changed             ().connect(sigc::mem_fun(*this, &PageFileWr::OnChangeFmt        ));
            ebxWaveNumFrms   .signal_focus_out_event     ().connect(sigc::mem_fun(*this, &PageFileWr::OnChangeN          ));
            ebxWaveNumFrms   .signal_key_release_event   ().connect(sigc::mem_fun(*this, &PageFileWr::OnKeyN             ));
            ebxWaveTimeDur   .signal_focus_out_event     ().connect(sigc::mem_fun(*this, &PageFileWr::OnChangeT          ));
  sigKeyT = ebxWaveTimeDur   .signal_key_release_event   ().connect(sigc::mem_fun(*this, &PageFileWr::OnKeyT             ));

        MRU_FileRshAll = new CbT<PageFileWr>();
        MRU_FileRshAll->SetCallback(this, &PageFileWr::OnFileRshAll);
  ctMd->MSU_FileRshAll = MRU_FileRshAll;

        MRU_FaveRshAll = new CbT<PageFileWr>();
        MRU_FaveRshAll->SetCallback(this, &PageFileWr::OnWaveRshAll);
  ctMd->MSU_FaveRshAll = MRU_FaveRshAll;

holdOffAction = false;
  return;
}
void     PageFileWr::DisConnect          ( void                  ) {
  holdOffAction = true;
  sigKeyT.disconnect();
  holdOffAction = false;
  return;
}
void     PageFileWr::SetupWave           ( void                  ) {
  uint    dex;

  taf->SetAccessWrite();
  sig->ReBase(1, 1);
  sig->SetFS(48000.0);
  dex = cbxSetFmt->get_active_row_number();
  trf->OnCreate(sig->GetCh(), sig->GetFS());
  trf->FmtSetType((NumSys::eType)dex);
  trf->FmtSetCh(sig->GetCh());
  trf->FmtSetFS(sig->GetFS());
  trf->SetN(sig->GetN());

  holdOffAction = false;
  return;
}

bool     PageFileWr::OnKeyFileName       ( GdkEventKey    *i_d   ) {
  if((i_d->keyval == GDK_KEY_Return) || (i_d->keyval == GDK_KEY_Tab))
    OnChangeFileName(NULL);
  return true;
}

void     PageFileWr::OnFileOpenWr        ( void                  ) {
  Gtk::FileChooserDialog   *dlg;

  dlg = new Gtk::FileChooserDialog("Please choose a wave file", Gtk::FILE_CHOOSER_ACTION_SAVE);
  dlg->set_transient_for(*parent);
  dlg->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dlg->add_button(Gtk::Stock::OK,     Gtk::RESPONSE_OK);

  Glib::RefPtr<Gtk::FileFilter> fltWav = Gtk::FileFilter::create();
  fltWav->set_name("Wave files");
  fltWav->add_mime_type("audio/x-wav");
  fltWav->add_pattern("*.wav");
  dlg->add_filter(fltWav);

  Glib::RefPtr<Gtk::FileFilter> fltTxt = Gtk::FileFilter::create();
  fltTxt->set_name("Text files");
  fltTxt->add_mime_type("text/plain");
  dlg->add_filter(fltTxt);

  Glib::RefPtr<Gtk::FileFilter> fltAll = Gtk::FileFilter::create();
  fltWav->set_name("All files");
  fltWav->add_pattern("*.*");
  dlg->add_filter(fltAll);


  dlg->set_current_folder(ce->GetWorkingDir());
  int result = dlg->run();
  dlg->hide();
  char tStr[32768];
  strcpy(tStr, dlg->get_filename().c_str());

  switch(result) {
    case(Gtk::RESPONSE_OK):
      fprintf(stdout, "\n\nFILE NAME %s\n\n", tStr);fflush(stdout);
      ebxCtlFileName.set_text(tStr);
      OnChangeFileName(NULL);
      break;
    case(Gtk::RESPONSE_CANCEL):
      return;
      break;
    default:
      return;
      break;
    }
  return;
  }
bool     PageFileWr::OnFileChooseT       ( GdkEventButton *i_ev  ) {
  if(i_ev->type == GDK_2BUTTON_PRESS)
    OnFileOpenWr();
  return true;
}
bool     PageFileWr::OnFileChooseB       ( GdkEventButton *i_ev  ) {
  if(i_ev->type == GDK_BUTTON_RELEASE)
    OnFileOpenWr();
  return true;
}
void     PageFileWr::OnFileWrite         ( void                  ) {

  ctWave->DoIt();
  AudioFiler::eStatus status;
  char  tStr[32768];

  strcpy(tStr, ce->GetFileNameAbs());
  status = taf->SetFileNameWrite(tStr);
       if((status  == AudioFiler::eStatus::FST_NOENT)) {
    fprintf(stdout, "Brand New File\n");fflush(stdout);
  }
  else if((status  == AudioFiler::eStatus::FST_IDLE) || (status == AudioFiler::eStatus::FST_WRITEWARN)) {
    fprintf(stdout, "File Present, ready to write WARNING: OVERWRITING\n");fflush(stdout);
  }
  else {
    fprintf(stdout, "Unknown File Status - I'm not going to proceed\n");fflush(stdout);
    return;
  }
  taf->Open();
  status = taf->GetStatus();
  if((status  != AudioFiler::eStatus::FST_OPENWR) && (status != AudioFiler::eStatus::FST_WRITEWARN))
    return;
  trf->Build();
  two->WriteAry();
  taf->Close();

  return;
  }

bool     PageFileWr::OnChangeFileName    ( GdkEventFocus   *i_e    ) {
  char tStr[32768];
  strcpy(tStr, ebxCtlFileName.get_text().c_str());

  ce->SetFileName(tStr);
  taf->SetFileNameWrite(tStr);
  ClearFileInfo();
  ebxCtlFileName.set_text(tStr);
  ctMd->MRD_WaveChanged();
  return false;
}
bool     PageFileWr::OnKeyCh             ( GdkEventKey    *i_d   ) {
  if((i_d->keyval == GDK_KEY_Return) || (i_d->keyval == GDK_KEY_Tab))
    OnChangeCh(NULL);
  return true;
}
bool     PageFileWr::OnChangeCh          ( GdkEventFocus  *i_e   ) {
  llong  nn;
  llong  oldC;
  llong  newC;
  char  *cc;
  double dd;

  if(holdOffAction) return true;
  cc = (char *)ebxSetCh.get_text().c_str();
  dd = trf->FmtGetFS();
  if(IsDoubleFixed(cc))
    sscanf(cc, "%lf", &dd);
  if(dd > 4)
    dd = 4;
  if(dd <  1)
    dd = 1;
  newC = (llong)dd;
  oldC = sig->GetCh();
  if(oldC == newC)
    return true;
  nn = sig->GetN();
  sig->ReBase(newC, nn);
  trf->FmtSetCh(dd);
  ctMd->MRD_WaveChanged();
  return true;
}
bool     PageFileWr::OnKeyFs             ( GdkEventKey    *i_d   ) {
  if((i_d->keyval == GDK_KEY_Return) || (i_d->keyval == GDK_KEY_Tab))
    OnChangeFs(NULL);
  return true;
}
bool     PageFileWr::OnChangeFs          ( GdkEventFocus  *i_e   ) {
  char  *cc;
  double dd;

  if(holdOffAction) return true;
  cc = (char *)ebxSetFS.get_text().c_str();
  dd = sig->GetFS();
  if(IsDoubleFixed(cc))
    sscanf(cc, "%lf", &dd);
  sig->SetFS(dd);
  trf->FmtSetFS(dd);
  ctMd->MRD_WaveChanged();
  return true;
}
void     PageFileWr::OnChangeFmt         ( void                  ) {
  llong ll;
  if(holdOffAction) return;
  ll = cbxSetFmt->get_active_row_number();
  tns->SetNumType((NumSys::eType)ll);
  trf->FmtSetType((NumSys::eType)ll);
  ctMd->MRD_WaveChanged();
  return;
}
bool     PageFileWr::OnKeyN              ( GdkEventKey    *i_d   ) {
  if((i_d->keyval == GDK_KEY_Return) || (i_d->keyval == GDK_KEY_Tab))
    OnChangeN (NULL);
  return true;
}
bool     PageFileWr::OnChangeN           ( GdkEventFocus  *i_e   ) {
  char  *cc;
  llong ll;

  if(holdOffAction) return true;
  cc = (char *)ebxWaveNumFrms.get_text().c_str();
  ll = sig->GetN();
  if(IsDoubleFixed(cc))
    sscanf(cc, "%lld", &ll);
  ctWave->SetN(ll);
  ll = sig->GetN();
  trf->SetN(ll);
  trf->Build();
  ctMd->MRD_WaveChanged();
  return true;
}
bool     PageFileWr::OnKeyT              ( GdkEventKey    *i_d   ) {
  if((i_d->keyval == GDK_KEY_Return) || (i_d->keyval == GDK_KEY_Tab))
    OnChangeT (NULL);
  return true;
}
bool     PageFileWr::OnChangeT           ( GdkEventFocus  *i_e   ) {
  char   *cc;
  llong   ll;
  double  dd;

  if(holdOffAction) return true;
  cc = (char *)ebxWaveTimeDur.get_text().c_str();
  dd = sig->GetT();
  if(IsDoubleFixed(cc))
    sscanf(cc, "%lf", &dd);
  ctWave->SetT(dd);
  ll = sig->GetN();
  trf->SetN(ll);
  ctMd->MRD_WaveChanged();
  return true;
}



void     PageFileWr::ClearFileInfo       ( void                  ) {
  holdOffAction = true;
  ebxCtlFileName.set_text("");
  holdOffAction = false;
  return;
}



bool     PageFileWr::OnFileRshAll        ( void  *i_d            ) {
  char   tStr[1024];

  holdOffAction = true;
  strcpy(tStr, ce->GetFileNameAbs());
  ebxCtlFileName.set_text(tStr);
  //==
  holdOffAction = false;
  return false;
  }
bool     PageFileWr::OnWaveRshAll        ( void  *i_d            ) {
  char   tStr[1024];
  double dd;
  llong  ll;

  holdOffAction = true;
  //==
  ll = sig->GetCh();
  sprintf(tStr, "%lld", ll);
  ebxSetCh.set_text(tStr);
  //==
  dd = sig->GetFS();
  IntWithComma(tStr, dd);
  ebxSetFS.set_text(tStr);
  //==
  ll = tns->GetType();
  cbxSetFmt->set_active(ll);
  //==
  ll = trf->GetFileSize();
  IntWithComma(tStr, ll);
  ebxFileSize.set_text(tStr);
  //==
  ll = trf->GetNumFrms();
  IntWithComma(tStr, ll);
  ebxWaveNumFrms.set_text(tStr);
  //==
  dd = sig->GetT();
  if(dd > 1.0)    SecToHMS(tStr, dd, true);
  else            EngString(tStr, dd, 3,  (char *)"");
  ebxWaveTimeDur.set_text(tStr);
  //==
  holdOffAction = false;
  return false;
}
