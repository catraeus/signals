
// $Id: WinMain.cpp 572 2021-06-21 00:42:24Z duncang $

//=================================================================================================
// Original File Name : WinMain.cpp
// Original Author    : duncang
// Creation Date      : 2013-08-15
// Copyright          : Copyright © 2013 - 2020 by Catraeus and Duncan Gray
//
// Description        :
//
//=================================================================================================

#include "WinMain.hpp"


#include <vector>
#include <gtkmm.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

         WinMain::WinMain             ( Signal *i_sig )
: sig(i_sig) {
  BuildEnv  ();
  BuildMenus();
  BuildMain ();

  show_all_children();
  Connect();
  Setup();
  return;
}
         WinMain::~WinMain            ( void          ) {

}
void     WinMain::BuildEnv            ( void          ) {
  ce             = CfgEnv      ::GetInstance();
  cs             = CfgStrings  ::GetInstance();
  cp             = CfgParticles::GetInstance();
  ctWave         = CtlWave     ::GetInstance(sig);

  two            = new      WaveFiler     ( sig         );

  vwFile         = new      PageFileWr    ( this, sig, two   ); // do this first to get a Signal initialized.
  vwRemez        = new      PageRemez     (       sig   );
  frmForms       = new Gtk::Frame         (             );
  ntbk_Main      = new Gtk::Notebook      (             );
  stb_Main       = new Gtk::Statusbar     (             );
  holdOffSigSel = false;
  dummy  = 0;
  return;
}
void     WinMain::BuildMenus          ( void          ) {
  mbar_Main           = new Gtk::MenuBar();

  menu_MainFile       = new Gtk::Menu();
  menu_MainHelp       = new Gtk::Menu();

  mitm_MainFile       = new Gtk::MenuItem("_File",      true);
  mitm_MainFileQuit   = new Gtk::MenuItem("_Quit",      true);
  mitm_MainHelp       = new Gtk::MenuItem("_Help",      true);
  mitm_MainHelpAbout  = new Gtk::MenuItem("_About",     true);

  mbar_Main->add(*mitm_MainFile);
  mbar_Main->add(*mitm_MainHelp);

  mitm_MainFile->set_submenu(*menu_MainFile);
  mitm_MainHelp->set_submenu(*menu_MainHelp);

  menu_MainFile->add(*mitm_MainFileQuit);
  menu_MainHelp->add(*mitm_MainHelpAbout);

  return;
}
void     WinMain::BuildMain           ( void          ) {
  char tStr[1024];
  char nStr[1024];
  sprintf(tStr, "%s   ", ce->appName);
  strcat (tStr, "-");
  sprintf(nStr, "%s %s   ", tStr, ce->appDesc);
  strcat (nStr, "-");
  sprintf(tStr, "%s version %d.%d build %d\n", nStr, ce->verMaj, ce->verMin, ce->buildNo);
  set_icon(cp->pxbf_logo_at);
  set_title(nStr);

  //== Setup particulars of each widget
  //== Toolbar
  tbarMain     = new Gtk::Toolbar();
  tbtnQuit     = new Gtk::ToolButton(Gtk::Stock::QUIT);
  tbtnFileSave = new Gtk::ToolButton(Gtk::Stock::SAVE);

  tbarMain            ->append      ( *tbtnQuit      );
  tbarMain            ->append      ( *tbtnFileSave  );


  vbxWhole        .set_orientation   (  Gtk::ORIENTATION_VERTICAL        );

  hbx_FillTop     .set_orientation   (  Gtk::ORIENTATION_HORIZONTAL      );
  hbx_FillTop     .set_size_request  ( -1,    20                         );

  hbxFormWrap     .set_orientation   (  Gtk::ORIENTATION_HORIZONTAL      );

  hbx_FillBot     .set_orientation   (  Gtk::ORIENTATION_HORIZONTAL      );
  hbx_FillBot     .set_size_request  ( -1,    20                         );

  sep_StatBar     .set_orientation   (  Gtk::ORIENTATION_HORIZONTAL      );

  stb_Main       ->set_border_width  (  1                                );
  stb_Main       ->push              ( "Put something sensible here"     );

  vbx_FillLeft    .set_orientation   (  Gtk::ORIENTATION_VERTICAL        );
  vbx_FillLeft    .set_size_request  ( 20,   -1                          );
  vbx_FillRight   .set_orientation   (  Gtk::ORIENTATION_VERTICAL        );
  vbx_FillRight   .set_size_request  ( 20,   -1                          );

  vbx_Holder      .set_orientation   (  Gtk::ORIENTATION_VERTICAL        );
  hbxForms        .set_orientation   (  Gtk::ORIENTATION_HORIZONTAL      );

  frmForms        ->set_label        ( "Remez Filter Function Generator" );
  frmForms        ->set_size_request (  600, 400                         );





  //== Pack and Add widgets in the right order




  add(vbxWhole);
    vbxWhole                   .pack_start       ( *mbar_Main,        Gtk::PACK_SHRINK,        0 );
    vbxWhole                   .pack_start       ( *tbarMain,         Gtk::PACK_SHRINK,        0 );
    vbxWhole                   .pack_start       (  hbx_FillTop,      Gtk::PACK_SHRINK,        0 ); // the bigger border blank space
    vbxWhole                   .pack_start       (  hbxFormWrap,      Gtk::PACK_SHRINK,        0 );
      hbxFormWrap              .pack_start       (  vbx_FillLeft,     Gtk::PACK_SHRINK,        0 ); // the bigger border blank space
      hbxFormWrap              .pack_start       ( *frmForms,         Gtk::PACK_SHRINK,        0 );
        frmForms              ->add              (  hbxForms                                     );
          hbxForms             .pack_start       (  vbx_Holder,       Gtk::PACK_SHRINK,        5 );
            vbx_Holder         .pack_start       ( *ntbk_Main,        Gtk::PACK_SHRINK,        5 );
              ntbk_Main       ->append_page      ( *vwFile,         " File Control "             );
              ntbk_Main       ->append_page      ( *vwRemez,        " Remez "                    );
      hbxFormWrap              .pack_start       (  vbx_FillRight,    Gtk::PACK_SHRINK,        0 ); // the bigger border blank space
    vbxWhole                   .pack_start       (  hbx_FillBot,      Gtk::PACK_SHRINK,        0 ); // the bigger border blank space
    vbxWhole                   .pack_start       (  sep_StatBar,      Gtk::PACK_SHRINK,        0 );
    vbxWhole                   .pack_start       ( *stb_Main,         Gtk::PACK_SHRINK,        0 );

  return;
}
void     WinMain::Connect             ( void          ) {

  mitm_MainHelpAbout ->signal_activate ().connect(sigc::mem_fun(*this,   &WinMain   ::OnHelpAbout        ));
  mitm_MainFileQuit  ->signal_activate ().connect(sigc::mem_fun(*this,   &WinMain   ::OnQuit             ));

  tbtnQuit           ->signal_clicked  ().connect(sigc::mem_fun(*this,   &WinMain   ::OnQuit             ));
  tbtnFileSave       ->signal_clicked  ().connect(sigc::mem_fun(*vwFile, &PageFileWr::OnFileWrite        ));

  return;
}
void     WinMain::Setup               ( void          ) {
  return;
}
// Event Handlers
void     WinMain::on_hide             ( void          ) {
  Gtk::Window::on_hide(); // thus passing back up the food chain.
  return;
  }



void     WinMain::OnHelpAbout         ( void          ) {
  char tStr[MAX_LINE_LEN];

  sprintf(tStr, "About %s", ce->appName);
  std::vector<Glib::ustring> tt;
  tt.push_back(ce->strAuthors);
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
void     WinMain::OnQuit              ( void          ) {
  hide();
  }

