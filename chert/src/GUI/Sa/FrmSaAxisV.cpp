
// $Id: FrmSaAxisV.cpp 493 2019-06-17 23:33:10Z duncang $

//=================================================================================================
// Original File Name : FrmSaAxisV.cpp
// Original Author    : duncang
// Creation Date      : 2017-03-05T16:12:03,646135358+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//=================================================================================================


#include "FrmSaAxisV.hpp"

         FrmSaAxisV::FrmSaAxisV      ( DrwSa *i_vwDs  ) {
  vwDs = i_vwDs;
  mdSa = MdlSa      ::GetInstance();
  ctMd = CtlMsgDspch::GetInstance();
  BuildMain();
  Connect();
  OnRshAll(NULL);
}
         FrmSaAxisV::~FrmSaAxisV     ( void        ) {
}

void     FrmSaAxisV::BuildMain       ( void        ) {
  lblAxisV     = new Gtk::Label[EWOC_AX_V_L];

  this        ->set_border_width(1);
  this        ->set_orientation(Gtk::ORIENTATION_VERTICAL);

  hbxVfDvV     .set_size_request(-1, 50);
  frmAxisV     .set_size_request (EWOC_AX_V_X, -1);
  frmAxisV     .add( vlyAxisV);

  for(uint ii = 0; ii<EWOC_AX_V_L; ii++) {
    char ss[32];
    sprintf(ss, "%d", ii);
    lblAxisV[ii]  .set_text        (ss);
    lblAxisV[ii]  .set_size_request(EWOC_AX_V_X,-1);
    lblAxisV[ii]  .set_justify     (Gtk::JUSTIFY_RIGHT);
    vlyAxisV      .put             (lblAxisV[ii],      0, ii*4);
    }

  pack_start( frmAxisV, Gtk::PACK_SHRINK, 0);
  pack_start( hbxVfDvV, Gtk::PACK_SHRINK, 0);        // little square box below the asixV to keep the axesV calculations easier

  return;
}
void     FrmSaAxisV::Connect         ( void        ) {

                           MRU_RshAll = new CbT<FrmSaAxisV>();
                           MRU_RshAll->SetCallback(this, &FrmSaAxisV::OnRshAll);
  ctMd->MSU_SaVrtRshAxis = MRU_RshAll;
  return;
}
void     FrmSaAxisV::OnSizeAlloc     ( void        ) {
  OnRshAll(NULL);
  return;
  }

bool     FrmSaAxisV::OnRshAll        ( void *i_d   ) {
  //Really, this is just a gridscale-redraw function.
  char   ss[32];

  double pxSize; // vertical size;
  double pxDel;  // vertical delta;
  int    pxThis; // vertical integer immediate placement
  int    gridN;  // How many grids to mark
  double vStart; // The voltage at the top of the screen
  double vDel;   // how far to jump per grid
  double vThis;  // The one to print
  int    gridDex;

  // FIXME TOTALLY HACKED to make a dB screen look OK.
  fprintf(stderr, "VRSH\n"); fflush(stderr);
  pxSize  = (double)vwDs->get_allocated_height(); // WARNING only works because vbxAxisVert has the same top as drawScreen
  frmAxisV   .set_size_request (EWOC_AX_V_X, (int)pxSize + 2 * EWOC_DS_B_V);
  pxDel  = pxSize / 10.0;// FIXME because I say so. This will eventually become a constant somewhere in user or global settings
  gridN = 11;
  vStart = mdSa->GetVmax();
  vStart = 20.0 * log10(vStart);
  vDel   = (mdSa->GetVmin() - mdSa->GetVmax()) / 10.0;// FIXME because I say so. This will eventually become a constant somewhere in user or global settings
  vDel   = -20.0;
  for( gridDex = 0; gridDex < gridN; gridDex++) {
    pxThis = (int)((double)gridDex * pxDel);
    vThis = (double)gridDex * vDel + vStart;
    sprintf(ss, "%1.1lf", vThis);

    lblAxisV[gridDex] .set_text        (ss);
    vlyAxisV     .move            (lblAxisV[gridDex],     3, pxThis);
    lblAxisV[gridDex] .set_visible     (true);
    }
  for(  ; gridDex<EWOC_AX_V_L; gridDex++) {
    lblAxisV[gridDex] .set_visible     (false);
    }
  return false;
}
