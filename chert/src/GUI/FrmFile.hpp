
// $Id: FrmFile.hpp 754 2023-03-19 03:05:07Z duncang $

//=================================================================================================
// Original File Name : FrmFile.hpp
// Original Author    : duncang
// Creation Date      : 2017-01-05T02:48:07,195961774+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
/* Description       :



*/
//
//=================================================================================================

#ifndef __FRM_FILE_HPP_
#define __FRM_FILE_HPP_

#include <gtkmm.h>

#include <caes/CaesTypes.hpp>
#include <caes/CaesString.hpp>

#include <caes/AudioFile/AudioFiler.hpp>
#include <caes/AudioFile/Signal.hpp>
#include <caes/AudioFile/RiffMgr.hpp>
#include <caes/AudioFile/WaveFiler.hpp>

#include "../Cfg/CfgParticles.hpp"
#include "../Cfg/CfgEnv.hpp"

#include "../Ctl/CtlMsgDspch.hpp"

class FrmFile: public Gtk::Frame {
  public:
                      FrmFile        ( Gtk::Window *i_parent, Signal *i_sig );
    virtual          ~FrmFile        (                    );
             void     ClearFileInfo  ( void               );
             void     ClearRiffInfo  ( void               );
             void     FillFileInfo   ( void               );
             void     FillRiffInfo   ( void               );
             void     OnFileOpen     ( void               );
  private:
             void     BuildEnv       ( Signal *i_sig      );
             void     BuildMain      ( void               );
             void     Connect        ( void               );

  public:
  private:
    CfgParticles        *cp;
    CfgEnv              *ce;
    Gtk::Window         *parent;

//    MdlFile             *mdFile;
    AudioFiler          *taf; // a little gangly, but these three are the model/controller stuff
    RiffMgr             *trf;
    WaveFiler           *twf;
    Signal              *tsig;

    Gtk::Box             vbxFilePad;
    Gtk::Box             hbxFileInfo;
    Gtk::Box             hbxRiffInfo;
// == In the hbxFileInfo
    Gtk::Label           lblFileName;
  public:
    Gtk::Entry           ebxFileName;
  private:
    Gtk::Label           lblFileSize;
  public:
    Gtk::Entry           ebxFileSize;
  private:
    Gtk::Box             boxPadFile;
    Gtk::Box             boxPadBetween;
    Gtk::Button         *btOpen;

// == In the hbxStreamInfo;
  private:
    Gtk::Label           lblRiffFS;
  public:
    Gtk::Entry           ebxRiffFS;
  private:
    Gtk::Label           lblRiffFmt;
  public:
    Gtk::Entry           ebxRiffFmt;
  private:
    Gtk::Label           lblRiffBitDepth;
  public:
    Gtk::Entry           ebxRiffBitDepth;
  private:
    Gtk::Label           lblRiffNumCH;
  public:
    Gtk::Entry           ebxRiffNumCH;

    CtlMsgDspch         *ctMd;

};

#endif // __FRM_FILE_HPP_
