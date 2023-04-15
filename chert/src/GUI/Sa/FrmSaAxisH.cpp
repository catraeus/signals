
// $Id: FrmSaAxisH.cpp 487 2019-06-11 02:40:22Z duncang $

//=================================================================================================
// Original File Name : FrmSaAxisH.cpp
// Original Author    : duncang
// Creation Date      : 2017-03-05T16:12:03,646135358+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//=================================================================================================


#include "FrmSaAxisH.hpp"

         FrmSaAxisH::FrmSaAxisH    ( DrwSa *i_vwDs, MdlSa *i_mdSa  ) {
  vwDs = i_vwDs;
  mdSa = i_mdSa;
  BuildMain();
}

         FrmSaAxisH::~FrmSaAxisH   ( void      ) {
}

void     FrmSaAxisH::BuildMain     ( void      ) {
  set_border_width(1);
  add(hbxAxisH);
  hbxAxisH.pack_start( hlyAxisH,        Gtk::PACK_SHRINK, 0);

  lblAxisH     = new Gtk::Label[EWOC_AX_H_L];

  for(uint ii = 0; ii<EWOC_AX_H_L; ii++) {
    char ss[32];
    sprintf(ss, "%d", ii);
    lblAxisH[ii] .set_text        (ss);
    lblAxisH[ii] .set_size_request(10,0);
    lblAxisH[ii] .set_justify     (Gtk::JUSTIFY_CENTER);
    hlyAxisH     .put             (lblAxisH[ii], ii*5,    10);
    }



  hlyAxisH   .set_size_request (-1, 40);

  return;
}
void     FrmSaAxisH::OnSizeAlloc   ( void      ) {
  //Really, this is just a gridscale-redraw function.
  char   ss[32];

  double vs;     // vertical size;
  double vd;     // vertical delta;

  double hfs;    // horizontal frequency span
  double hfz;    // horizontal frequency zero
  double hfd;    // horizontal frequency delta
  bool   isLogF; // Logarithmic in frequency

  double hs;     // horizontal size;
  double hd;     // horizontal delta;
  int    hi;     // horizontal integer immediate placement
  int    hn;     // horizontal number of grids

  vs  = (double)vwDs->get_allocated_height(); // FIXME only works because vbxAxisVert has the same top as vwDs
  vd  = vs / 10.5;  // FIXME because I say so. This will eventually become a constant somewhere in user or global settings
                    // This MAGICK 10.5 is trail and error to get them laid out at the right places compared to the
                    // SaDraw vertical lines that got drawn elsewhere

  hs  = (double)vwDs->get_allocated_width(); // FIXME only works because vbxAxisVert has the same top as vwDs
  hlyAxisH.set_size_request((int)(hs + EWOC_DS_B_H), 40);
  hd  = vd; // TODO Make everyone know that horizontal and vertical grid size will ALWAYS be equal.
  hn  = (int)floor(hs / vs * 10.0) + 1;// First try, let's see how many get made like this.
                                       // FIXME The grid back in the draw needs to be coordinated.

  hfz = mdSa->GetFmin();
  hfs = mdSa->GetFmax();

  if(hn > EWOC_AX_H_L) hn = EWOC_AX_H_L;
  hfd = (hfs - hfz) / (double)(hn - 1);
  for(int ii = 0; ii < hn; ii++) {
    hi = (int)((0.35 + 1.04*(double)ii) * hd);
    sprintf(ss, "%1.2lf", ((double)ii * hfd + hfz)/1000.0);
    lblAxisH[ii]  .set_text      (ss);
    hlyAxisH      .move          (lblAxisH[ii], hi,  10);
    lblAxisH[ii]  .set_visible   (true);
    }
  for(int ii = hn; ii < EWOC_AX_H_L; ii++) {
    lblAxisH[ii] .set_visible    (false);
    }

  return;
  }
