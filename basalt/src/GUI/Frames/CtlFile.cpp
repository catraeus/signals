// $Id: CtlFile.cpp 552 2020-07-09 02:13:43Z duncang $

//=================================================================================================
// Original File Name : CtlFile.cpp
// Original Author    : duncang
// Creation Date      : Oct 27, 2012
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include "CtlFile.hpp"
#include "../WinMain.hpp"
#include <caes/CaesString.hpp>

      CtlFile::CtlFile(Signal *i_sig, WaveFiler *i_twf) {
  cp = CfgParticles::GetInstance();
  ce = CfgEnv::GetInstance();
  twf = i_twf;
  trf = twf->GetRiffMgr(); // must be done after assigning twf
  taf = twf->GetAudioFiler();

  tbar_File     = 0;
  tbtn_FileOpen = 0;
  BuildActions();
  //========================================================================
  //========================================================================
  //  Set up the whole shebang of the File vertical box
  vbx_Main.set_orientation(Gtk::ORIENTATION_VERTICAL);

  //========================================================================
  //  File Name
  hbxCtlFileName.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  frmCtlFileName.add(hbxCtlFileName);
  lblCtlFileName.set_text("File Name:");
  ebxCtlFileName.set_width_chars(30);
  ebxCtlFileName.set_text(ce->GetFileNameAbs()); // only at startup
  btnCtlFileWrite = new Gtk::Button("_Write", true);
  btnCtlFileWrite->signal_clicked().connect(sigc::mem_fun(*this, &CtlFile::OnFileWrite));

  hbxCtlFileName.pack_start(lblCtlFileName, Gtk::PACK_SHRINK, 3);
  hbxCtlFileName.pack_start(ebxCtlFileName, Gtk::PACK_SHRINK);
  hbxCtlFileName.pack_start(*btnCtlFileWrite, Gtk::PACK_SHRINK, 3);

  //========================================================================
  //========================================================================
  //  fmt chunk info
  vbxCtlFmt.set_orientation(Gtk::ORIENTATION_VERTICAL);
  frmCtlFmt.add(vbxCtlFmt);

  hbxCtlFmt1.set_orientation(Gtk::ORIENTATION_HORIZONTAL);

  lblFmtCode.set_text("fmt_ code:");
  ebxFmtCode.set_alignment(Gtk::ALIGN_START);
  ebxFmtCode.set_width_chars(34);
  ebxFmtCode.set_editable(false);

  hbxCtlFmt1.pack_start(lblFmtCode, Gtk::PACK_SHRINK, 3);
  hbxCtlFmt1.pack_start(ebxFmtCode, Gtk::PACK_SHRINK, 3);


  //========================================================================
  //========================================================================
  //  fmt parameters, row 2
  hbxCtlFmt2.set_orientation(Gtk::ORIENTATION_HORIZONTAL);

  lblFmtNumChan.set_text("Channels:");
  ebxFmtNumChan.set_alignment(Gtk::ALIGN_END);
  ebxFmtNumChan.set_width_chars(4);
  ebxFmtNumChan.set_editable(false);

  lblFmtSmplRate.set_text("Frame Rate:");
  ebxFmtFrmRate.set_alignment(Gtk::ALIGN_END);
  ebxFmtFrmRate.set_width_chars(9);
  ebxFmtFrmRate.set_editable(false);

  lblFmtWordSize.set_text("Word Size:");
  ebxFmtWordSize.set_alignment(Gtk::ALIGN_END);
  ebxFmtWordSize.set_width_chars(4);
  ebxFmtWordSize.set_editable(false);



  hbxCtlFmt2.pack_start(lblFmtNumChan,    Gtk::PACK_SHRINK, 3);
  hbxCtlFmt2.pack_start(ebxFmtNumChan,    Gtk::PACK_SHRINK, 3);
  hbxCtlFmt2.pack_start(lblFmtSmplRate,   Gtk::PACK_SHRINK, 3);
  hbxCtlFmt2.pack_start(ebxFmtFrmRate,    Gtk::PACK_SHRINK, 3);
  hbxCtlFmt2.pack_start(lblFmtWordSize,   Gtk::PACK_SHRINK, 3);
  hbxCtlFmt2.pack_start(ebxFmtWordSize,   Gtk::PACK_SHRINK, 3);
  //________________________________________________________________________
  vbxCtlFmt.pack_start(hbxCtlFmt1, Gtk::PACK_SHRINK, 3);
  vbxCtlFmt.pack_start(hbxCtlFmt2, Gtk::PACK_SHRINK, 3);

  //========================================================================
  //========================================================================
  //  fact and data chunk info
  hbxCtlFactData.set_orientation(Gtk::ORIENTATION_HORIZONTAL);

  hbxCtlData.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  frmCtlData.add(hbxCtlData);

  lblDataSize.set_text("data size:");
  ebxDataSize.set_alignment(Gtk::ALIGN_END);
  ebxDataSize.set_width_chars(14);
  ebxDataSize.set_editable(false);

  hbxCtlData.pack_start(lblDataSize,    Gtk::PACK_SHRINK, 3);
  hbxCtlData.pack_start(ebxDataSize,    Gtk::PACK_SHRINK, 3);

  hbxCtlFactData.pack_start(frmCtlData,         Gtk::PACK_EXPAND_WIDGET, 0);
  //========================================================================
  //========================================================================
  //  stream parameters

  hbxCtlArray.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  frmCtlArray.add(hbxCtlArray);

  lblWaveNumFrms.set_text("Frames:");
  ebxWaveNumFrms.set_alignment(Gtk::ALIGN_END);
  ebxWaveNumFrms.set_width_chars(13);
  ebxWaveNumFrms.set_editable(false);

  lblWaveTimeDur.set_text("Duration:");
  ebxWaveTimeDur.set_alignment(Gtk::ALIGN_END);
  ebxWaveTimeDur.set_width_chars(20);
  ebxWaveTimeDur.set_editable(false);

  hbxCtlArray.pack_start(lblWaveNumFrms, Gtk::PACK_SHRINK, 3);
  hbxCtlArray.pack_start(ebxWaveNumFrms, Gtk::PACK_SHRINK, 3);
  hbxCtlArray.pack_start(lblWaveTimeDur, Gtk::PACK_SHRINK, 3);
  hbxCtlArray.pack_start(ebxWaveTimeDur, Gtk::PACK_SHRINK, 3);

  //========================================================================
  //========================================================================
  //========================================================================
  //========================================================================
  vbx_Main.pack_start(*tbar_File,     Gtk::PACK_SHRINK, 3);
  vbx_Main.pack_start(frmCtlFileName, Gtk::PACK_SHRINK, 3);
  vbx_Main.pack_start(frmCtlFmt,      Gtk::PACK_SHRINK, 3);
  vbx_Main.pack_start(hbxCtlFactData, Gtk::PACK_SHRINK, 0);
  vbx_Main.pack_start(frmCtlArray,    Gtk::PACK_SHRINK, 3);
  add(vbx_Main);
  //show_all();
  }
      CtlFile::~CtlFile() {}
void  CtlFile::BuildActions(void) {
  //=================================================================================================
    tbar_File     = new Gtk::Toolbar();
    tbtn_FileOpen = new Gtk::ToolButton();
    Gtk::Image *wx = new Gtk::Image(cp->pxbf_op_fileOpen_bright);
    tbtn_FileOpen->set_icon_widget(*wx);

    tbar_File->append(*tbtn_FileOpen, sigc::mem_fun(*this, &CtlFile::OnFileOpen));

  return;
  }
void  CtlFile::OnFileWrite(void) {
  char tStr[1024];
  strcpy(tStr, ebxCtlFileName.get_text().c_str());
  if(!taf->SetFileNameWrite(tStr))
    return;
  taf->Open();
  trf->OnParse();
  taf->Close();


  //===============================================================================================
  ebxFmtCode.set_text(trf->FmtGetHdr());
  //================================================================================================
  sprintf(tStr, "%llu", trf->FmtGetCh());
  ebxFmtNumChan.set_text(tStr);
  //==
  IntWithComma(tStr, trf->FmtGetFS());
  ebxFmtFrmRate.set_text(tStr);
  //==
  sprintf(tStr, "%lld", trf->FmtGetBitDepth());
  ebxFmtWordSize.set_text(tStr);
  //===============================================================================================
  IntWithComma(tStr, trf->DataGetSize());
  ebxDataSize.set_text(tStr);

  //===============================================================================================
  IntWithComma(tStr, trf->GetNumFrms());
  ebxWaveNumFrms.set_text(tStr);
  //==
  SecToHMS(tStr, twf->GetDuration(), false);
  ebxWaveTimeDur.set_text(tStr);

  return;
  }
void  CtlFile::SetFileName(char *tStr) {
  ebxCtlFileName.set_text(tStr);
  return;
  }
void  CtlFile::ClearFileInfo(void) {

  ebxFmtCode.set_text("");
  ebxDataSize.set_text("");
  ebxFmtNumChan.set_text("");
  ebxFmtFrmRate.set_text("");
  ebxFmtWordSize.set_text("");
  ebxWaveNumFrms.set_text("");
  ebxWaveTimeDur.set_text("");
  }
void  CtlFile::OnFileOpen(void) {
  Gtk::FileChooserDialog td("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
  //td.set_transient_for(*theMain);
  td.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  td.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

  Glib::RefPtr<Gtk::FileFilter> filter_text = Gtk::FileFilter::create();
  filter_text->set_name("Text files");
  filter_text->add_mime_type("text/plain");
  td.add_filter(filter_text);

  Glib::RefPtr<Gtk::FileFilter> filter_xml = Gtk::FileFilter::create();
  filter_xml->set_name("XML files");
  filter_xml->add_mime_type("text/xml");
  td.add_filter(filter_xml);

  Glib::RefPtr<Gtk::FileFilter> filter_cpp = Gtk::FileFilter::create();
  filter_cpp->set_name("C/C++ files");
  filter_cpp->add_mime_type("text/x-c");
  filter_cpp->add_mime_type("text/x-c++");
  filter_cpp->add_mime_type("text/x-c-header");
  td.add_filter(filter_cpp);

  Glib::RefPtr<Gtk::FileFilter> filter_any = Gtk::FileFilter::create();
  filter_any->set_name("Any files");
  filter_any->add_pattern("*");
  td.add_filter(filter_any);


  td.run();
  td.hide();

  return;
  }
