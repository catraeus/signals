/*
 * FrmFile.cpp
 *
 *  Created on: Jan 4, 2017
 *      Author: duncang
 */

#include "FrmFile.hpp"

          FrmFile::FrmFile        ( Gtk::Window *i_parent, Signal *i_sig )
: parent    ( i_parent )
, tsig      ( i_sig    ) {
  BuildEnv  ( i_sig    );
  BuildMain (          );
  Connect   (          );
  show_all  (          );
}
          FrmFile::~FrmFile       (        ) {
}
void      FrmFile::BuildEnv       ( Signal *i_sig   ) {
  cp     = CfgParticles ::GetInstance(       );
  ce     = CfgEnv       ::GetInstance(       );
  ct     = CfgSettings  ::GetInstance(       );
  twf    = new WaveFiler      ( i_sig );
  taf    = twf->GetAudioFiler (       ); // must be done after WaveFiler
  trf    = twf->GetRiffMgr    (       ); // must be done after WaveFiler
  ctMd   = CtlMsgDspch  ::GetInstance(       );
  return;
}
void      FrmFile::BuildMain      ( void   ) {
  set_label("File Info");

  btOpen = new Gtk::Button();
  Gtk::Image *wx = new Gtk::Image(cp->pxbf_op_file_open_bright);
  btOpen->set_image(*wx);

  boxPadFile.set_size_request(8, 0);
  boxPadBetween.set_size_request(16,0);

  vbxFilePad.set_orientation(Gtk::ORIENTATION_VERTICAL);
  hbxFileInfo.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  hbxRiffInfo.set_orientation(Gtk::ORIENTATION_HORIZONTAL);

  //====
  lblFileName.set_text("File Name:");
  lblFileName.set_has_tooltip(true);
  ebxFileName.set_width_chars(32);
  ebxFileName.set_editable(false);

  lblFileSize.set_text("File size:");
  ebxFileSize.set_alignment(Gtk::ALIGN_END);
  ebxFileSize.set_width_chars(12);
  ebxFileSize.set_editable(false);

  //====
  lblRiffFmt.set_text("FMT:");
  lblRiffFmt.set_has_tooltip(false);
  ebxRiffFmt.set_width_chars(8);
  ebxRiffFmt.set_alignment(Gtk::ALIGN_START);
  ebxRiffFmt.set_editable(false);

  lblRiffBitDepth.set_text("BitDepth:");
  lblRiffBitDepth.set_has_tooltip(false);
  ebxRiffBitDepth.set_width_chars(3);
  ebxRiffBitDepth.set_alignment(Gtk::ALIGN_END);
  ebxRiffBitDepth.set_editable(false);

  lblRiffNumCH.set_text("CH:");
  lblRiffNumCH.set_has_tooltip(false);
  ebxRiffNumCH.set_width_chars(4);
  ebxRiffNumCH.set_alignment(Gtk::ALIGN_END);
  ebxRiffNumCH.set_editable(false);

  lblRiffFS.set_text("FS:");
  lblRiffFS.set_has_tooltip(false);
  ebxRiffFS.set_width_chars(8);
  ebxRiffFS.set_alignment(Gtk::ALIGN_END);
  ebxRiffFS.set_editable(false);

  vbxFilePad.pack_start (hbxFileInfo,     Gtk::PACK_SHRINK, 3);
  hbxFileInfo.pack_start(lblFileName,     Gtk::PACK_SHRINK, 3);
  hbxFileInfo.pack_start(ebxFileName,     Gtk::PACK_SHRINK   );
  hbxFileInfo.pack_start(boxPadFile,      Gtk::PACK_SHRINK   );
  hbxFileInfo.pack_start(*btOpen,         Gtk::PACK_SHRINK   );
  hbxFileInfo.pack_start(boxPadBetween,   Gtk::PACK_SHRINK   );
  hbxFileInfo.pack_start(lblFileSize,     Gtk::PACK_SHRINK, 3);
  hbxFileInfo.pack_start(ebxFileSize,     Gtk::PACK_SHRINK, 3);

  vbxFilePad.pack_start (hbxRiffInfo,     Gtk::PACK_SHRINK, 3);
  hbxRiffInfo.pack_start(lblRiffFmt,      Gtk::PACK_SHRINK, 3);
  hbxRiffInfo.pack_start(ebxRiffFmt,      Gtk::PACK_SHRINK   );
  hbxRiffInfo.pack_start(lblRiffBitDepth, Gtk::PACK_SHRINK, 3);
  hbxRiffInfo.pack_start(ebxRiffBitDepth, Gtk::PACK_SHRINK   );
  hbxRiffInfo.pack_start(lblRiffNumCH,    Gtk::PACK_SHRINK, 3);
  hbxRiffInfo.pack_start(ebxRiffNumCH,    Gtk::PACK_SHRINK   );
  hbxRiffInfo.pack_start(lblRiffFS,       Gtk::PACK_SHRINK, 3);
  hbxRiffInfo.pack_start(ebxRiffFS,       Gtk::PACK_SHRINK   );

  add(vbxFilePad);
  return;
}
void      FrmFile::Connect        ( void   ) {
  btOpen->signal_clicked().connect(sigc::mem_fun(*this, &FrmFile::OnFileOpen));
  return;
}
void      FrmFile::OnFileOpen     ( void   ) {
  int  result;
  char tStr[32768];
  Gtk::FileChooserDialog   *dlgFileOpen;

  dlgFileOpen = new Gtk::FileChooserDialog("Please choose a wave file", Gtk::FILE_CHOOSER_ACTION_OPEN);
  dlgFileOpen->set_transient_for(*parent);
  dlgFileOpen->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dlgFileOpen->add_button(Gtk::Stock::OK,     Gtk::RESPONSE_OK);

  dlgFileOpen->set_current_folder(ct->GetDirNameIn());
  result = dlgFileOpen->run();
  dlgFileOpen->hide();
  switch(result) {
    case(Gtk::RESPONSE_OK):
      ct->SetDirNameIn(  dlgFileOpen->get_current_folder().c_str()  );
      strcpy(tStr, (char*)dlgFileOpen->get_filename().c_str());
      ce->SetFileName(tStr);
      AudioFiler::eStatus accResult;
      accResult = taf->SetFileNameRead(tStr);
      if(accResult != AudioFiler::FST_IDLE) {
        Gtk::MessageDialog *theD;
        theD = new Gtk::MessageDialog("File Problem!");
        theD->set_secondary_text("At some point I'll put more info here.");
        theD->run();
        delete theD;
        return;
      }
      taf->Open();
      trf->OnFileUpdateSrc();
      trf->OnParse();

      twf->OnFileChange();
      ctMd->MRD_FileReStart();

      ClearFileInfo();
      FillFileInfo();

      ClearRiffInfo();
      FillRiffInfo();
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
void      FrmFile::ClearFileInfo  ( void   ) {
  ebxFileName.set_text("");
  ebxFileSize.set_text("");
}
void      FrmFile::ClearRiffInfo  ( void   ) {
  ebxRiffFS       .set_text("");
  ebxRiffBitDepth .set_text("");
  ebxRiffNumCH    .set_text("");
}
void      FrmFile::FillFileInfo   ( void   ) {
  char  tStr[32768];
  char *bStr;

  bStr = (char *)taf->GetFileName();
  PathExtractFileName(bStr, tStr);
  ebxFileName.set_text(tStr);
  ebxFileName.set_tooltip_text(bStr); // the Tool Tip keeps the absolute path+file string.

  IntWithComma(tStr, taf->GetFileSize());
  ebxFileSize.set_text(tStr);

  return;
}
void      FrmFile::FillRiffInfo   ( void   ) {
  char    tStr[32768];
  double  tDbl;
  llong   tLL;

  strcpy(tStr, trf->FmtGetTagName());
  ebxRiffFmt.set_text(tStr);

  tLL = trf->FmtGetBitDepth();
  IntWithComma(tStr, tLL);
  ebxRiffBitDepth.set_text(tStr);

  tLL = tsig->GetCh();
  IntWithComma(tStr, tLL);
  ebxRiffNumCH.set_text(tStr);

  tDbl = tsig->GetFS();
  IntWithComma(tStr, tDbl);
  ebxRiffFS.set_text(tStr);

  return;
}
