
// $Id: WinMain.cpp 634 2022-11-19 22:52:03Z duncang $

//============================================================================
// Original File Name : WinMain.cpp for chert
// Original Author    : Catraeus & Duncan Gray
// Creation Date      : Jun 1, 2011
// Copyright          : Copyright © 2011-2019 Catraeus & Duncan Gray
//
// Description        :
//    The one and only
//
//============================================================================

#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <caes/CaesString.hpp>

#include "../_PrjGlbl.hpp"

#include "WinMain.hpp"

//  Creation Myths
      WinMain::WinMain         ( Signal *i_sig ) {
  BuildEnv   ( i_sig );
  BuildMenus (       );
  BuildMain  (       );
  Connect    (       );

  this   -> move     (10, 40);
  this   -> show_all (      );
  vwXprt -> show     (      );
}
      WinMain::~WinMain        ( void        ) {
}
//  GUI -- Operational
void  WinMain::OnQuit          ( void        ) {
  hide();
  return;
  }
void  WinMain::OnScopeButn     ( void        ) {
  shLOscope = true;
  if(tbtScope->get_active())    vwOsw->show_all();
  else                          vwOsw->hide();
  shLOscope = false;
  return;
  }
void  WinMain::OnSpecAnButn    ( void        ) {
  shLOspecan = true;
  if(tbtSpecAn->get_active())  vwSaw->show_all();
  else                         vwSaw->hide();
  shLOspecan = false;
  return;
  }
void  WinMain::OnHelpAbout     ( void        ) {
  char tStr[MAX_LINE_LEN];

  sprintf(tStr, "About %s", ce->appName);
  Glib::ustring uu = ce->strAuthors;
  std::vector<Glib::ustring> tt(1);
  tt[0] = uu;
  Gtk::AboutDialog *theDialog = new Gtk::AboutDialog();
  theDialog->set_transient_for(*this);
  theDialog->set_copyright(ce->strCopyright);
  theDialog->set_program_name(ce->appName);
  sprintf(tStr, "%d.%d build %d", ce->verMaj, ce->verMin, ce->buildNo);
  theDialog->set_version(tStr);
  theDialog->set_website_label(ce->strUrlLabel);
  theDialog->set_website(ce->strUrl);
  theDialog->set_authors(tt);
  theDialog->set_logo(cp->pxbf_logo_at);
  theDialog->run();
  theDialog->hide();

  return;
  }
bool  WinMain::OnOsWin         ( void *i_tt  ) {
  bool *pBB = (bool *)i_tt;
  if(!shLOscope)
    if(!(*pBB))
      tbtScope->set_active(false);
  return true;
  }
bool  WinMain::OnSaWin         ( void *i_tt  ) {
  bool *pBB = (bool *)i_tt;
  if(!shLOspecan)
    if(!(*pBB))
      tbtSpecAn->set_active(false);
  fflush(stdout);
  return true;
  }
//  GUI -- Setup
void  WinMain::BuildEnv        ( Signal *i_sig ) {
// Administrivia

// this GUI
  ce         = CfgEnv       ::GetInstance();
  cs         = CfgStrings   ::GetInstance();
  cp         = CfgParticles ::GetInstance();
  ctMd       = CtlMsgDspch  ::GetInstance();


  shLOscope  = false;
  shLOspecan = false;


  vwSaw    = new WinSa    ( i_sig      );
  vwOsw    = new WinOs    ( i_sig      );
  vwXprt   = new WinXport ( i_sig      );  vwXprt->set_keep_above(true);
  vwFile   = new FrmFile  ( this, i_sig);

  return;
}
void  WinMain::BuildMenus      ( void        ) {
//=================================================================================================
  mbar_Main           = new Gtk::MenuBar();

  menu_MainFile       = new Gtk::Menu();
  menu_MainHelp       = new Gtk::Menu();

  mitm_MainFile       = new Gtk::MenuItem("_File",      true);
  mitm_MainFileOpen   = new Gtk::MenuItem("_Open",      true);
  mitm_MainFileQuit   = new Gtk::MenuItem("_Quit",      true);
  mitm_MainHelp       = new Gtk::MenuItem("_Help",      true);
  mitm_MainHelpAbout  = new Gtk::MenuItem("_About",     true);

  mbar_Main->add(*mitm_MainFile);
  mbar_Main->add(*mitm_MainHelp);

  mitm_MainFile->set_submenu(*menu_MainFile);
  mitm_MainHelp->set_submenu(*menu_MainHelp);

  menu_MainFile->add(*mitm_MainFileOpen);
  menu_MainFile->add(*mitm_MainFileQuit);
  menu_MainHelp->add(*mitm_MainHelpAbout);

//=================================================================================================

//=================================================================================================
  tbar_Main     = new Gtk::Toolbar();

  tbtn_Quit     = new Gtk::ToolButton();
  Gtk::Image *ww = new Gtk::Image(cp->pxbf_op_quit_bright);
  tbtn_Quit->set_icon_widget(*ww);
  tbar_Main->append(*tbtn_Quit, sigc::mem_fun(*this, &WinMain::OnQuit));

  tbtn_HelpAbout = new Gtk::ToolButton();
  Gtk::Image *wy = new Gtk::Image(cp->pxbf_op_help_about);
  tbtn_HelpAbout->set_icon_widget(*wy);
  tbar_Main->append(*tbtn_HelpAbout, sigc::mem_fun(*this, &WinMain::OnHelpAbout));

  return;
}
void  WinMain::BuildMain       ( void        ) {
  char tStr[32768];

  sprintf(tStr, "%s %d.%d build %d", ce->appName, ce->verMaj, ce->verMin, ce->buildNo);
  set_title(tStr);

  set_icon(cp->pxbf_icon_catraeus);
//set_icon(cp->pxbf_logo_at);

  hbox_Main.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  vbxMainSub.set_orientation(Gtk::ORIENTATION_VERTICAL);
  vbxMainSub.pack_start(*vwFile, false, false, 3);

  hbox_Main.pack_start(vbxMainSub, false, false, 3);

  vbxAnaVis.set_orientation(Gtk::ORIENTATION_VERTICAL);

  tbtScope = new Gtk::ToggleButton("Scope");
  vbxAnaVis.pack_start(*tbtScope,  Gtk::PACK_SHRINK, 3);

  tbtSpecAn = new Gtk::ToggleButton("SpecAn");
  vbxAnaVis.pack_start(*tbtSpecAn,  Gtk::PACK_SHRINK, 3);


  hbox_Main.pack_start(vbxAnaVis, false, false, 3);

  vbxMainOuter.set_orientation(Gtk::ORIENTATION_VERTICAL);
  vbxMainOuter.pack_start(*mbar_Main, Gtk::PACK_SHRINK);
  vbxMainOuter.pack_start(*tbar_Main, Gtk::PACK_SHRINK);
  vbxMainOuter.pack_start(hbox_Main,  Gtk::PACK_EXPAND_WIDGET, 3);
  add(vbxMainOuter);

  return;
}
void  WinMain::Connect         ( void        ) {

// Interconnect - Foreign GUI
  MRU_OsWin = new CbT<WinMain>();
  MRU_OsWin->SetCallback(this, &WinMain::OnOsWin);
  vwOsw->MSU_OsWin = MRU_OsWin;

  MRU_SaWin = new CbT<WinMain>();
  MRU_SaWin->SetCallback(this, &WinMain::OnSaWin);
  vwSaw->MSU_SaWin  = MRU_SaWin;


// Interconnect - This' GUI
  mitm_MainHelpAbout ->signal_activate() .connect(sigc::mem_fun(*this,   &WinMain::OnHelpAbout  ));
  mitm_MainFileOpen  ->signal_activate() .connect(sigc::mem_fun(*vwFile, &FrmFile::OnFileOpen   ));
  mitm_MainFileQuit  ->signal_activate() .connect(sigc::mem_fun(*this,   &WinMain::OnQuit       ));
  tbtScope           ->signal_clicked()  .connect(sigc::mem_fun(*this,   &WinMain::OnScopeButn  ));
  tbtSpecAn          ->signal_clicked()  .connect(sigc::mem_fun(*this,   &WinMain::OnSpecAnButn ));
  return;
}
