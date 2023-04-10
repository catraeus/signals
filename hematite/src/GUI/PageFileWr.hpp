
// $Id: PageFileWr.hpp 756 2023-03-25 00:45:33Z duncang $

//=================================================================================================
// Original File Name : PageFileWr.hpp
// Original Author    : duncang
// Creation Date      : Oct 17, 2012
// Copyright          : Copyright © 2012 - 2023 by Catraeus and Duncan Gray
//
// Description        :
/*

The sine jitter processing is the only thing that can turn on a re-write.  I don't think there's
  much value to letting, for example the gain normalization to send the file back out.  First
  is the problem that most apps will not permit peak greater than 1.0 etc. etc. bla bla.
SO
  the sine jitter processing, generally, makes a very very very low level signal.  I'll gain that up
  then it decimates it to something much more narrowband than the original.  Most often this will
  be to take a 48kHz input with a 1000-ish Hz carrier that is demodulated to be analyzed for
  near-in phase noise.  Even at that the output is the phase, not frequency and will have its DC
  taken out.  Thus making it so that wander is (kind-of) removed and there should be a missing
  hole at DC.  I had better do some TIE work in the analyzer, hunh?

Finally:
  The write controller might be moot and everything can stay here in the view.
      The Signal:: informs of the number of channels and samples.
      A WaveFiler that has a RIFF and FMT section is told by this page what the FMT stuff
          needs to look like.
So, let's have the Demodulate Signal be known to this page.
Let the Analyzer Emit a ctMd which is caught by this page.
This page then pushes FS, ch and N down to the File/Wave/Riff/Fmt stuff.
The user can set the bit depth, float vs. int on this page.  That's all.

*/
//
//
//=================================================================================================

#ifndef __PAGE_FILE_WR_HPP_
#define __PAGE_FILE_WR_HPP_

#include <gtkmm.h>

#include <caes/CaesTypes.hpp>

#include "../Cfg/CfgEnv.hpp"
#include "../Cfg/CfgSettings.hpp"
#include "../Cfg/CfgStrings.hpp"

//====  This is a tutorial application.  Lots of WAVE file stuff needs exposure.
#include <caes/AudioFile/NumSys.hpp>
#include <caes/AudioFile/Signal.hpp>
#include <caes/AudioFile/AudioFiler.hpp>
#include <caes/AudioFile/RiffMgr.hpp>
#include <caes/AudioFile/WaveFiler.hpp>

#include <gdk/gdkkeysyms.h>

#include "../Ctl/CtlMsgDspch.hpp"

class PageFileWr: public Gtk::Box {
  public:
                  PageFileWr        ( Gtk::Window *i_parent, Signal *i_sig, WaveFiler *i_two  );
    virtual      ~PageFileWr        ( void                  );


            bool  OnFileWrite       ( GdkEventButton *i_ev  );
            void  OnFileOutSelect   ( void                  );

            void  SetHasData        ( bool           i_d    ) { hasData = i_d; return        ; };
            bool  GetHasDatta       ( void                  ) {                return hasData; };

  private:
            void  BuildEnv          ( void                  );
            void  BuildMain         ( void                  );
            void  BuildFile         ( void                  );
            void  SetupWave         ( void                  );
            void  Connect           ( void                  );


            void  ClearFileInfo     ( void                  );
            bool  OnKeyFileName     ( GdkEventKey    *i_e   );
            bool  OnFileChooseB     ( GdkEventButton *i_e   );
            bool  OnFileChooseT     ( GdkEventButton *i_e   );
            bool  OnChangeFileName  ( GdkEventFocus  *i_s   );
            void  OnChangeFmt       ( void                  );
  public:
  protected:
  private:

    CfgEnv                   *ce;
    CfgSettings              *ct;
    CfgStrings               *cs;

    NumSys                   *tns;
    Signal                   *sig;
    WaveFiler                *two;
    RiffMgr                  *trf;
    AudioFiler               *taf;

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

    bool                      hasData;

    CtlMsgDspch              *ctMd;

    CbT<PageFileWr>          *HnCb_SigWrChg;
    bool                      HnSigWrChg(void *i_d);
  };

#endif // __PAGE_FILE_WR_HPP_
