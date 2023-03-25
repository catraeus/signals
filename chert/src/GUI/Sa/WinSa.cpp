// $Id: WinSa.cpp 497 2019-08-17 20:46:44Z duncang $

//=================================================================================================
// Original File Name : WinSa.cpp
// Original Author    : duncang
// Creation Date      : Oct 14, 2012
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include "WinSa.hpp"




       WinSa::WinSa              ( Signal *i_sig )
: mdSa(NULL) {
  BuildEnv  ();
  BuildSubs (i_sig);
  BuildMain ();
  Connect   ();
  }
       WinSa::~WinSa             ( void         ) {
  }

void   WinSa::BuildEnv           ( void         ) {
  ce               = CfgEnv       :: GetInstance();
  cs               = CfgStrings   :: GetInstance();
  cp               = CfgParticles :: GetInstance();
  mdSa             = MdlSa        :: GetInstance();
  ctMd             = CtlMsgDspch  :: GetInstance();
  return;
}
void   WinSa::BuildSubs          ( Signal *i_sig ) {
  vwDrwSa     = new      DrwSa      ( i_sig   );
  frmAxisH    = new      FrmSaAxisH ( vwDrwSa );  // a whole class of its own since it has lots of function as we rescale etc.
  frmAxisV    = new      FrmSaAxisV ( vwDrwSa );  // a whole class of its own since it has lots of function as we rescale etc.
  vwSaMode    = new      FrmSaMode  ( i_sig   );
  vwSaHor     = new      FrmSaHor   ( i_sig   );
  vwSaVrt     = new      FrmSaVrt   ( i_sig   );
  vwSaApod    = new      FrmSaAp    (         );
  nbkControls = new Gtk::Notebook   (         );
  stbMain     = new Gtk::Statusbar  (         );
  return;
}
void   WinSa::BuildMain          ( void         ) {
  ReTitle                           (                                 );
  this          ->set_icon          ( cp->pxbf_logo_at                );

  frmMain        .set_border_width  (                              1  );

  vbxMain        .set_orientation   ( Gtk::ORIENTATION_VERTICAL       );
  hbxMain        .set_orientation   ( Gtk::ORIENTATION_HORIZONTAL     );
  vbxScrs        .set_orientation   ( Gtk::ORIENTATION_VERTICAL       );
  hbxScrs        .set_orientation   ( Gtk::ORIENTATION_HORIZONTAL     );

  hbxBfDdTop      .set_size_request (-1, FrmSaAxisV::EWOC_DS_B_V      );
  hbxBfDdBot      .set_size_request (-1, FrmSaAxisV::EWOC_DS_B_V      );

  hbxVwDs         .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL     );
  hbxBfDdLeft     .set_size_request (    FrmSaAxisH::EWOC_DS_B_H, -1  );
  hbxBfDdRite     .set_size_request (    FrmSaAxisH::EWOC_DS_B_H, -1  );

  vbxMode        .set_orientation   ( Gtk::ORIENTATION_VERTICAL);
  vbxMode        .set_size_request  (                       200,   0  );
  vbxModeFill    .set_orientation   ( Gtk::ORIENTATION_VERTICAL       );

  vbxCtlHoriz    .set_orientation   ( Gtk::ORIENTATION_VERTICAL       );
  vbxCtlHoriz    .set_size_request  (                       200,   0  );
  vbxHorFill     .set_orientation   ( Gtk::ORIENTATION_VERTICAL       );

  vbxCtlVert     .set_orientation   ( Gtk::ORIENTATION_VERTICAL       );
  vbxCtlVert     .set_size_request  (                       200,   0  );
  vbxApFill      .set_orientation   ( Gtk::ORIENTATION_VERTICAL       );
  vbxVrtFill     .set_orientation   ( Gtk::ORIENTATION_VERTICAL       );

  vbxCtlApod     .set_orientation   ( Gtk::ORIENTATION_VERTICAL       );
  vbxCtlApod     .set_size_request  (                       200,   0  );


  frmStbMain    .set_border_width   (                              3  );
  stbMain      ->set_border_width   (                              2  );
  stbMain      ->push               ( "Dummy Message"                 );

  this                      ->add         (  frmMain                                             );
    frmMain                  .add         (  vbxMain                                             );
      vbxMain                .pack_start  (  hbxMain,         Gtk::PACK_SHRINK,                3 );
        hbxMain              .pack_start  (  hbxScrs,         Gtk::PACK_SHRINK,                3 );
          hbxScrs            .pack_start  ( *frmAxisV,        Gtk::PACK_SHRINK,                0 ); // eol
          hbxScrs            .pack_start  (  vbxScrs,         Gtk::PACK_SHRINK,                3 );
            vbxScrs          .pack_start  (  hbxBfDdTop,      Gtk::PACK_SHRINK,                0 ); // eol
            vbxScrs          .pack_start  (  hbxVwDs,         Gtk::PACK_SHRINK,                3 );
              hbxVwDs        .pack_start  (  hbxBfDdLeft,     Gtk::PACK_SHRINK,                0 ); // eol
              hbxVwDs        .pack_start  ( *vwDrwSa,         Gtk::PACK_SHRINK,                0 ); // eol
              hbxVwDs        .pack_start  (  hbxBfDdRite,     Gtk::PACK_SHRINK,                0 ); // eol
            vbxScrs          .pack_start  (  hbxBfDdBot,      Gtk::PACK_SHRINK,                0 ); // eol
            vbxScrs          .pack_start  ( *frmAxisH,        Gtk::PACK_SHRINK,                0 );
        hbxMain              .pack_start  ( *nbkControls,     Gtk::PACK_SHRINK,                0 );
          nbkControls       ->append_page (  vbxMode,       " Mode "                             );
            vbxMode          .pack_start  ( *vwSaMode,        Gtk::PACK_SHRINK,                2 );
            vbxMode          .pack_start  (  vbxModeFill,     Gtk::PACK_EXPAND_WIDGET,         2 );
          nbkControls       ->append_page (  vbxCtlHoriz,   " Horiz "                            );
            vbxCtlHoriz      .pack_start  ( *vwSaHor,         Gtk::PACK_SHRINK,                2 );
            vbxCtlHoriz      .pack_start  (  vbxHorFill,      Gtk::PACK_EXPAND_WIDGET,         2 );
          nbkControls       ->append_page (  vbxCtlVert,    " Vert "                             );
            vbxCtlVert       .pack_start  (  vbxApFill,       Gtk::PACK_EXPAND_WIDGET,         2 );
            vbxCtlVert       .pack_start  ( *vwSaVrt,         Gtk::PACK_SHRINK,                2 );
            vbxCtlVert       .pack_start  (  vbxVrtFill,      Gtk::PACK_EXPAND_WIDGET,         2 );
          nbkControls       ->append_page (  vbxCtlApod,    " Apodization "                      );
            vbxCtlApod       .pack_start  ( *vwSaApod,        Gtk::PACK_SHRINK,                2 );
      vbxMain                .pack_start  (  frmStbMain,      Gtk::PACK_SHRINK,           0 );
        frmStbMain           .add         ( *stbMain                                        );

  return;
  }
void   WinSa::ReTitle            ( void         ) {
  char tStr[32768];
  strcpy(tStr, "Spec An : ");
  strcat(tStr, ce->GetFileNameAbs());
  set_title(tStr);
  return;
}

void  WinSa::Connect             ( void         ) {
  MSU_SaWin          = NULL;

  add_events( Gdk::ENTER_NOTIFY_MASK        );
  add_events( Gdk::POINTER_MOTION_MASK      );
  add_events( Gdk::POINTER_MOTION_HINT_MASK );
  add_events( Gdk::KEY_PRESS_MASK           );
  add_events( Gdk::KEY_RELEASE_MASK         );
  add_events( Gdk::BUTTON_PRESS_MASK        );
  add_events( Gdk::BUTTON_RELEASE_MASK      );

  CbSaReSkin         = new CbT<WinSa>();
  CbSaReSkin->SetCallback (this, &WinSa::OnReSkin);
//ctMd->MRD_SaReSkin = CbSaReSkin;

  CbOnReSize        = new CbT<WinSa>();
  CbOnReSize->SetCallback(this, &WinSa::OnReSize);
  vwDrwSa->MSU_SaReSize = CbOnReSize;

  MRU_SaStatMsg     = new CbT<WinSa>();
  MRU_SaStatMsg->SetCallback(this, &WinSa::OnSaStatMsg);
  ctMd->MSU_SaStatMsg = MRU_SaStatMsg;

  vwSaHor->SetDrwSa(vwDrwSa);
  return;
}

bool  WinSa::OnReSize            ( void   *i_N  ) {
  ullong ll;
  ullong bb;
  ullong tt;
  char   cmsg[256];
  ll = (ullong)(*((double *)i_N));

  bb = mdSa->GetFrqVana();
  tt = mdSa->GetSmpVana();
  sprintf(cmsg, "SA width: %lld      bins: %lld     samples: %lld", ll, bb, tt);
  stbMain->pop();
  stbMain->push(cmsg);
  return true;
  }
bool  WinSa::OnReSkin            ( void   *i_d  ) {
  int i;

  i = *((int *)i_d);
  fprintf(stdout, "WinSa::OnReSkin(%d)\n", i);
  fflush(stdout);
  return true;
  }

void  WinSa::on_hide             ( void         ) {
  bool b = false;
  if(MSU_SaWin != NULL)
    MSU_SaWin->Execute(&b);
  Window::on_hide();
  return;
  }
void  WinSa::on_show             ( void         ) {
  bool b = true;
  if(MSU_SaWin != 0)    MSU_SaWin->Execute(&b);
  Gtk::Window::on_show();
  return;
  }
void  WinSa::on_size_allocate    ( Gtk::Allocation& i_allocation) {
  //Really, this is just a gridscale-redraw function.
  frmAxisV->OnSizeAlloc();
  frmAxisH->OnSizeAlloc();
  ullong l;
  l = 0;
  if(mdSa != NULL) l = mdSa->GetPxlVscrX();
  char cmsg[32768];
  sprintf(cmsg, "width: %lld", l);
  stbMain->pop();
  stbMain->push(cmsg);
  ctMd->MRD_SaHorNumerics();
  Gtk::Window::on_size_allocate(i_allocation);
  return;
  }
bool  WinSa::OnSaStatMsg         ( void   *i_s  ) {
  char *s;
  s = (char *)i_s;
  stbMain->pop();
  stbMain->push(s);
  return false;
}
