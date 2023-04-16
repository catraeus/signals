
// $Id: FrmSaAxisH.hpp 487 2019-06-11 02:40:22Z duncang $

//=================================================================================================
// Original File Name : FrmSaAxisH.hpp
// Original Author    : duncang
// Creation Date      : 2017-03-05T16:12:03,646135358+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//    Oscilloscope Vertical Axis Labels
//
//=================================================================================================
/*


*/
#ifndef __FRM_SA_AXIS_H_HPP_
#define __FRM_SA_AXIS_H_HPP_

#include <gtkmm.h>
#include "DrwSa.hpp"
#include "../../Mdl/MdlSa.hpp"

class FrmSaAxisH: public Gtk::Frame {
private:
  enum eConst {
    EWOC_AX_H_Y          =   30,  // Horizontal Layout for axis markers vertical width.
    EWOC_AX_V_X          =   50,  // Vertical Axis horiz width, label and strip
    EWOC_AX_H_L          =   32,  // How many labels in the horiz dim.
    EWOC_AX_B_H          =   45
    };
  public:
    enum eSizes {
      EWOC_DS_B_H        =   EWOC_AX_B_H // drawScreen buffer to let axis lables be centered on graticule lines.
    };
  public:
                      FrmSaAxisH       ( DrwSa *i_vwDs, MdlSa *i_mdSa  );
    virtual          ~FrmSaAxisH       ( void   );
             void     OnSizeAlloc      ( void   );
  protected:
  private:
             void     BuildMain        ( void   );
  public:
  private:
             Gtk::Box      vbxAxisH;        // Packs the full-scalizer labels.
             Gtk::Box      hbxAxisH;        // holds the layout and the filler box
             Gtk::Layout   hlyAxisH;        // contains labels
             Gtk::Label   *lblAxisH;        // Are the labels, will be an array
             Gtk::Box      hbxFSZrH;        // The box to hold the full-scalizer labels.
             Gtk::Label    lblFSZsH;        // The start Label
             Gtk::Box      hbxFSZfill;      // Occupy the space between the start and stop labels.
             Gtk::Label    lblFSZpH;        // The stop  Label

   static const char      pmkuLblFP[];
   static const char      pmkuLblFS[];

   static const double    PXO_HL_Z;   // How far to move to the right for the first one
   static const double    PXO_HL_D;   // How far to separate each one

             DrwSa        *vwDs;
             MdlSa        *mdSa;
};

#endif // __FRM_SA_AXIS_H_HPP_
