
// $Id: WinMain.cpp 693 2022-12-28 03:44:39Z duncang $

//=================================================================================================
// Original File Name : WinMain.cpp
// Original Author    : duncang
// Creation Date      : Dec 11, 2010
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//
//=================================================================================================

#include "WinMain.hpp"

#include "../Cfg/CfgEnv.hpp"

#include <gtkmm.h>
#include <stdio.h>
#include <string.h>


     WinMain::WinMain(Signal *i_sig)
: sig(i_sig) {
#ifdef FIND_BADNESS
  std::cout << "=>WinMain::WinMain" << std::endl;
#endif
  char ss[32768];
  char tStr[257];

  ce             = CfgEnv::GetInstance();
  cs             = CfgStrings::GetInstance();
  cp             = CfgParticles::GetInstance();
  twf            = new WaveFiler(sig);
  theAlsa        = new Alsa(); // IMPORTANT  This has to be before CtlPhy happens
  mcAlsaStream   = new AlsaStreamOut(theAlsa);
  vcGenerator    = new CtlArb(theAlsa, mcAlsaStream);
  vcAlsaFacility = new CtlPhy("Audio Control", theAlsa, mcAlsaStream, vcGenerator);
  vcWaveFile     = new CtlFile(sig, twf);
  vcSweep        = new CtlSweep();


  BuildMenus();
  sprintf(tStr, "%s %d.%d build %d", ce->appName, ce->verMaj, ce->verMin, ce->buildNo);
  set_title(tStr);
  set_icon(cp->pxbf_xIconApp);

  fprintf(stdout, "ALSA Version:  %s\n", theAlsa->GetVersion()); fflush(stdout);
  theAlsa->PrintPcmSpecList();
//  theAlsa->PrintTree();


  vcGenerator->Start();

  ntbk_Ctl.append_page(*vcAlsaFacility, cs->s[CfgStrings::AUDIO_IO]);
  ntbk_Ctl.append_page(*vcWaveFile, "Wave File");
  ntbk_Ctl.append_page(*vcSweep,    "Sine Sweep");

  //signal_key_press_event().connect_notify(sigc::mem_fun(*this, &WinMain::OnKeyPressed));

  strcpy(ss, cs->s[cs->MAIN_TITLE]);
  strcat(ss, " -- version ");
  strcat(ss, cs->s[cs->ABOUT_VERSION]);
  set_title(ss);
  //set_size_request(400, 400);
  set_resizable(false);



//=================================================================================================
  set_icon(cp->pxbf_xIconApp);

//=================================================================================================
  stb_Main = new Gtk::Statusbar();
  stb_Main->push("Initializing", 0);
  //stb_Main->set_has_resize_grip(false);

//=================================================================================================
// Instrument
  hbx_Inst.pack_start(*vcGenerator, Gtk::PACK_EXPAND_WIDGET, 0);
  hbx_Inst.pack_start(ntbk_Ctl, Gtk::PACK_SHRINK, 5);

//=================================================================================================
  add(vbx_Main);
  vbx_Main.pack_start(*mbar_Main, Gtk::PACK_SHRINK, 0);
  vbx_Main.pack_start(*tbar_Main, Gtk::PACK_SHRINK, 0);
  vbx_Main.pack_start(hbx_Inst,   Gtk::PACK_EXPAND_WIDGET, 5);
  vbx_Main.pack_start(*stb_Main,  Gtk::PACK_SHRINK);


//=================================================================================================
  show_all();
  ntbk_Ctl.set_current_page(0);
  stb_Main->push("Startup Complete", 0);
  return;
  }
     WinMain::~WinMain() {
  fprintf(stdout, "I just got c++ destroyed\n"); fflush(stdout);
  }
void WinMain::BuildMenus(void) {
//=================================================================================================
  mbar_Main           = new Gtk::MenuBar();

  menu_MainFile       = new Gtk::Menu();
  menu_MainConfig     = new Gtk::Menu();
  menu_MainHelp       = new Gtk::Menu();

  mitm_MainFile       = new Gtk::MenuItem("_File",      true);
  mitm_MainFileOpen   = new Gtk::MenuItem("_Open",      true);
  mitm_MainFileQuit   = new Gtk::MenuItem("_Quit",      true);
  mitm_MainConfig     = new Gtk::MenuItem("_Configure", true);
  mitm_MainConfigCard = new Gtk::MenuItem("_Card",      true);
  mitm_MainHelp       = new Gtk::MenuItem("_Help",      true);
  mitm_MainHelpAbout  = new Gtk::MenuItem("_About",     true);

  mbar_Main->add(*mitm_MainFile);
  mbar_Main->add(*mitm_MainConfig);
  mbar_Main->add(*mitm_MainHelp);

  mitm_MainFile->set_submenu(*menu_MainFile);
  mitm_MainConfig->set_submenu(*menu_MainConfig);
  mitm_MainHelp->set_submenu(*menu_MainHelp);

  menu_MainFile->add(*mitm_MainFileOpen);
  menu_MainFile->add(*mitm_MainFileQuit);
  menu_MainHelp->add(*mitm_MainHelpAbout);

//=================================================================================================
  mitm_MainHelpAbout->signal_activate().connect(sigc::mem_fun(*this,&WinMain::OnHelpAbout));
  mitm_MainFileOpen->signal_activate().connect(sigc::mem_fun(*vcWaveFile,&CtlFile::OnFileOpen));
  mitm_MainFileQuit->signal_activate().connect(sigc::mem_fun(*this,&WinMain::OnQuit));

//=================================================================================================
  tbar_Main     = new Gtk::Toolbar();

  tbtn_Quit     = new Gtk::ToolButton();
  Gtk::Image *ww = new Gtk::Image(cp->pxbf_op_quit_bright);
  tbtn_Quit->set_icon_widget(*ww);
  tbar_Main->append(*tbtn_Quit, sigc::mem_fun(*this, &WinMain::OnQuit));

  tbtn_HelpAbout = new Gtk::ToolButton();
  Gtk::Image *wy = new Gtk::Image(cp->pxbf_op_helpAbout);
  tbtn_HelpAbout->set_icon_widget(*wy);
  tbar_Main->append(*tbtn_HelpAbout, sigc::mem_fun(*this, &WinMain::OnHelpAbout));


//=================================================================================================
  sbar_Main = new Gtk::Statusbar();
  return;
  }
// Event Handlers
void WinMain::on_hide() {
  Gtk::Window::on_hide(); // thus passing back up the food chain.
  return;
  }
void WinMain::OnHelpAbout(void) {
  //=================================================================================================
  WinAbout      *winAbout;
  winAbout = new WinAbout(cs, cp);
  winAbout->set_transient_for(*this);
  winAbout->run();
  delete winAbout;
  }
void WinMain::OnQuit(void) {
  hide();
  }

