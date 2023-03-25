
// $Id: FrmOsAxisH.hpp 308 2017-03-06 04:24:54Z duncang $

//=================================================================================================
// Original File Name : FrmOsAxisH.hpp
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
#ifndef __FRM_OS_AXIS_H_HPP_
#define __FRM_OS_AXIS_H_HPP_

#include <gtkmm.h>
#include "DrwOs.hpp"

class FrmOsAxisH: public Gtk::Frame {
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
                      FrmOsAxisH       ( DrwOs        *i_vwDs  );
    virtual          ~FrmOsAxisH       ( void        );
             void     OnSizeAlloc        ( void        );
  protected:
  private:
             void     BuildMain          ( void        );
  public:
  private:
             Gtk::Box      hbxAxisH;        // holds the layout and the filler box
             Gtk::Layout   hlyAxisH;        // contains labels
             Gtk::Label   *lblAxisH; // Are the labels

             DrwOs        *vwDs;
};

#endif // __FRM_OS_AXIS_H_HPP_
