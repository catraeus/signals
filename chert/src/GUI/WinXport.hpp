
// $Id: WinXport.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : WinXport.hpp
// Original Author    : duncang
// Creation Date      : Dec 20, 2016
// Copyright          : Copyright © 2016 by Catraeus and Duncan Gray
//
// Description        :
//    A GTKmm Frame to hold start stop time and all that stuff.
//
//=================================================================================================


#ifndef __WIN_XPORT_HPP_
#define __WIN_XPORT_HPP_

#include <gtkmm.h>

#include <caes/CaesCallBack.hpp>
#include <caes/AudioFile/Signal.hpp>

#include "../Cfg/CfgParticles.hpp"

#include "../Ctl/Os/CtlOsHor.hpp"
#include "../Ctl/CtlXport.hpp"

#include "../Mdl/MdlOs.hpp"

#include "../Ctl/CtlMsgDspch.hpp"

class WinXport: public Gtk::Window {
  public:
  protected:
  private:
  public:
             WinXport(Signal *i_sig);
    virtual ~WinXport();
  private:
    void     BuildEnv               (Signal *i_sig);
    void     BuildMain              (void);
    void     BuildTimeSlider        (void);
    void     BuildSetup             (void);
    void     Connect                (void);

    void     OnFirst                (void) { ctXp->OnFirst(NULL); return;};
    void     OnPrev                 (void) { ctXp->OnPrev (NULL); return;};
    void     OnStart                (void) { ctXp->OnStart(NULL); return;};
    void     OnStop                 (void) { ctXp->OnStop (NULL); return;};
    void     OnNext                 (void) { ctXp->OnNext (NULL); return;};
    void     OnLast                 (void) { ctXp->OnLast (NULL); return;};
    void     OnWhole                (void) { ctXp->OnWhole(NULL); return;};

    void     OnTimeSlide            (void);

    bool     OnNextScreen           (void);

  public:
  private:
    // administrivia
    CfgParticles          *cp;
    // Transport Control
    Gtk::Box               vbxMain;
    Gtk::Box               hbxTbar;
    Gtk::Toolbar          *tbXprt;
    Gtk::ToggleToolButton *tbtnXprtFirst;
    Gtk::ToggleToolButton *tbtnXprtPrev;
    Gtk::ToggleToolButton *tbtnXprtStart;
    Gtk::ToggleToolButton *tbtnXprtStop;
    Gtk::ToggleToolButton *tbtnXprtNext;
    Gtk::ToggleToolButton *tbtnXprtLast;
    Gtk::ToggleToolButton *tbtnXprtWhole;
    Gtk::EventBox          evxCurrPosN;
    Gtk::EventBox          evxCurrPosT;
    Gtk::Label             lblCurrPosN;
    Gtk::Label             lblCurrPosT;
    static const char      txtCurrPosPrefix[];
    static const char      txtCurrPosSuffix[];

    //==================================================================
    // Time Slider
    Gtk::Box               hbxTimeSlider;
    Gtk::Frame            *frmTimeSlider;
    Gtk::Box               vbxTimeSlider;
    Gtk::Scale            *sclTimeSlider;
    Gtk::Box               hbxTimeNumeric;
    Gtk::Box               hbxSliderMech;
    Glib::RefPtr<
      Gtk::Adjustment>     adjTime;

    CtlOsHor              *ctOsHor;
    CtlXport              *ctXp;
    MdlOs                 *mdOs;


    //==================================================================
    // Connect down and up to get things done
    CtlMsgDspch           *ctMd;
    CbT<WinXport>         *MRU_XpTimN;
    bool                   XpTimN                 (void *i_dummy);
    CbT<WinXport>         *MRU_XpButSet;
    bool                   XpButSet             (void *i_butAry);

    //==================================================================
    // Control state of the thing ... FIXME but this really has to be down in the CtlXport, now doesn't it
    bool               running;
    bool               lastRunning;
    bool               sliderHoldOff;

};

#endif // __WIN_XPORT_HPP_
