// $Id: CtlArb.cpp 506 2019-12-25 15:35:12Z duncang $

//=================================================================================================
// Original File Name : CtlArb.cpp
// Original Author    : duncang
// Creation Date      : Nov 14, 2011
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include "CtlArb.hpp"

#include "../../Cfg/CfgEnv.hpp"

#include <gtkmm.h>
#include <stdio.h>
#include <string.h>


     CtlArb::CtlArb(Alsa *i_ae, AlsaStreamOut *i_aso)
: ae(i_ae)
, aso(i_aso)
{

  cs = CfgStrings::GetInstance();
  cp = CfgParticles::GetInstance();


  roFreq = new Readout();
  roFreq->SetMinValue(10.0);
  roFreq->SetMaxValue(20000.0);
  roFreq->SetUnits("Hz");
  roFreq->SetValue(440.0);
  roFreq->SetBright(true);
  roFreq->SetCurPos(3);
  roFreq->SetBright(false);

  roLevel = new Readout();
  roLevel->SetMinValue(-120.0);
  roLevel->SetMaxValue( 20.0);
  roLevel->SetUnits("dBFS");
  roLevel->SetValue(0.0);
  roLevel->SetBright(true);
  roLevel->SetCurPos(2);
  roLevel->SetBright(false);

  roCurrent = roFreq;

  theWave   = new WaveOut(ae, aso);


//=================================================================================================
//=================================================================================================
//=================================================================================================
  signal_key_press_event().connect(sigc::mem_fun(*this, &CtlArb::OnKeyPressed));

//=================================================================================================
//=================================================================================================
//=================================================================================================
//=================================================================================================
  //BuildMenus();

//=================================================================================================
//=================================================================================================
//=================================================================================================
//=================================================================================================
  const Gdk::RGBA *db = new Gdk::RGBA(cp->cols_Caes_BlueDark);
  const Gdk::RGBA *tu = new Gdk::RGBA(cp->cols_Caes_Tungsten);
  const Gdk::RGBA *rr = new Gdk::RGBA("#ff0000");
  const Gdk::RGBA *dr = new Gdk::RGBA("#400000");

  fram_Freq    = new Gtk::Frame(cs->s[cs->ANY_FREQUENCY]);
  fram_Freq->override_color(*tu, Gtk::STATE_FLAG_NORMAL);
  fram_Freq->override_background_color(*tu, Gtk::STATE_FLAG_NORMAL);

  lbl_FreqText = new Gtk::Label("");
  lbl_FreqText->set_markup(roFreq->GetPangoMarkup());
  lbl_FreqText->override_color(*rr, Gtk::STATE_FLAG_NORMAL);

  Gtk::Widget *l = fram_Freq->get_label_widget();
  l->override_color(*tu, Gtk::STATE_FLAG_NORMAL);


  alm_FreqBgColor   = new Gtk::Alignment(0.1, 0.1, 0.0, 0.0);
  alm_FreqTxt       = new Gtk::Alignment(0.1, 0.1, 0.2, 0.2);

  evbx_FreqBgColor.override_background_color(*db, Gtk::STATE_FLAG_NORMAL);
  evbx_FreqBgTxt.set_size_request(650,80);
  evbx_FreqBgTxt.override_background_color(*dr, Gtk::STATE_FLAG_NORMAL);

//=================================================================================================
  evbx_FreqBgColor.add(vbx_FreqBgPadV);
  vbx_FreqBgPadV.pack_start(hbx_FreqBgPadH, Gtk::PACK_EXPAND_WIDGET, 10); // to get a nice border around the frame on top/bot
  hbx_FreqBgPadH.pack_start(*fram_Freq, Gtk::PACK_EXPAND_WIDGET, 10);  // to get a nice border around the frame on sides
  fram_Freq->add(*alm_FreqBgColor);
  alm_FreqBgColor->add(evbx_FreqBgTxt);
  evbx_FreqBgTxt.add(*lbl_FreqText);

//=================================================================================================
  evbx_FreqBgColor.signal_button_release_event().connect(sigc::mem_fun(*this, &CtlArb::OnMousePressedFreq));


//=================================================================================================
//=================================================================================================
//=================================================================================================
//=================================================================================================
  fram_Level    = new Gtk::Frame(cs->s[cs->ANY_LEVEL]);
  fram_Level->override_color(*tu, Gtk::STATE_FLAG_NORMAL);
  fram_Level->override_background_color(*tu, Gtk::STATE_FLAG_NORMAL);

  lbl_LevelText = new Gtk::Label("");
  lbl_LevelText->set_markup(roLevel->GetPangoMarkup());
  lbl_LevelText->override_color(*rr, Gtk::STATE_FLAG_NORMAL);

  l = fram_Level->get_label_widget();
  l->override_color(*tu, Gtk::STATE_FLAG_NORMAL);

  alm_LevelBgColor   = new Gtk::Alignment(0.1, 0.1, 0.0, 0.0);
  alm_LevelTxt       = new Gtk::Alignment(0.1, 0.1, 0.2, 0.2);

  evbx_LevelBgColor.override_background_color(*db, Gtk::STATE_FLAG_NORMAL);
  evbx_LevelBgTxt.set_size_request(650,80);
  evbx_LevelBgTxt.override_background_color(*dr, Gtk::STATE_FLAG_NORMAL);

//=================================================================================================
  evbx_LevelBgColor.add(vbx_LevelBgPadV);
  vbx_LevelBgPadV.pack_start(hbx_LevelBgPadH, Gtk::PACK_EXPAND_WIDGET, 10); // to get a nice border around the frame on top/bot
  hbx_LevelBgPadH.pack_start(*fram_Level, Gtk::PACK_EXPAND_WIDGET, 10);  // to get a nice border around the frame on sides
  fram_Level->add(*alm_LevelBgColor);
  alm_LevelBgColor->add(evbx_LevelBgTxt);
  evbx_LevelBgTxt.add(*lbl_LevelText);

//=================================================================================================
  evbx_LevelBgColor.signal_button_release_event().connect(sigc::mem_fun(*this, &CtlArb::OnMousePressedLevel));


//=================================================================================================
//=================================================================================================
//=================================================================================================
//=================================================================================================
  tbtn_QuietTerm = new Gtk::ToggleButton("Output");
  tbtn_QuietTerm->set_size_request(50, 30);
  tbtn_QuietTerm->set_active(false);
  tbim_QuietTerm = new Gtk::Image(cp->pxbf_pn_LEDgrnOff);

//=================================================================================================
  rbt_WaveTypeSine  = Gtk::manage(new Gtk::RadioButton(grp_WaveType,"Sine"));
  rbt_WaveTypeIMD4  = Gtk::manage(new Gtk::RadioButton(grp_WaveType,"4-Tone IMD"));
  rbt_WaveTypeSweep = Gtk::manage(new Gtk::RadioButton(grp_WaveType,"Sine Sweep"));

//=================================================================================================
  tbtn_QuietTerm   ->signal_clicked().connect(sigc::mem_fun(*this,&CtlArb::OnQuietTermPressed));
  rbt_WaveTypeSine ->signal_clicked().connect(sigc::mem_fun(*this,&CtlArb::OnWaveChanged));
  rbt_WaveTypeIMD4 ->signal_clicked().connect(sigc::mem_fun(*this,&CtlArb::OnWaveChanged));
  rbt_WaveTypeSweep->signal_clicked().connect(sigc::mem_fun(*this,&CtlArb::OnWaveChanged));

//=================================================================================================
  vbx_ButtonsV.pack_start( hbx_ButtonsH,      Gtk::PACK_SHRINK,        10);
  hbx_ButtonsH.pack_start(*tbtn_QuietTerm,    Gtk::PACK_SHRINK,        10);
  hbx_ButtonsH.pack_start(*tbim_QuietTerm,    Gtk::PACK_SHRINK,         0);
  hbx_ButtonsH.pack_start(*rbt_WaveTypeSine,  Gtk::PACK_SHRINK,        10);
  hbx_ButtonsH.pack_start(*rbt_WaveTypeIMD4,  Gtk::PACK_SHRINK,        10);
  hbx_ButtonsH.pack_start(*rbt_WaveTypeSweep, Gtk::PACK_SHRINK,        10);


//=================================================================================================
//=================================================================================================
//=================================================================================================
//=================================================================================================
  add(vbx_App);
  vbx_App.pack_start     ( evbx_FreqBgColor,  Gtk::PACK_SHRINK,  0);
  vbx_App.pack_start     ( evbx_LevelBgColor, Gtk::PACK_SHRINK,  0);
  vbx_App.pack_start     ( vbx_ButtonsV,      Gtk::PACK_SHRINK,  0);



  return;
  }
     CtlArb::~CtlArb() {
  }
// Event Handlers
bool CtlArb::MeterTick(int i_dummy) {
  FlashCursor();
  return true;
  }
void CtlArb::FlashCursor(void) {
  static Readout *roLast = roFreq;
  if(roLast != roCurrent) {
    if(roCurrent == roFreq) {  // Yeah I know it wants a factory, I'll get there when there are lots of readouts.
      roLevel->SetBright(false);
      roFreq->SetBright(!roFreq->GetBright());
      }
    else {
      roLevel->SetBright(!roLevel->GetBright());
      roFreq->SetBright(false);
      }
    lbl_FreqText->set_markup(roFreq->GetPangoMarkup());
    lbl_LevelText->set_markup(roLevel->GetPangoMarkup());
    }
  else {
    if(roCurrent == roFreq) {  // Yeah I know it wants a factory, I'll get there when there are lots of readouts.
      roFreq->SetBright(!roFreq->GetBright());
      lbl_FreqText->set_markup(roFreq->GetPangoMarkup());
      }
    else {
      roLevel->SetBright(!roLevel->GetBright());
      lbl_LevelText->set_markup(roLevel->GetPangoMarkup());
      }
    }
  roLast = roCurrent;
  return;
  }
bool CtlArb::OnButtonPressed(GdkEventButton* event) {
  fprintf(stdout, "doink general\n");
  return true;
  }
bool CtlArb::OnMousePressedFreq(GdkEventButton* event) {
  roCurrent = roFreq;
  return true;
  }
bool CtlArb::OnMousePressedLevel(GdkEventButton* event) {
  roCurrent = roLevel;
  return true;
  }
bool CtlArb::OnKeyPressed(GdkEventKey* event) {
  bool setIt = false;
  char c;
  uint k;

  k = (uint)event->keyval;
  c = (char)event->keyval;
  switch(k) {
    case CfgParticles::K_UP:
      roCurrent->SetValueByInc();
      setIt = true;
      break;
    case CfgParticles::K_DOWN:
      roCurrent->SetValueByDec();
      setIt = true;
      break;
    case CfgParticles::K_LEFT:
      roCurrent->SetCurPos(roCurrent->GetCurPos() - 1);
      break;
    case CfgParticles::K_RIGHT:
      roCurrent->SetCurPos(roCurrent->GetCurPos() + 1);
      break;
    case CfgParticles::K_TAB:
      if(roCurrent == roFreq)
        roCurrent = roLevel;
      else
        roCurrent = roFreq;
      break;
    case CfgParticles::K_ENTER:
      setIt = true;
      break;
    case CfgParticles::K_BACK:
      fprintf(stdout, "back\n");
      break;
    case CfgParticles::K_ESC:
      fprintf(stdout, "escape\n");
      break;
    case CfgParticles::K_DELETE:
      fprintf(stdout, "delete\n");
      break;
    case CfgParticles::K_DEL:
      fprintf(stdout, "del\n");
      break;
    case CfgParticles::L_CHAR_MINUS:
      if(roCurrent == roLevel)
        roLevel->Invert();
      break;
    default:
      if((c >= '0') && (c <= '9')) {
        roCurrent->SetValueByPos(c);
        setIt = true;
        }
      else
        fprintf(stdout, "0x%x\n", k);
      break;
    }
  if(setIt) {
    if(roCurrent == roFreq)
      theWave->SetFreq(roFreq->GetValue());
    else
      theWave->SetLeveldBFS(roLevel->GetValue());
    }
  //on_key_press_event(event);
  return true;
  }
void CtlArb::Start(void) {


  if(!aso->err)
    theWave->Setup();
  if(!aso->err) {
    theWave->Announce();
    //fprintf(stdout, "CtlArb:  %lx\n", (long)aso);
    //if(!aso->err) rc = pthread_create(&portThread, NULL, &AlsaOut::StartOutput, (void *)aso);
    timerSlot      = sigc::bind(sigc::mem_fun(*this,  &CtlArb::MeterTick), dummy);
    connMeterTimer = Glib::signal_timeout().connect(timerSlot,          180);
    }
  }
void CtlArb::Mute(void) {
  fprintf(stdout, "Mute\n");
  return;
}
void CtlArb::UnMute(void) {
  fprintf(stdout, "UnMute\n");
  return;
}
void CtlArb::OnQuietTermPressed(void) {
  if(tbtn_QuietTerm->get_active()) {
    theWave->QT = false;
    tbim_QuietTerm->set(cp->pxbf_pn_LEDgrnOn);
    }
  else {
    theWave->QT = true;
    tbim_QuietTerm->set(cp->pxbf_pn_LEDgrnOff);
    }
  return;
  }
void CtlArb::OnWaveChanged(void) {
  if(rbt_WaveTypeSine->get_active())
    theWave->SetWave(WaveOut::EWT_SINE);
  else if(rbt_WaveTypeIMD4->get_active())
    theWave->SetWave(WaveOut::EWT_IMD4);
  else if(rbt_WaveTypeSweep->get_active())
    theWave->SetWave(WaveOut::EWT_SWEEP);
  else
    theWave->SetWave(WaveOut::EWT_SINE);
  return;
  }
