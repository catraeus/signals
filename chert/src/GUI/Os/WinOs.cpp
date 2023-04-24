// $Id: WinOs.cpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : OScope.cpp
// Original Author    : duncang
// Creation Date      : Oct 14, 2012
// Copyright          : Copyright © 2012 - 2017 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include <string.h>

#include <caes/CaesTypes.hpp>
#include <caes/CaesString.hpp>

#include "WinOs.hpp"

       WinOs:: WinOs                  ( Signal *i_sig )
: mdOs(NULL) {
  BuildEnv   (i_sig);
  BuildSubs  (i_sig);
  BuildMain  ();
  Connect    ();
}
       WinOs::~WinOs                  ( void         ) {
}

void   WinOs::BuildEnv                ( Signal *i_sig ) {
  cp        = CfgParticles ::GetInstance();
  ce        = CfgEnv       ::GetInstance();
  mdOs      = MdlOs        ::GetInstance(i_sig);
  ctMd      = CtlMsgDspch  ::GetInstance();
  return;
}
void   WinOs::BuildSubs               ( Signal *i_sig ) {
  vwDrwOs     = new      DrwOs      ( i_sig   );
  frmAxisH    = new      FrmOsAxisH ( vwDrwOs );  // a whole class of its own since it has lots of function as we rescale etc.
  frmAxisV    = new      FrmOsAxisV ( vwDrwOs, i_sig );  // a whole class of its own since it has lots of function as we rescale etc.
  vwOsHor     = new      FrmOsHor   ( this, i_sig    );
  vwOsv       = new      FrmOsVrt   ( this, i_sig    );
  nbkControls = new Gtk::Notebook   (         );
  stbMain     = new Gtk::Statusbar  (         );
  return;
  }
void   WinOs::BuildMain               ( void         ) {
  ReTitle                           (                                 );
  this          ->set_icon          ( cp->pxbf_logo_at                );

  frmMain        .set_border_width  (                              1  );

  vbxMain        .set_orientation   ( Gtk::ORIENTATION_VERTICAL       );
  hbxMain        .set_orientation   ( Gtk::ORIENTATION_HORIZONTAL     );
  vbxScrs        .set_orientation   ( Gtk::ORIENTATION_VERTICAL       );
  hbxScrs        .set_orientation   ( Gtk::ORIENTATION_HORIZONTAL     );

  hbxBfDdTop     .set_size_request  (-1, FrmOsAxisV::EWOC_DS_B_V      );
  hbxBfDdBot     .set_size_request  (-1, FrmOsAxisV::EWOC_DS_B_V      );

  hbxVwDs        .set_orientation   ( Gtk::ORIENTATION_HORIZONTAL     );
  hbxBfDdLeft    .set_size_request  (    FrmOsAxisH::EWOC_DS_B_H, -1  );
  hbxBfDdRite    .set_size_request  (    FrmOsAxisH::EWOC_DS_B_H, -1  );

  hbxWinCtlHoriz  .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL     );
  hbxWinCtlVert   .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL     );

  frmStbMain      .set_border_width (                              3  );
  stbMain        ->set_border_width (                              2  );
  stbMain        ->push             ( "hello status bar world"        );


//=========================  Final Packaging  =========================================================

  frmMain       .set_border_width(1);
  this                      ->add         (  frmMain);
    frmMain                  .add         (  vbxMain                                        );
      vbxMain                .pack_start  (  hbxMain,         Gtk::PACK_SHRINK,           3 );
        hbxMain              .pack_start  (  hbxScrs,         Gtk::PACK_SHRINK,           3 );
          hbxScrs            .pack_start  ( *frmAxisV,        Gtk::PACK_SHRINK,           0 ); // eol
          hbxScrs            .pack_start  (  vbxScrs,         Gtk::PACK_SHRINK,           0 );
            vbxScrs          .pack_start  (  hbxBfDdTop,      Gtk::PACK_SHRINK,           0 ); // eol
            vbxScrs          .pack_start  (  hbxVwDs,         Gtk::PACK_SHRINK,           0 );
              hbxVwDs        .pack_start  (  hbxBfDdLeft,     Gtk::PACK_SHRINK,           0 ); // eol
              hbxVwDs        .pack_start  ( *vwDrwOs,         Gtk::PACK_SHRINK,           0 ); // eol
              hbxVwDs        .pack_start  (  hbxBfDdRite,     Gtk::PACK_SHRINK,           0 ); // eol
            vbxScrs          .pack_start  (  hbxBfDdBot,      Gtk::PACK_SHRINK,           0 ); // eol
            vbxScrs          .pack_start  ( *frmAxisH,        Gtk::PACK_SHRINK,           0 ); // eol
        hbxMain              .pack_start  ( *nbkControls,     Gtk::PACK_SHRINK,           0 );
          nbkControls       ->append_page (  hbxWinCtlHoriz," Horiz "                       );
            hbxWinCtlHoriz   .pack_start  ( *vwOsHor,         Gtk::PACK_SHRINK,           3 ); // eol
          nbkControls       ->append_page (  hbxWinCtlVert, " Vert "                        );
            hbxWinCtlVert    .pack_start  ( *vwOsv,           Gtk::PACK_SHRINK,           3 ); // eol
      vbxMain                .pack_start  (  frmStbMain,      Gtk::PACK_SHRINK,           0 );
        frmStbMain           .add         ( *stbMain                                        );
  return;
  }
void   WinOs::ReTitle                 ( void         ) {
  char tStr[32768];
  strcpy(tStr, "Oscilloscope : ");
  strcat(tStr, ce->GetFileNameAbs());
  set_title(tStr);
  return;
}

void   WinOs::Connect                 ( void         ) {
  MSU_OsWin         = NULL;

  add_events( Gdk::ENTER_NOTIFY_MASK        );
  add_events( Gdk::POINTER_MOTION_MASK      );
  add_events( Gdk::POINTER_MOTION_HINT_MASK );
  add_events( Gdk::KEY_PRESS_MASK           );
  add_events( Gdk::KEY_RELEASE_MASK         );
  add_events( Gdk::BUTTON_PRESS_MASK        );
  add_events( Gdk::BUTTON_RELEASE_MASK      );

  return;
}


void   WinOs::on_hide                 ( void         ) {
  bool b = false;
  if(MSU_OsWin != 0)    MSU_OsWin->Execute(&b);
  Window::on_hide();
  return;
  }
void   WinOs::on_show                 ( void         ) {
  bool b = true;
  if(MSU_OsWin != 0)    MSU_OsWin->Execute(&b);
  Gtk::Window::on_show();
  return;
  }
void   WinOs::on_size_allocate        ( Gtk::Allocation& i_allocation) {
  //Really, this is just a gridscale-redraw function.
  frmAxisV->OnSizeAlloc();
  frmAxisH->OnSizeAlloc();
  ullong l;
  l = 0;
  if(mdOs != NULL) l = mdOs->GetTPvScr();
  char cmsg[32768];
  sprintf(cmsg, "width: %lld", l);
  stbMain->pop();
  stbMain->push(cmsg);
  Gtk::Window::on_size_allocate(i_allocation);
  return;
  }







