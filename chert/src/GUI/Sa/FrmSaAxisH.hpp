
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
  public:
    enum eSizes {
      EWOC_DS_B_H          =   25 // drawScreen buffer to let axis lables be centered on graticule lines.
    };
  private:
    enum eConst {
      EWOC_AX_V_X          =   50, // Vertical Axis horiz width, label and strip
      EWOC_AX_H_L          =   32  // How many labels in the horiz dim.
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
             Gtk::Box      hbxAxisH;        // holds the layout and the filler box
             Gtk::Layout   hlyAxisH;        // contains labels
             Gtk::Label   *lblAxisH;        // Are the labels, will be an array

             DrwSa        *vwDs;
             MdlSa        *mdSa;
};

#endif // __FRM_SA_AXIS_H_HPP_
