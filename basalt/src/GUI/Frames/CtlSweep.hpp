// $Id: CtlSweep.hpp 506 2019-12-25 15:35:12Z duncang $

//=================================================================================================
// Original File Name : twfWriteWrite.hpp
// Original Author    : duncang
// Creation Date      : Oct 27, 2012
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#ifndef __CTL_SWEEP_HPP_
#define __CTL_SWEEP_HPP_


#include <gtkmm.h>
#include "../../Cfg/CfgParticles.hpp"
#include "../../Cfg/CfgEnv.hpp"
#include <caes/CaesTypes.hpp>

class CtlSweep: public Gtk::Frame {
  public:
          CtlSweep();
         ~CtlSweep();
  private:
    void  SetFileName(char *);
    void  ClearFileInfo(void);
    void  OnTypeChanged();

    CfgParticles             *cp;
    CfgEnv                   *ce;

    Gtk::Box                  vbx_Main;

    Gtk::Frame                frmType;
    Gtk::Label                lblType;
    Gtk::Box                  hbxType;
    Gtk::ComboBox             ebxType;

    Gtk::Frame                frmCtlFmt;
    Gtk::Box                  vbxCtlFmt;
    Gtk::Box                  hbxCtlFmt1;
    Gtk::Label                lblFmtCode;
    Gtk::Entry                ebxFmtCode;

    Gtk::Box                  hbxCtlFmt2;
    Gtk::Label                lblFmtNumChan;
    Gtk::Entry                ebxFmtNumChan;
    Gtk::Label                lblFmtSmplRate;
    Gtk::Entry                ebxFmtFrmRate;
    Gtk::Label                lblFmtWordSize;
    Gtk::Entry                ebxFmtWordSize;

    Gtk::Box                  hbxCtlFactData;
    Gtk::Frame                frmCtlData;
    Gtk::Box                  hbxCtlData;
    Gtk::Label                lblDataSize;
    Gtk::Entry                ebxDataSize;

    Gtk::Frame                frmCtlArray;
    Gtk::Box                  hbxCtlArray;
    Gtk::Label                lblWaveNumFrms;
    Gtk::Entry                ebxWaveNumFrms;
    Gtk::Label                lblWaveTimeDur;
    Gtk::Entry                ebxWaveTimeDur;

    class CbxTypeCols : public Gtk::TreeModel::ColumnRecord {
      public:
        CbxTypeCols() { add(type);}
        Gtk::TreeModelColumn<Glib::ustring> type;
      };
    Glib::RefPtr<Gtk::ListStore> cbxTypeModel;

    CbxTypeCols cbxTypeCols;
  };

#endif /* __CTLtwf_HPP_ */
