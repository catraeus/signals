// $Id: WinOs.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : OScope.hpp
// Original Author    : duncang
// Creation Date      : Oct 14, 2012
// Copyright          : Copyright © 2012 - 2017 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================
/*! \brief  The place where time analysis takes place.

Frames, Samples, Pxls and all that.
-----------------------------------
      I'm a statistician, so sample is a reserved word meaning a "draw from the well."  The well
        is homogeneous and the bucket takes in a "sensible" way.  Sensible means either ordered or
        random.  Now ... don't get me wrong, I know we're not doing aggregate analysis as a
        statistics does ... we are doing signal analysis of a Reimann manifold in (C1,R1) domain;
        but I use Sample to mean a group, bucket, view, subset of the individual time-marked
        voltage values out of the audio interface.

      I'm a telecom guy too, so a Frame means a single atomic group of data acquired at one single
        conceptual instant.  The data may be unrelated (many people's conversations) or the data
        might be very closely related (the 32 microphones in an orchestral recording session.)
        A Frame is one and only one time-instant worth of channels.

      I'm an audio guy, so Channel means one single microphone, single guitar, single voice.
        Don't try to put a structure of disjoint sources packaged into a single "channel."  A
        surround 17.3 Frame has 20 channels.  They are related by whatever their fractional
        notation means, but it's not a "Surround Channel" here, it's a Surround Source.

      I'm an audio guy, so a pile of related channels is a Group.

Vector Spaces:
--------------
      There are several arrays of arrays, not matrices (in my world) because the rows are
        single-valued periodic arrays and the term "column" is not relevant, because there is no
        sensible column operation.  Stop trying to make EVERYTHING a matrix.
        SO
        There are buhcnes of this **thing and that **stuff.  The first index is nCh.  The second
        index is nSmp.  Smp is variable during operation.  On the Signal side it is Frames of audio
        data straight from the CODEC (or its resampler, but who cares if it is resampled it is
        what we have.)
        On the analyzed side, which is the scope, it is Pxls.

Who makes what?
---------------
      These spaces, the Signal Side and the Analyzed Side, need allocation.  The Signal Side is
        from either the sound card or from the waveform file.  The sound card version is assumed
        to be double-buffered, so when I work on it, it won't be over-written as the next sample
        is acquired.
      So, ALSA or the file manager will get that stuff into memory and I will ask for pointers to
        their space.  It might be nice to give those as pointers, but that will be running with
        scissors, so I probably won't.
      I allocate space for the analyzer in the analyzer, so here in the OScope, I just do pointers.
      I allocate space for the scope in the scope, so that's a reference here too.  This has one
        funky exception ... the array of vectors of the Scope Scr is done here.  The Scope Scr
        is a single object to handle all drawing of a single Channel.  So I will new() the anaCh**
        but not the nCh anaCh* individuals because I will get them from the Scopes after I build them.
      So, the WinOs doesn't slosh data around, it seems. Hmmmm.
*/

#ifndef __OSCOPE_HPP_
#define __OSCOPE_HPP_

#include <gtkmm.h>

#include <caes/CaesCallBack.hpp>
#include <caes/AudioFile/Signal.hpp>

#include "../../Cfg/CfgEnv.hpp"
#include "../../Cfg/CfgParticles.hpp"
#include "../../Ctl/CtlMsgDspch.hpp"

#include "DrwOs.hpp"

#include "FrmOsAxisH.hpp"
#include "FrmOsAxisV.hpp"

#include "FrmOsHor.hpp"
#include "FrmOsVrt.hpp"

class WinOs: public Gtk::Window {
  private:
    enum eConst {
      EWOC_MAX_HORIZ_WIDTH = 2048
      };
  public:
                  WinOs             ( Signal *i_sig      );
    virtual      ~WinOs             ( void               );
  protected:
    virtual void  on_hide           ( void                          );
    virtual void  on_show           ( void                          );
    virtual void  on_size_allocate  ( Gtk::Allocation& i_allocation );
  private:
            void  BuildEnv          ( Signal *i_sig      );
            void  BuildSubs         ( Signal *i_sig      );
            void  BuildMain         ( void               );

            void  Connect           ( void               );
            void  ReTitle           ( void               );
  private:


  private:
//==== The Main Window Envelope
    Gtk::Frame         frmMain;
    Gtk::Box           vbxMain;
    Gtk::Box           hbxMain;        // Contains vwDrwOs, axes AND the Horiz and Vert panels to its right.


//==== Scope
//==== Oscilloscope Draw Screen
    DrwOs             *vwDrwOs;            // The cairo draw thingamabob
    Gtk::Box           hbxScrs;         // Contains the vbxScrs that has all the other junk ... AND ... the vAxis.
    Gtk::Box           vbxScrs;         // Contains the drawscreen + hAxis and buffers


    Gtk::Box           hbxBfDdTop;      // Sliver above vwDrwOs to allow vAxis to center its labels on graticules
    Gtk::Box           hbxBfDdBot;      // Sliver below vwDrwOs to allow vAxis to center its labels on graticules

    FrmOsAxisV        *frmAxisV;        // Contains the vbxScrs that has all the other junk ... AND ... the vAxis.

    FrmOsAxisH        *frmAxisH;

    Gtk::Box           hbxBfDdLeft;      // Sliver left  of vwDrwOs to allow hAxis to center its labels on graticules
    Gtk::Box           hbxBfDdRite;      // Sliver right of vwDrwOs to allow hAxis to center its labels on graticules
    Gtk::Box           hbxVwDs;          // To allow left.right slivers

//==== Controls
    Gtk::Notebook     *nbkControls;
    Gtk::Box           hbxWinCtlHoriz;
    Gtk::Box           hbxWinCtlVert;
    FrmOsHor          *vwOsHor;
    FrmOsVrt          *vwOsv;

//==== Status Bar all the way at the bottom
    Gtk::Frame         frmStbMain;
    Gtk::Statusbar    *stbMain;

// Analyzer
  private:
    MdlOs             *mdOs;

// Environment
  private:
    CfgEnv            *ce;
    CfgParticles      *cp;

// ====  Message System
  private:
    CtlMsgDspch       *ctMd;

  public:
    CbV               *MSU_OsWin; //!<To highlight the scope button  Doesn't go to messaging system because it's purely GUI. Talks to WinMain
  };

#endif /* __OSCOPE_HPP_ */
