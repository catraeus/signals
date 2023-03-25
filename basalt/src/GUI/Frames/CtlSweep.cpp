// $Id: CtlSweep.cpp 506 2019-12-25 15:35:12Z duncang $

//=================================================================================================
// Original File Name : CtlSweep.cpp
// Original Author    : duncang
// Creation Date      : Oct 27, 2012
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include "CtlSweep.hpp"
#include "../WinMain.hpp"
#include <caes/CaesString.hpp>

      CtlSweep::CtlSweep() {

  cp = CfgParticles::GetInstance();
  ce = CfgEnv::GetInstance();
  //========================================================================
  //========================================================================
  //  Set up the whole shebang of the File vertical box
  vbx_Main.set_orientation(Gtk::ORIENTATION_VERTICAL);

  //========================================================================
  //  File Name
  hbxType.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  frmType.add(hbxType);
  lblType.set_text("Sweep Type:");
  cbxTypeModel = Gtk::ListStore::create(cbxTypeCols);
  ebxType.set_model(cbxTypeModel);
  Gtk::TreeModel::Row row = *(cbxTypeModel->append());
  row[cbxTypeCols.type] = *(new Glib::ustring("Linear"));
  ebxType.set_active(row);
  row = *(cbxTypeModel->append());
  row[cbxTypeCols.type] = *(new Glib::ustring("Log Decade"));
  row = *(cbxTypeModel->append());
  row[cbxTypeCols.type] = *(new Glib::ustring("Log Octave"));

  hbxType.pack_start(lblType, Gtk::PACK_SHRINK, 3);
  hbxType.pack_start(ebxType, Gtk::PACK_SHRINK);

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
  vbx_Main.pack_start(frmType,        Gtk::PACK_SHRINK, 3);
  vbx_Main.pack_start(frmCtlFmt,      Gtk::PACK_SHRINK, 3);
  vbx_Main.pack_start(hbxCtlFactData, Gtk::PACK_SHRINK, 0);
  vbx_Main.pack_start(frmCtlArray,    Gtk::PACK_SHRINK, 3);
  add(vbx_Main);
  show_all();
  }
      CtlSweep::~CtlSweep() {}
void  CtlSweep::SetFileName(char *tStr) {
  //ebxType.set_active(0);
  return;
  }
void  CtlSweep::ClearFileInfo(void) {

  ebxFmtCode    .set_text("");
  ebxDataSize   .set_text("");
  ebxFmtNumChan .set_text("");
  ebxFmtFrmRate .set_text("");
  ebxFmtWordSize.set_text("");
  ebxWaveNumFrms.set_text("");
  ebxWaveTimeDur.set_text("");
  }
void  CtlSweep::OnTypeChanged(){
  Gtk::TreeModel::iterator iter = ebxType.get_active();
  if(iter) {
    Gtk::TreeModel::Row row = *iter;
    if(row) {
      Glib::ustring type = row[cbxTypeCols.type];
      fprintf(stdout, "type=%s\n", type.c_str());
      }
    }
  else
    fprintf(stdout, "Invalid Iterator\n");
  }
