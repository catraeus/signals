// $Id: PageApod.hpp 743 2023-02-28 03:31:29Z duncang $

//=================================================================================================
// Original File Name : WinApod.hpp
// Original Author    : duncang
// Creation Date      : Aug 28, 2013
// Copyright          : Copyright © 2011 - 2017 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#ifndef __PAGE_APOD_HPP_
#define __PAGE_APOD_HPP_

#include <gtkmm.h>

#include "../Ctl/CtlApod.hpp"
#include "../Ctl/CtlWave.hpp"
#include "../Ctl/CtlMsgDspch.hpp"

#include <caes/AudioFile/Signal.hpp>
#include <caes/CaesApodia.hpp>
#include <caes/CaesCallBack.hpp>


class PageApod: public Gtk::Box {
  private:
    enum eConst {
      EPA_MAX_COS_APOD = 3
    };
  public:
                    PageApod         ( Signal *i_sig          );
    virtual        ~PageApod         ( void                   );
  private:
            void    BuildEnv         ( Signal *i_sig          );
            void    BuildMain        ( void                   );
            void    Setup            ( void                   );
            void    Connect          ( void                   );

            void    OnShape          ( void                   );
            void    OnAlpha          ( void                   );
            void    OnAnti           ( void                   );
            void    ExecuteChange    ( void                   );
            bool    AlphaSigFocOut   ( GdkEventFocus* i_event );
            void    AlphaSigAct      ( void                   );
  private:

    //====================
    // Spec row
    Gtk::Box              hbxSpec;

    Gtk::ComboBoxText    *cbxShape;
    Gtk::Label           *lblAlpha;
    Gtk::Entry           *txtAlpha;
    Gtk::CheckButton     *cbAnti;

    //====================
    // Vector text box
    Gtk::Box              hbxVector;
    Gtk::Box              hbxVectorDummy;
    Gtk::ScrolledWindow  *txtVector_scrl;  // A scroller to contain a long text view
    Gtk::TextView        *txtVector_txtv;  // A very long text view
    Glib::RefPtr<
    Gtk::TextBuffer>      txtVector_bufr;  // A text buffer for the text view

  private:

    bool                  actionHoldoff;

    CtlWave              *ctWave;
    CtlApod              *ctApod;
    Apodia               *mdApod;

    CbT<PageApod>       *MRU_ApodRshAll;
    bool                 OnApodRshAll ( void *                 );

    CtlMsgDspch         *ctMd;

  };

#endif // __PAGE_APOD_HPP_
