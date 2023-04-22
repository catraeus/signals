
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
#include <caes/CaesString.hpp>

const char   FrmSaAxisH::pmkuLblFP[] = "<span font=\"serif\">";
const char   FrmSaAxisH::pmkuLblFS[] = "</span>";
const double FrmSaAxisH::PXO_HL_Z    =  0.850;
const double FrmSaAxisH::PXO_HL_D    =  1.051;

         FrmSaAxisH::FrmSaAxisH    ( DrwSa *i_vwDs, MdlSa *i_mdSa  ) {
  vwDs = i_vwDs;
  mdSa = i_mdSa;
  BuildMain();
}

         FrmSaAxisH::~FrmSaAxisH   ( void      ) {
}

void     FrmSaAxisH::BuildMain     ( void      ) {
  char markup[256];
  char ss[128];

  //====  Make Stuff

  set_border_width(1);

  vbxAxisH   .set_orientation     (Gtk::ORIENTATION_VERTICAL  );
  hbxAxisH   .set_orientation     (Gtk::ORIENTATION_HORIZONTAL);

  hlyAxisH   .set_size_request    (800, EWOC_AX_H_Y);

  strcpy(markup, pmkuLblFP);
  strcat(markup, "45");
  strcat(markup, pmkuLblFS);
  lblAxisH     = new Gtk::Label[EWOC_AX_H_L];
  for(uint ii = 0; ii<EWOC_AX_H_L; ii++) {
    sprintf(ss, "%d", ii);
    lblAxisH[ii] .set_size_request (15,0);
    lblAxisH[ii] .set_use_markup   (true);
    lblAxisH[ii] .set_markup       (markup);
    lblAxisH[ii] .set_justify      (Gtk::JUSTIFY_CENTER);
  }




  hbxFSZrH   .set_orientation     (Gtk::ORIENTATION_HORIZONTAL);

  EngString(ss,     0.0, 1, (char *)"Hz");
  sprintf(markup, "%s%s%s", pmkuLblFP, ss, pmkuLblFS);
  lblFSZsH   .set_use_markup   (true);
  lblFSZsH   .set_markup       (markup);

  hbxFSZfill .set_orientation     (Gtk::ORIENTATION_HORIZONTAL); // Not that this one matters

  EngString(ss, 24000.0, 1, (char *)"Hz");
  sprintf(markup, "%s%s%s", pmkuLblFP, ss, pmkuLblFS);
  lblFSZpH   .set_use_markup   (true);
  lblFSZpH   .set_markup       (markup);


  //====  Place Stuff

                   add        ( vbxAxisH                                   );
  vbxAxisH        .pack_start ( hbxAxisH,      Gtk::PACK_SHRINK,         0 );
    hbxAxisH      .pack_start ( hlyAxisH,      Gtk::PACK_EXPAND_WIDGET,  0 );
    for(uint ii = 0; ii<EWOC_AX_H_L; ii++)
      hlyAxisH    .put        ( lblAxisH[ii],    ii*5,       10            );  // bogus placement for now
  vbxAxisH        .pack_start ( hbxFSZrH,      Gtk::PACK_SHRINK,         0 );
  hbxFSZrH        .pack_start ( lblFSZsH,      Gtk::PACK_SHRINK,         0 );
  hbxFSZrH        .pack_start ( hbxFSZfill,    Gtk::PACK_EXPAND_WIDGET,  0 );
  hbxFSZrH        .pack_start ( lblFSZpH,      Gtk::PACK_SHRINK,         0 );

  return;
}
void     FrmSaAxisH::OnSizeAlloc   ( void      ) {
  //Really, this is just a gridscale-redraw function.
  char   ss[128];
  char   markup[256];

  ss[0]     = 0;
  markup[0] = 0;

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

  hs     = (double)vwDs->get_allocated_width(); // FIXME only works because vbxAxisVert has the same top as vwDs
  hlyAxisH.set_size_request((int)(hs + EWOC_AX_B_H), EWOC_AX_H_Y);
  hd     = vd; // TODO Make everyone know that horizontal and vertical grid size will ALWAYS be equal.
  hn     = (int)floor(hs / vs * 10.0) + 1;// First try, let's see how many get made like this.
                                       // FIXME The grid back in the draw needs to be coordinated.

  hfz    = mdSa->GetFmin();
  hfs    = mdSa->GetFmax();
  isLogF = mdSa->IsLogF();

  double nG;
  double fG;
  double tT;
  double tGn;
  fG  = Gridder125(hfs - hfz, 36, false);
  nG  = fG * 1.000000000000001;
  tGn = log10(nG) - floor(log10(nG));
  tGn = floor(pow(10, tGn));
  if(tGn == 5.0)
    nG *= 2.0 / 5.0;
  else if(tGn == 2.0)
    nG *= 0.5;
  else
    nG *= 0.5;
  tT  = (hfs - hfz) / nG / 10.0;

  EngString(ss, hfz, 3, (char *)"Hz");
  sprintf(markup, "%s%s%s", pmkuLblFP, ss, pmkuLblFS);
  lblFSZsH   .set_markup       (markup);

  EngString(ss, hfs, 3, (char *)"Hz");
  sprintf(markup, "%s%s%s", pmkuLblFP, ss, pmkuLblFS);
  lblFSZpH   .set_markup       (markup);


  if(hn > EWOC_AX_H_L) hn = EWOC_AX_H_L;
  if(isLogF) {
  }
  else {
    hfd = (hfs - hfz) / (double)(hn - 1);
    for(int ii = 0; ii < hn; ii++) {
      double tnm;
      hi = (int)((PXO_HL_Z + PXO_HL_D*(double)ii) * hd);
      tnm = ((double)ii * hfd + hfz)/1000.0;
      sprintf(ss, "%s%1.1lf%s", pmkuLblFP, tnm, pmkuLblFS);
      lblAxisH[ii]  .set_markup    (ss);
      hlyAxisH      .move          (lblAxisH[ii], hi,  10);
      lblAxisH[ii]  .set_visible   (true);
    }
    for(int ii = hn; ii < EWOC_AX_H_L; ii++) {
      lblAxisH[ii] .set_visible    (false);
    }
  }
  return;
  }
