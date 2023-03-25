// $Id: CtlFile.hpp 531 2020-06-28 00:11:47Z duncang $

//=================================================================================================
// Original File Name : twfWriteWrite.hpp
// Original Author    : duncang
// Creation Date      : Oct 27, 2012
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#ifndef __CTLtwf_HPP_
#define __CTLtwf_HPP_


#include <gtkmm.h>
#include "../../Cfg/CfgParticles.hpp"
#include "../../Cfg/CfgEnv.hpp"
#include <caes/AudioFile/RiffMgr.hpp>
#include <caes/AudioFile/AudioFiler.hpp>
#include <caes/AudioFile/WaveFiler.hpp>
#include <caes/CaesTypes.hpp>

class CtlFile: public Gtk::Frame {
  public:
          CtlFile(Signal *i_sig, WaveFiler *i_twf);
         ~CtlFile();
    void  OnFileOpen(void);
    void  OnFileWrite(void);
  private:
    void  BuildActions(void);
    void  SetFileName(char *);
    void  ClearFileInfo(void);

    RiffMgr                *trf;
    AudioFiler               *taf;
    WaveFiler                *twf;
    CfgParticles             *cp;
    CfgEnv                   *ce;

    Gtk::Toolbar             *tbar_File;
    Gtk::ToolButton          *tbtn_FileOpen;

    Gtk::Box                  vbx_Main;

    Gtk::Frame                frmCtlFileName;
    Gtk::Label                lblCtlFileName;
    Gtk::Box                  hbxCtlFileName;
    Gtk::Entry                ebxCtlFileName;
    Gtk::Button              *btnCtlFileWrite;

    Gtk::Frame                frmCtlFmt;
    Gtk::Box                  vbxCtlFmt;
    Gtk::Box                  hbxCtlFmt1;
    Gtk::Label                lblFmtCode;
    Gtk::Entry                ebxFmtCode;

    Gtk::Box                  hbxCtlFmt2;
    Gtk::Label                lblFmtNumChan;
    Gtk::Entry                ebxFmtNumChan;
    Gtk::Label                lblFmtSmplRate;
    Gtk::Entry                ebxFmtFrmRate;
    Gtk::Label                lblFmtWordSize;
    Gtk::Entry                ebxFmtWordSize;

    Gtk::Box                  hbxCtlFactData;
    Gtk::Frame                frmCtlData;
    Gtk::Box                  hbxCtlData;
    Gtk::Label                lblDataSize;
    Gtk::Entry                ebxDataSize;

    Gtk::Frame                frmCtlArray;
    Gtk::Box                  hbxCtlArray;
    Gtk::Label                lblWaveNumFrms;
    Gtk::Entry                ebxWaveNumFrms;
    Gtk::Label                lblWaveTimeDur;
    Gtk::Entry                ebxWaveTimeDur;

  };

#endif /* __CTLtwf_HPP_ */
