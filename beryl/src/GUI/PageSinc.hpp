
// $Id: PageSinc.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : PageSinc.hpp
// Original Author    : duncang
// Creation Date      : 2017-04-16T15:57:59,514344111+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//    Pretty self descriptive, eh!?
//
//=================================================================================================

#ifndef __PAGE_SINC_HPP_
#define __PAGE_SINC_HPP_

#include <gtkmm.h>

#include <caes/AudioFile/Signal.hpp>

#include "../Ctl/CtlMsgDspch.hpp"
#include "../Ctl/CtlSinc.hpp"
#include "../Ctl/CtlWave.hpp"

class PageSinc: public Gtk::Box {
  public:
                       PageSinc         ( Signal *i_sig  );
    virtual           ~PageSinc         ( void           );

  private:
              void     BuildEnv        ( Signal *i_sig  );
              void     BuildMain       ( void           );
              void     Connect         ( void           );

              bool     OnChangeFreqRel ( GdkEventFocus *i_e    );
              bool     OnChangeFreqAbs ( GdkEventFocus *i_e    );


  public:
  private:
              Gtk::Frame                frmSig;
              Gtk::Box                  hbxFreq;

              Gtk::Label                lblFreqRel;
              Gtk::Entry                ebxFreqRel;
              Gtk::Label                lblFreqAbs;
              Gtk::Entry                ebxFreqAbs;

              bool                      actionHoldoff;

              CtlSinc                  *ctSinc;
//              Signal                   *mdSig;
              CtlWave                  *ctWave;

              CtlMsgDspch              *ctMd;

              CbT<PageSinc>             *MRU_SincRshAll;
              bool                        OnSincRshAll   ( void *i_d     );

};

#endif // __PAGE_SINC_HPP_
