
// $Id: PageRemez.hpp 572 2021-06-21 00:42:24Z duncang $

//=================================================================================================
// Original File Name : PageRemez.hpp
// Original Author    : duncang
// Creation Date      : 2017-03-12T14:56:47,226221993+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//    Pretty self descriptive, eh!?
//
//=================================================================================================

#ifndef __PAGE_REMEZ_HPP_
#define __PAGE_REMEZ_HPP_

#include <gtkmm.h>
#include "../Ctl/CtlMsgDspch.hpp"
#include "../Ctl/CtlWave.hpp"
#include "../Ctl/CtlRemez.hpp"

class PageRemez: public Gtk::Box {
  public:
  private:
    enum eConst {NUM_BANDS = 5};
  public:
                       PageRemez        ( Signal *i_sig  );
    virtual           ~PageRemez        ( void          );

  private:
              void     BuildEnv         ( Signal *i_sig  );
              void     BuildMain        ( void          );
              void     Connect          ( void          );

              bool     OnKeyPbandRel    ( GdkEventKey   *i_e    );
              void     OnChangeBandSa   ( llong          i_b, char *i_cc   );
              bool     OnChangeBandSa0  ( GdkEventFocus *i_e    );
              bool     OnChangeBandSa1  ( GdkEventFocus *i_e    );
              bool     OnChangeBandSa2  ( GdkEventFocus *i_e    );
              bool     OnChangeBandSa3  ( GdkEventFocus *i_e    );
              bool     OnChangeBandSa4  ( GdkEventFocus *i_e    );
              bool     OnKeyPbandAbs    ( GdkEventKey   *i_e    );
              bool     OnChangePbandAbs ( GdkEventFocus *i_e    );

              bool     OnKeyXbandRel    ( GdkEventKey   *i_e    );
              bool     OnChangeXbandRel ( GdkEventFocus *i_e    );
              bool     OnKeyXbandAbs    ( GdkEventKey   *i_e    );
              bool     OnChangeXbandAbs ( GdkEventFocus *i_e    );

              bool     OnKeySbWtLin     ( GdkEventKey   *i_e    );
              bool     OnChangeSbWtLin  ( GdkEventFocus *i_e    );
              bool     OnKeySbWtDb      ( GdkEventKey   *i_e    );
              bool     OnChangeSbWtDb   ( GdkEventFocus *i_e    );

              void     OnChangeFreq     ( void          );

  public:
  private:
              Gtk::Grid                *grdBands;
              Gtk::Label                lblBandBn;     Gtk::Frame  frmBandBnHd;
              Gtk::Label                lblBandSa;     Gtk::Frame  frmBandSaHd;
              Gtk::Label                lblBandSr;     Gtk::Frame  frmBandSrHd;
              Gtk::Label                lblBandPa;     Gtk::Frame  frmBandPaHd;
              Gtk::Label                lblBandPr;     Gtk::Frame  frmBandPrHd;
              Gtk::Label                lblBandWa;     Gtk::Frame  frmBandWaHd;
              Gtk::Label                lblBandWd;     Gtk::Frame  frmBandWdHd;

              Gtk::Label               *lblBn;
              Gtk::Frame               *frmBn;
              Gtk::Entry                ebxBandSa0, ebxBandSa1, ebxBandSa2, ebxBandSa3, ebxBandSa4;
              Gtk::Frame               *frmSa;

              Gtk::Frame                frmPband;
              Gtk::Box                  hbxPband;
              Gtk::Label                lblPbandRel;
              Gtk::Entry                ebxPbandRel;
              Gtk::Label                lblPbandAbs;
              Gtk::Entry                ebxPbandAbs;

              Gtk::Frame                frmXband;
              Gtk::Box                  hbxXband;
              Gtk::Label                lblXbandRel;
              Gtk::Entry                ebxXbandRel;
              Gtk::Label                lblXbandAbs;
              Gtk::Entry                ebxXbandAbs;

              Gtk::Frame                frmSbWt;
              Gtk::Box                  hbxSbWt;
              Gtk::Label                lblSbWtLin;
              Gtk::Entry                ebxSbWtLin;
              Gtk::Label                lblSbWtDb;
              Gtk::Entry                ebxSbWtDb;

              bool                      actionHoldoff;

              CtlMsgDspch              *ctMd;

              CtlWave                  *ctWave;
              CtlRemez                 *ctRemez;

              CbT<PageRemez>            *MRU_RemezRshAll;
              bool                       OnRemezRshAll   ( void *i_d     );

};

#endif // __PAGE_REMEZ_HPP_
