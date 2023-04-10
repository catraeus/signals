
// $Id: PageFileWr.cpp 756 2023-03-25 00:45:33Z duncang $

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
#include <caes/CaesMath.hpp>
#include <caes/AudioFile/NumSys.hpp>

#include "PageFileWr.hpp"
#include "WinMain.hpp"

         PageFileWr::PageFileWr          ( Gtk::Window *i_parent, Signal *i_sig, WaveFiler *i_two   )
: sig    ( i_sig    )
, two    ( i_two    )
, parent ( i_parent ) {
  BuildEnv    (      );
  BuildMain   (      );
  Connect     (      );
  SetupWave   (      );
  HnSigWrChg  ( NULL );
  OnChangeFmt (      );
}
         PageFileWr::~PageFileWr         ( void                  ) {
}
void     PageFileWr::BuildEnv            ( void                  ) {
  ce        = CfgEnv      ::GetInstance   ();
  ct        = CfgSettings ::GetInstance   ();
  cs        = CfgStrings  ::GetInstance   ();
  tns       = two         ->GetNumSys     ();
  trf       = two         ->GetRiffMgr    ();
  taf       = two         ->GetAudioFiler ();
  ctMd      = CtlMsgDspch ::GetInstance   ();
  return;
}
void     PageFileWr::BuildMain           ( void                  ) {
  set_orientation(Gtk::ORIENTATION_VERTICAL);
  BuildFile();

  tbtnFileOutSel    = new Gtk::ToolButton  (                       );
  tbtnFileOutSel   ->     set_icon_name    ( "document-open"       );
  tbtnFileOutSel   ->     set_has_tooltip  (  true                 );
  tbtnFileOutSel   ->     set_tooltip_text (  cs->strsFileOutSel   );

  tbtnFileOutWrite  = new Gtk::ToolButton  (                       );
  tbtnFileOutWrite ->     set_icon_name    ( "document-save"       );
  tbtnFileOutWrite ->     set_has_tooltip  (  true                 );
  tbtnFileOutWrite ->     set_tooltip_text (  cs->strsFileSaveNone );

  ebxSetCh       .set_editable (false);
  ebxSetCh       .set_sensitive(false);
  ebxSetFS       .set_editable (false);
  ebxSetFS       .set_sensitive(false);
  ebxFileSize    .set_editable (false);
  ebxFileSize    .set_sensitive(false);
  ebxWaveNumFrms .set_editable (false);
  ebxWaveNumFrms .set_sensitive(false);
  ebxWaveTimeDur .set_editable (false);
  ebxWaveTimeDur .set_sensitive(false);


  this               ->pack_start  (  frmCtlActions,         Gtk::PACK_SHRINK, 3 );
    frmCtlActions     .add         (  hbxCtlActions                              );
      hbxCtlActions   .pack_start  ( *tbtnFileOutSel,        Gtk::PACK_SHRINK    );
      hbxCtlActions   .pack_start  ( *tbtnFileOutWrite,      Gtk::PACK_SHRINK    );
  this               ->pack_start  (  frmCtlFileName,        Gtk::PACK_SHRINK, 3 );
    frmCtlFileName    .add         (  hbxCtlFileName                             );
      hbxCtlFileName  .pack_start  (  lblCtlFileName,        Gtk::PACK_SHRINK, 3 );
      hbxCtlFileName  .pack_start  (  ebxCtlFileName,        Gtk::PACK_SHRINK    );

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


  hbxCtlActions  .set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  hbxCtlFileName .set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  hbxCtlWaveSpec .set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  hbxCtlStream   .set_orientation(Gtk::ORIENTATION_HORIZONTAL);

  tStr = ce->GetFileNameAbs();  // only at startup
  lblCtlFileName .set_text("File Name:"  );  lblCtlFileName .set_alignment(Gtk::ALIGN_END  );
  ebxCtlFileName .set_text(tStr          );  ebxCtlFileName .set_alignment(Gtk::ALIGN_START);  ebxCtlFileName .set_width_chars(80);
  lblSetCh       .set_text("ch:"         );  lblSetCh       .set_alignment(Gtk::ALIGN_END  );
  ebxSetCh       .set_text(    "2"       );  ebxSetCh       .set_alignment(Gtk::ALIGN_END  );  ebxSetCh       .set_width_chars( 3);  ebxSetCh       .set_editable(true );
  lblSetFS       .set_text("FS:"         );  lblSetFS       .set_alignment(Gtk::ALIGN_END  );
  ebxSetFS       .set_text("1"           );  ebxSetFS       .set_alignment(Gtk::ALIGN_END  );  ebxSetFS       .set_width_chars(12);  ebxSetFS       .set_editable(false);
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
        tbtnFileOutSel  ->signal_button_release_event().connect(sigc::mem_fun(*this, &PageFileWr::OnFileChooseB      ));
        cbxSetFmt       ->signal_changed             ().connect(sigc::mem_fun(*this, &PageFileWr::OnChangeFmt        ));
        tbtnFileOutWrite->signal_button_release_event().connect(sigc::mem_fun(*this, &PageFileWr::OnFileWrite        ));

        HnCb_SigWrChg   = new CbT<PageFileWr>();
        HnCb_SigWrChg  ->SetCallback(this, &PageFileWr::HnSigWrChg);
  ctMd->HCB_SigWrChg  = HnCb_SigWrChg;

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

void     PageFileWr::OnFileOutSelect     ( void                  ) {
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


  dlg->set_current_folder(ct->GetDirNameIn());  // FIXME, make a DirNameOut in CfgSettings
  int result = dlg->run();
  dlg->hide();
  char tStr[32768];
  strcpy(tStr, dlg->get_current_folder().c_str());
  ct->SetDirNameIn(tStr);


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
    OnFileOutSelect();
  return true;
}
bool     PageFileWr::OnFileChooseB       ( GdkEventButton *i_ev  ) {
  if(i_ev->type == GDK_BUTTON_RELEASE)
    OnFileOutSelect();
  return true;
}
bool     PageFileWr::OnFileWrite         ( GdkEventButton *i_ev  ) {

  if(i_ev->type != GDK_BUTTON_RELEASE) return false;

  AudioFiler::eStatus status;
  char  tStr[32768];

  strcpy(tStr, taf->GetFileName());
  status = taf->SetFileNameWrite(tStr);
       if((status  == AudioFiler::eStatus::FST_NOENT)) {
    fprintf(stdout, "Brand New File\n");fflush(stdout);
  }
  else if((status  == AudioFiler::eStatus::FST_IDLE) || (status == AudioFiler::eStatus::FST_WRITEWARN)) {
    fprintf(stdout, "File Present, ready to write WARNING: OVERWRITING\n");fflush(stdout);
  }
  else {
    fprintf(stdout, "Unknown File Status - I'm not going to proceed\n");fflush(stdout);
    return false;
  }
  taf->Open();
  status = taf->GetStatus();
  if((status  != AudioFiler::eStatus::FST_OPENWR) && (status != AudioFiler::eStatus::FST_WRITEWARN)) {
    fprintf(stdout, "Oops, the output file didn't open correctly.\n");fflush(stdout);
    return false;
  }
  else {
    fprintf(stdout, "Ah, the output file opened correctly.\n");fflush(stdout);
  }
  trf->Build();
  two->WriteAry();
  taf->Close();

  return true;
  }

bool     PageFileWr::OnChangeFileName    ( GdkEventFocus  *i_e   ) {
  char tStr[32768];
  strcpy(tStr, ebxCtlFileName.get_text().c_str());
  taf->SetFileNameWrite(tStr);

  return false;
}
void     PageFileWr::OnChangeFmt         ( void                  ) {
  llong ll;
  char  tStr[32];

  if(holdOffAction) return; // I'm pretty sure nobody can set data format, so this is probably moot
  ll = cbxSetFmt->get_active_row_number();
  tns->SetNumType((NumSys::eType)ll);
  trf->FmtSetType((NumSys::eType)ll);

  //==
  ll = trf->GetFileSize(); // no need to do holdOffAction since ebxFileSize is not editable or sensitive
  IntWithComma(tStr, ll);
  ebxFileSize.set_text(tStr);


  return;
}

void     PageFileWr::ClearFileInfo       ( void                  ) {
  holdOffAction = true;
  ebxCtlFileName.set_text("");
  holdOffAction = false;
  return;
}

bool     PageFileWr::HnSigWrChg            ( void  *i_d            ) {
  char   tStr[32];
  double dd;
  llong  ll;

  holdOffAction = true;

  (void)i_d;
  //====
  dd = sig->GetFS();
  trf->FmtSetFS(dd);
  tStr[0] = '\0';
  sprintf(tStr, "%8.2lf", dd);
  ebxSetFS.set_text(tStr);

  //==  IMPORTANT Do this before getting file size or time length.
  ll = sig->GetCh();
  trf->FmtSetCh(ll);
  sprintf(tStr, "%lld", ll);
  ebxSetCh.set_text(tStr);

  //====
  ll = sig->GetN();
  IntWithComma(tStr, ll);
  trf->SetN(ll);
  ebxWaveNumFrms.set_text(tStr);

  //==
  ll = trf->GetFileSize();
  IntWithComma(tStr, ll);
  ebxFileSize.set_text(tStr);

  //==
  dd = sig->GetT();
  if(dd > 1.0)    SecToHMS(tStr, dd, true);
  else            EngString(tStr, dd, 3,  (char *)"");
  ebxWaveTimeDur.set_text(tStr);

  //== IMPORTANT When changing Data Type, refresh file size.

  //==
  holdOffAction = false;
  return false;
}

