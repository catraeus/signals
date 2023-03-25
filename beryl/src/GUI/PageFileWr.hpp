
// $Id: PageFileWr.hpp 634 2022-11-19 22:52:03Z duncang $

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
#include <gdk/gdkkeysyms.h>

#include <caes/CaesTypes.hpp>

//====  This is a tutorial application.  Lots of WAVE file stuff needs exposure.
#include <caes/AudioFile/NumSys.hpp>
#include <caes/AudioFile/Signal.hpp>
#include <caes/AudioFile/AudioFiler.hpp>
#include <caes/AudioFile/RiffMgr.hpp>
#include <caes/AudioFile/WaveFiler.hpp>

#include "../Cfg/CfgEnv.hpp"

#include "../Ctl/CtlWave.hpp"
#include "../Ctl/CtlMsgDspch.hpp"

class PageFileWr: public Gtk::Box {
  public:
                  PageFileWr        ( Gtk::Window *i_parent, Signal *i_sig, WaveFiler *i_two  );
    virtual      ~PageFileWr        ( void                  );


            void  OnFileWrite       ( void                  );
            void  OnFileOpenWr      ( void                  );

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

    NumSys                   *tns;
    Signal                   *sig;
    WaveFiler                *two;
    RiffMgr                  *trf;
    AudioFiler               *taf;

    CtlWave                  *ctWave;

    Gtk::Window              *parent;

    Gtk::Frame                frmCtlFileName;
    Gtk::Label                lblCtlFileName;
    Gtk::Box                  hbxCtlFileName;
    Gtk::Entry                ebxCtlFileName;
    Gtk::ToolButton          *tbtnFileOpen;

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
    CbT<PageFileWr>          *MRU_FileRshAll;
    bool                      OnFileRshAll(void *i_d);
    CbT<PageFileWr>          *MRU_FaveRshAll;
    bool                      OnWaveRshAll(void *i_d);
  };

#endif // __PAGE_FILE_WR_HPP_
