
// $Id: PageSine.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : PageSine.hpp
// Original Author    : duncang
// Creation Date      : 2017-03-12T14:56:47,226221993+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//    Pretty self descriptive, eh!?
//
//=================================================================================================

#ifndef __PAGE_SINE_HPP_
#define __PAGE_SINE_HPP_

#include <gtkmm.h>

#include <caes/CaesCallBack.hpp>
#include <caes/AudioFile/Signal.hpp>

#include "../Ctl/CtlMsgDspch.hpp"
#include "../Ctl/CtlWave.hpp"
#include "../Ctl/CtlSine.hpp"

class PageSine: public Gtk::Box {
  public:
                       PageSine            ( Signal *i_sig );
    virtual           ~PageSine            ( void          );

  private:
              void     BuildEnv            ( void          );
              void     BuildMain           ( void          );
              void     Connect             ( void          );

              bool     OnKeyFreqRel        ( GdkEventKey   *i_e    );
              bool     OnChangeFreqRel     ( GdkEventFocus *i_e    );
              bool     OnKeyFreqAbs        ( GdkEventKey   *i_e    );
              bool     OnChangeFreqAbs     ( GdkEventFocus *i_e    );
              bool     OnKeyFreqN          ( GdkEventKey   *i_e    );
              bool     OnChangeFreqN       ( GdkEventFocus *i_e    );
              void     OnChangeSinCosSin   ( void          );
              void     OnChangeSinCosCos   ( void          );
              void     OnChangeSinCosIQ    ( void          );
              void     OnChangeZeroStart   ( void          );
              void     OnChangeZeroCenter  ( void          );

              bool     OnKeyAmpLin         ( GdkEventKey   *i_e    );
              bool     OnChangeAmpLin      ( GdkEventFocus *i_e    );
              bool     OnKeyAmpDb          ( GdkEventKey   *i_e    );
              bool     OnChangeAmpDb       ( GdkEventFocus *i_e    );


  public:
  private:
              Gtk::Frame                frmFreq;
              Gtk::Box                  hbxFreq;
              Gtk::Label                lblFS;
              Gtk::Entry                ebxFS;
              Gtk::Label                lblFreqRel;
              Gtk::Entry                ebxFreqRel;
              Gtk::Label                lblFreqAbs;
              Gtk::Entry                ebxFreqAbs;
              Gtk::Label                lblFreqN;
              Gtk::Entry                ebxFreqN;

              Gtk::Frame                frmAmp;
              Gtk::Box                  hbxAmp;
              Gtk::Label                lblAmpLin;
              Gtk::Entry                ebxAmpLin;
              Gtk::Label                lblAmpDb;
              Gtk::Entry                ebxAmpDb;

              Gtk::RadioButton::Group   rbgSinCos;
              Gtk::RadioButton         *rbtSelSinCosSin;
              Gtk::RadioButton         *rbtSelSinCosCos;
              Gtk::RadioButton         *rbtSelSinCosIQ;
              Gtk::Label                lblSinSep;
              Gtk::RadioButton::Group   rbgZero;
              Gtk::RadioButton         *rbtZeroStart;
              Gtk::RadioButton         *rbtZeroCenter;

              bool                      actionHoldoff;

              Signal                   *sig;
              CtlWave                  *ctWave;
              CtlSine                  *ctSine;

              CtlMsgDspch              *ctMd;

              CbT<PageSine>            *MRU_SineRshAll;
              bool                      OnSineRshAll   ( void *i_d     );

};

#endif // __PAGE_SINE_HPP_
