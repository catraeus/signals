
// $Id: PageFileWr.hpp 756 2023-03-25 00:45:33Z duncang $

//=================================================================================================
// Original File Name : PageFileWr.hpp
// Original Author    : duncang
// Creation Date      : Oct 17, 2012
// Copyright          : Copyright © 2011 - 2017 by Catraeus and Duncan Gray
//
// Description        :
//
//
//=================================================================================================

#ifndef __PAGE_FILE_WR_HPP_
#define __PAGE_FILE_WR_HPP_

#include <gtkmm.h>

#include <caes/CaesTypes.hpp>

#include "../Cfg/CfgEnv.hpp"
#include "../Cfg/CfgStrings.hpp"

//====  This is a tutorial application.  Lots of WAVE file stuff needs exposure.
#include <caes/AudioFile/NumSys.hpp>
#include <caes/AudioFile/Signal.hpp>
#include <caes/AudioFile/AudioFiler.hpp>
#include <caes/AudioFile/RiffMgr.hpp>
#include <caes/AudioFile/WaveFiler.hpp>

#include <gdk/gdkkeysyms.h>

#include "../Ctl/CtlWaveWr.hpp"
#include "../Ctl/CtlMsgDspch.hpp"

class PageFileWr: public Gtk::Box {
  public:
                  PageFileWr        ( Gtk::Window *i_parent, Signal *i_sig, WaveFiler *i_two  );
    virtual      ~PageFileWr        ( void                  );


            void  OnFileWrite       ( void                  );
            void  OnFileOutSelect   ( void                  );

  private:
            void  BuildEnv          ( void                  );
            void  BuildMain         ( void                  );
            void  BuildFile         ( void                  );
            void  SetupWave         ( void                  );
            void  Connect           ( void                  );
            void  DisConnect        ( void                  );


            void  ClearFileInfo     ( void                  );
            bool  OnKeyFileName     ( GdkEventKey    *i_e   );
            bool  OnFileChooseB     ( GdkEventButton *i_e   );
            bool  OnFileChooseT     ( GdkEventButton *i_e   );
            bool  OnChangeFileName  ( GdkEventFocus  *i_s   );
            bool  OnKeyCh           ( GdkEventKey    *i_e   );
            bool  OnChangeCh        ( GdkEventFocus  *i_e   );
            bool  OnKeyFs           ( GdkEventKey    *i_e   );
            bool  OnChangeFs        ( GdkEventFocus  *i_e   );
            void  OnChangeFmt       ( void                  );
            bool  OnKeyN            ( GdkEventKey    *i_e   );
            bool  OnChangeN         ( GdkEventFocus  *i_e   );
            sigc::connection          sigKeyT;
            bool  OnKeyT            ( GdkEventKey    *i_e   );
            bool  OnChangeT         ( GdkEventFocus  *i_e   );
  public:
  protected:
  private:

    CfgEnv                   *ce;
    CfgStrings               *cs;

    NumSys                   *tns;
    Signal                   *sig;
    WaveFiler                *two;
    RiffMgr                  *trf;
    AudioFiler               *taf;

    CtlWaveWr                *ctWave;

    Gtk::Window              *parent;

    Gtk::Frame                frmCtlActions;
    Gtk::Box                  hbxCtlActions;
    Gtk::ToolButton          *tbtnFileOutSel;
    Gtk::ToolButton          *tbtnFileOutWrite;

    Gtk::Frame                frmCtlFileName;
    Gtk::Box                  hbxCtlFileName;
    Gtk::Label                lblCtlFileName;
    Gtk::Entry                ebxCtlFileName;

    Gtk::Frame                frmCtlWaveSpec;
    Gtk::Box                  hbxCtlWaveSpec;
    Gtk::Label                lblSetCh;
    Gtk::Entry                ebxSetCh;
    Gtk::Label                lblSetFS;
    Gtk::Entry                ebxSetFS;
    Gtk::Label                lblSetFmt;
    Gtk::ComboBoxText        *cbxSetFmt;


    Gtk::Frame                frmCtlStream;
    Gtk::Box                  hbxCtlStream;
    Gtk::Label                lblWaveNumByte;
    Gtk::Entry                ebxFileSize;
    Gtk::Label                lblWaveNumFrms;
    Gtk::Entry                ebxWaveNumFrms;
    Gtk::Label                lblWaveTimeDur;
    Gtk::Entry                ebxWaveTimeDur;


    bool                      holdOffAction;

    CtlMsgDspch              *ctMd;
    CbT<PageFileWr>          *Handler_FileWrRshAll;
    CbT<PageFileWr>          *Handler_WaveRshAll;
    bool                      OnFileWrRshAll(void *i_d);
    bool                      OnWaveWrRshAll(void *i_d);
  };

#endif // __PAGE_FILE_WR_HPP_
