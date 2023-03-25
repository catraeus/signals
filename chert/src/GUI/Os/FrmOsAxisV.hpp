
// $Id: FrmOsAxisV.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : FrmOsAxisV.hpp
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
#ifndef __FRM_OS_AXIS_V_HPP_
#define __FRM_OS_AXIS_V_HPP_

#include <gtkmm.h>

#include <caes/CaesCallBack.hpp>
#include <caes/AudioFile/Signal.hpp>


#include "DrwOs.hpp"
#include "../../Mdl/MdlOs.hpp"
#include "../../Ctl/CtlMsgDspch.hpp"

class FrmOsAxisV: public Gtk::Box {
  private:
    enum eConst {
      EWOC_AX_V_X          =   50, // Vertical Axis horiz width, label and strip
      EWOC_AX_V_L          =   32  // How many labels in the vert dim.
    };
  public:
    enum eSizes {
      EWOC_DS_B_V          =    7 // vwDs buffer to let axis lables be centered on graticule lines.
    };
  public:
                      FrmOsAxisV         ( DrwOs *i_vwDs, Signal *i_sig  );
    virtual          ~FrmOsAxisV         ( void           );
             void     OnSizeAlloc        ( void           );
  protected:
  private:
             void     BuildMain          ( void           );
             void     Connect            ( void           );

             bool     OnRshAll           ( void *i_d      );

  public:
  private:
             Gtk::Frame    frmAxisV;
             Gtk::Layout   vlyAxisV;  // contains labels
             Gtk::Label   *lblAxisV;  // Are the labels
             Gtk::Box      hbxVfDvV;  // little square box below the asixV to keep the axesV calculations easier

             DrwOs        *vwDs;
             MdlOs        *mdOs;
             CtlMsgDspch  *ctMd;

             CbT<FrmOsAxisV> *MRU_RshAll;
};

#endif // __BOX_OS_AXIS_V_HPP_
