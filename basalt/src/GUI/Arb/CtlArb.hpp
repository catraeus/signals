// $Id: CtlArb.hpp 506 2019-12-25 15:35:12Z duncang $

//=================================================================================================
// Original File Name : CtlArb.h
// Original Author    : duncang
// Creation Date      : Nov 14, 2011
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#ifndef _CTLARB_HPP__
#define _CTLARB_HPP__


#include <gtkmm.h>

#include "../../Cfg/CfgParticles.hpp"
#include "../../Cfg/CfgStrings.hpp"

#include <caes/Alsa/Alsa.hpp>
#include <caes/Alsa/AlsaStreamOut.hpp>
#include "../../ArbGen/WaveOut.hpp"
#include "Readout.hpp"

class CtlArb : public Gtk::VBox {
  public:
                  CtlArb(Alsa *i_ae, AlsaStreamOut *i_aso);
    virtual      ~CtlArb();
            void  Start(void);
  protected:
            bool  OnMousePressedFreq(GdkEventButton* event);
            bool  OnMousePressedLevel(GdkEventButton* event);
            bool  OnButtonPressed(GdkEventButton* event);
            bool  OnMuteButtonPressed(GdkEventButton *event);
            bool  OnKeyPressed(GdkEventKey* event);
            void  OnQuietTermPressed(void);
            void  OnWaveChanged(void);
            bool  MeterTick(int i_dummy);
  private:
            void  Mute(void);
            void  UnMute(void);
  public:
    WaveOut                    *theWave;
  protected:
    Gtk::VBox                   vbx_App;

    Gtk::Frame                 *fram_Freq;
    Gtk::EventBox               evbx_FreqBgColor;
    Gtk::Alignment             *alm_FreqBgColor;
    Gtk::Alignment             *alm_FreqTxt;
    Gtk::VBox                   vbx_FreqBgPadV;
    Gtk::HBox                   hbx_FreqBgPadH;
    Gtk::Label                 *lbl_FreqText;
    Gtk::EventBox               evbx_FreqBgTxt;

    Gtk::Frame                 *fram_Level;
    Gtk::EventBox               evbx_LevelBgColor;
    Gtk::Alignment             *alm_LevelBgColor;
    Gtk::Alignment             *alm_LevelTxt;
    Gtk::VBox                   vbx_LevelBgPadV;
    Gtk::HBox                   hbx_LevelBgPadH;
    Gtk::Label                 *lbl_LevelText;
    Gtk::EventBox               evbx_LevelBgTxt;

    Gtk::VBox                   vbx_ButtonsV;
    Gtk::HBox                   hbx_ButtonsH;
    Gtk::ToggleButton          *tbtn_QuietTerm;
    Gtk::Image                 *tbim_QuietTerm;

    Gtk::RadioButton::Group     grp_WaveType;
    Gtk::RadioButton           *rbt_WaveTypeSine;
    Gtk::RadioButton           *rbt_WaveTypeIMD4;
    Gtk::RadioButton           *rbt_WaveTypeSweep;

    sigc::connection            connMeterTimer;
    sigc::slot<bool>            timerSlot;
    void                        FlashCursor(void);
  private:
    CfgStrings      *cs;
    CfgParticles    *cp;
    Alsa            *ae;
    AlsaStreamOut   *aso;
    Readout         *roFreq;
    Readout         *roLevel;
    Readout         *roCurrent;
    pthread_t        portThread;

    int dummy;
    //==============================================
    // Windows
    double      freqVal;
    double      levelVal;
    enum eFocusEnt{
        F_FREQ,
        F_AMPL
    };
  };

#endif /* _CTLARB_HPP__ */
