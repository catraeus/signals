/*
 * PageNoise.hpp
 *
 *  Created on: Mar 7, 2017
 *      Author: duncang
 */

#ifndef __PAGE_NOISE_HPP_
#define __PAGE_NOISE_HPP_

#include <gtkmm.h>

#include <caes/AudioFile/Signal.hpp>

#include "../Ctl/CtlMsgDspch.hpp"
#include "../Ctl/CtlWave.hpp"
#include "../Ctl/CtlNoise.hpp"

class PageNoise: public Gtk::Box {
  public:
                       PageNoise        ( Signal *i_sig  );
    virtual           ~PageNoise        ( void           );

  private:
              void     BuildEnv        ( Signal *i_sig  );
              void     BuildMain       ( void           );
              void     Connect         ( void           );

              void     OnChangeShape   ( void           );

              bool     OnChangeRR      ( GdkEventFocus *i_e    );

              bool     OnChangeAmpLin  ( GdkEventFocus *i_e    );
              bool     OnChangeAmpDb   ( GdkEventFocus *i_e    );



  public:
  private:
              Gtk::Frame                frmDist;
              Gtk::Box                  hbxDist;
              Gtk::RadioButton::Group   rbgDistType;
              Gtk::RadioButton         *rbtDistRect;
              Gtk::RadioButton         *rbtDistGauss;
              Gtk::Label                lblRR;
              Gtk::Entry                ebxRR;

              Gtk::Frame                frmAmp;
              Gtk::Box                  hbxAmp;
              Gtk::Label                lblAmpLin;
              Gtk::Entry                ebxAmpLin;
              Gtk::Label                lblAmpDb;
              Gtk::Entry                ebxAmpDb;

              bool                      actionHoldoff;

              CtlWave                  *ctWave;
              CtlNoise                 *ctNoise;

              CtlMsgDspch              *ctMd;

              CbT<PageNoise>            *MRU_NoiseRshAll;
              bool                        OnNoiseRshAll   ( void *i_d     );

};

#endif // __PAGE_NOISE_HPP_
