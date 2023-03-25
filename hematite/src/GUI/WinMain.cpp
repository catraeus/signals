
// $Id: WinMain.cpp 757 2023-03-25 01:15:02Z duncang $

//=================================================================================================
// Original File Name : WinMain.cpp for hematite
// Original Author    : Catraeus & Duncan Gray
// Creation Date      : Jun 1, 2012
// Copyright          : Copyright © 2011-2019 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <vector>

#include <gtkmm/entry.h>
#include <gtkmm/notebook.h>

#include <caes/CaesString.hpp>

#include "WinMain.hpp"

class AnBulk;

      WinMain::WinMain             ( void ) {
  BuildEnv    ();
  BuildMenus  ();
  BuildDialogs();
  BuildMain   ();
  show_all_children();
  Connect();
  return;
  }
      WinMain::~WinMain            ( void ) {
  fprintf(stdout, "WinMain::~WinMain\n");
  }
void  WinMain::on_hide             ( void ) {
  fprintf(stdout, "WinMain hide event in progress\n");
  return;
  }
void  WinMain::OnFileSave          ( void ) {
  return;
}
void  WinMain::OnHelpAbout         ( void ) {
  char tStr[1024];
  sprintf(tStr, "About %s", ce->appName);
  Glib::ustring uu = ce->strAuthors;
  std::vector<Glib::ustring> tt(1);
  tt[0] = uu;
  Gtk::AboutDialog *theDialog = new Gtk::AboutDialog();
  theDialog->set_copyright(ce->strCopyright);
  theDialog->set_program_name(ce->appName);
  sprintf(tStr, "%d.%d build %d", ce->verMaj, ce->verMin, ce->buildNo);
  theDialog->set_version(tStr);
  theDialog->set_website_label("http://www.catraeus.com");
  theDialog->set_website("http://www.catraeus.com");
  theDialog->set_authors(tt);
  theDialog->set_logo(cp->pxbf_xLogoApp);
  theDialog->run();
  theDialog->hide();
  return;
  }
void  WinMain::OnQuit              ( void ) {
  hide();
  return;
  }



void  WinMain::BuildEnv            ( void ) {
  // - These signals have to be in place before the remainder of the working classes can function.
  sigRaw     = new Signal();
  sigNorm    = new Signal();
  sigCarr    = new Signal();
  sigBase    = new Signal();
  sigDemReIm = new Signal();
  sigDemAmPh = new Signal();

  anBulk     = new AnBulk (sigRaw, sigNorm                                          );
  anSine    = new AnSine (sigRaw, sigNorm, sigCarr, sigBase, sigDemReIm, sigDemAmPh);

  twi        = new WaveFiler(sigRaw);
  two        = new WaveFiler(sigDemReIm);

  ctMd       =     CtlMsgDspch  ::GetInstance();

  ce         =     CfgEnv       ::GetInstance();
  cs         =     CfgStrings   ::GetInstance();
  cp         =     CfgParticles ::GetInstance();

  mbarMain            = NULL;

  menuMainFile        = NULL;
  menuMainConfig      = NULL;
  menuMainHelp        = NULL;

  mitmMainFile        = NULL;
  mitmMainFileInSel   = NULL;
  mitmMainFileOutSave = NULL;
  mitmMainFileOutSel  = NULL;

  mitmMainFileQuit    = NULL;
  mitmMainConfig      = NULL;
  mitmMainHelp        = NULL;
  mitmMainHelpAbout   = NULL;
  tbarMain            = NULL;
  sbarMain            = NULL;
  return;
}
void  WinMain::BuildMenus          ( void ) {
//=================================================================================================
  mbarMain             = new Gtk::MenuBar();

  menuMainFile         = new Gtk::Menu();
  menuMainConfig       = new Gtk::Menu();
  menuMainHelp         = new Gtk::Menu();

  mitmMainFile         = new Gtk::MenuItem("_File",             true);
  mitmMainFileInSel    = new Gtk::MenuItem("Select _Input",     true);
  mitmMainFileOutSel   = new Gtk::MenuItem("Select _Output",    true);
  mitmMainFileOutSave  = new Gtk::MenuItem("_Save",             true);
  mitmMainFileQuit     = new Gtk::MenuItem("_Quit",      true);

  mitmMainConfig       = new Gtk::MenuItem("Confi_gure", true);
  mitmMainHelp         = new Gtk::MenuItem("_Help",      true);
  mitmMainHelpAbout    = new Gtk::MenuItem("_About",     true);

  mbarMain->add(*mitmMainFile);
  mbarMain->add(*mitmMainConfig);
  mbarMain->add(*mitmMainHelp);

  mitmMainFile->set_submenu(*menuMainFile);
  mitmMainConfig->set_submenu(*menuMainConfig);
  mitmMainHelp->set_submenu(*menuMainHelp);

  menuMainFile->add(*mitmMainFileInSel);
  menuMainFile->add(*mitmMainFileOutSel);
  menuMainFile->add(*mitmMainFileOutSave);
  menuMainFile->add(*mitmMainFileQuit);

  menuMainHelp->add(*mitmMainHelpAbout);

//=================================================================================================
  tbarMain         = new Gtk::Toolbar();

  tbtnAppQuit      = new Gtk::ToolButton();
  tbtnAppQuit->set_icon_name("application-exit");
  tbtnAppQuit->set_has_tooltip(true);
  tbtnAppQuit->set_tooltip_text(cs->strsAppExit);


  tbarMain     -> append( *tbtnAppQuit  );


//=================================================================================================
  sbarMain = new Gtk::Statusbar();

  lblSbarL.set_text("    Completion: Done    ");
  hbxSbarL.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  hbxSbarL.pack_start(lblSbarL);
  frmSbarL.add(hbxSbarL);

  lblSbarC.set_text("    Working: Idle    "    );
  hbxSbarC.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  hbxSbarC.pack_start(lblSbarC);
  frmSbarC.add(hbxSbarC);

  lblSbarR.set_text("    Errors: None    ");
  hbxSbarR.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  hbxSbarR.pack_start(lblSbarR);
  frmSbarR.add(hbxSbarR);

  sbarMain->set_homogeneous(false);
  //        pack_start(widget  , expand, fill, padding
  sbarMain->pack_start(frmSbarL, true,  false, 20);
  sbarMain->pack_start(frmSbarC, true,  false, 20);
  sbarMain->pack_start(frmSbarR, true,  false, 20);
  return;
  }
void  WinMain::BuildDialogs        ( void ) {
  return;
}
void  WinMain::BuildMain           ( void ) {
  char tStr[257];

  theFilePageRd        = new PageFileRd  ( this, sigRaw,                                            twi   );
  theAnPageBulk        = new PageAnBulk  (       sigRaw, sigNorm,                           anBulk        );
  theAnPageSine        = new PageAnSine  (       sigRaw, sigNorm, sigCarr, sigBase, sigDemReIm, anSine       );
  theFilePageWr        = new PageFileWr  ( this,                                    sigDemAmPh,         two   );
  HnCbReTitle          = new CbT<WinMain>;
  HnCbStatWork         = new CbT<WinMain>;
  HnCbStatCmpl         = new CbT<WinMain>;


  sprintf(tStr, "%s %d.%d build %d", ce->appName, ce->verMaj, ce->verMin, ce->buildNo);
  set_title(tStr);
  set_icon(cp->pxbf_xLogoApp);

  frmMain.set_shadow_type(Gtk::SHADOW_IN);

  //========================================================================
  hbxMainInner.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  hbxMainInner.pack_start(frmMain, Gtk::PACK_EXPAND_WIDGET, 3);
  ntbMain.set_border_width(10);
  ntbMain.append_page(*theFilePageRd,      "Input File");
  ntbMain.append_page(*theAnPageBulk,      "Bulk Analysis");
  ntbMain.append_page(*theAnPageSine,      "Sine Impairments");
  ntbMain.append_page(*theFilePageWr,      "Output File");
  frmMain.add(ntbMain);

  //========================================================================
  //========================================================================
  vbx_Main.set_orientation(Gtk::ORIENTATION_VERTICAL);
  vbx_Main.pack_start(*mbarMain,   Gtk::PACK_SHRINK);
  vbx_Main.pack_start(*tbarMain,    Gtk::PACK_SHRINK);
  vbx_Main.pack_start(hbxMainInner, Gtk::PACK_EXPAND_WIDGET, 3);
  vbx_Main.pack_start(*sbarMain,    Gtk::PACK_SHRINK);
  add(vbx_Main);

  set_default_size(800, 400);


  return;
}
void  WinMain::Connect             ( void ) {
//==  Menus  ======================================================================================
  mitmMainFileInSel                 -> signal_activate().connect(sigc::mem_fun(*theFilePageRd,  &PageFileRd::OnFileInSelect  ));
  mitmMainFileOutSel                -> signal_activate().connect(sigc::mem_fun(*theFilePageWr,  &PageFileWr::OnFileOutSelect ));
  mitmMainFileQuit                  -> signal_activate().connect(sigc::mem_fun(*this,           &WinMain ::OnQuit            ));

  tbtnAppQuit                       -> signal_clicked ().connect(sigc::mem_fun(*this,           &WinMain ::OnQuit            ));

  mitmMainHelpAbout                 -> signal_activate().connect(sigc::mem_fun(*this,           &WinMain ::OnHelpAbout       ));

  HnCbReTitle        ->SetCallback(this, &WinMain::HndlReTitle);
  ctMd               ->HCB_MainReTitle = HnCbReTitle;


  HnCbStatWork       ->SetCallback(this, &WinMain::HndlStatWork);
  ctMd               ->HCB_MainStWork = HnCbStatWork;

  HnCbStatCmpl       ->SetCallback(this, &WinMain::HndlStatCmpl);
  ctMd               ->HCB_MainStCmpl = HnCbStatCmpl;

  return;
}






bool  WinMain::HndlReTitle(void *d)  {
  char tStr[32768];

  fprintf(stderr, "WinMain::HndlReTitle()\n"); fflush(stderr);
  sprintf(tStr, "%s %d.%d build %d  --  %s", ce->appName, ce->verMaj, ce->verMin, ce->buildNo, ce->GetFileNameAbs());
  set_title(tStr);

  return true;
  }

bool  WinMain::HndlStatWork(void *d) {
  char   *ts;

  ts = (char *)d;
  char tStr[32768];
  sprintf(tStr, "    Working: %s    ", ts);
  lblSbarC.set_text(tStr);
  return true;
  }
bool  WinMain::HndlStatCmpl(void *d) {
  double tDoneNess;
  double *td;
  td = (double *)d;
  tDoneNess = (double) *td;
  tDoneNess *= 100.0;
  char tStr[32768];
  sprintf(tStr, "    Done: %4.1lf%%    ", tDoneNess);
  lblSbarL.set_text(tStr);
  return true;
  }

