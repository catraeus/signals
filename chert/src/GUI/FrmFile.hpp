
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
#include "../Cfg/CfgSettings.hpp"

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
    CfgSettings         *ct;
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
    Gtk::Entry           ebxFileName;
    Gtk::Label           lblFileSize;
    Gtk::Entry           ebxFileSize;
    Gtk::Box             boxPadFile;
    Gtk::Box             boxPadBetween;
    Gtk::Button         *btOpen;

// == In the hbxStreamInfo;
    Gtk::Label           lblRiffFS;
    Gtk::Entry           ebxRiffFS;
    Gtk::Label           lblRiffFmt;
    Gtk::Entry           ebxRiffFmt;
    Gtk::Label           lblRiffBitDepth;
    Gtk::Entry           ebxRiffBitDepth;
    Gtk::Label           lblRiffNumCH;
    Gtk::Entry           ebxRiffNumCH;

    CtlMsgDspch         *ctMd;

};

#endif // __FRM_FILE_HPP_
