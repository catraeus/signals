
// $Id: WinAbout.hpp 7 2014-10-16 01:36:47Z duncang $

//=================================================================================================
// Original File Name : WinAbout.h
// Original Author    : duncang
// Creation Date      : Dec 11, 2010
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//
//=================================================================================================

#ifndef __AF_WIN_ABOUT_H_
#define __AF_WIN_ABOUT_H_


#include <gtkmm.h>
#include "../../src/Cfg/CfgParticles.hpp"
#include "../../src/Cfg/CfgStrings.hpp"

class WinAbout : public Gtk::AboutDialog {
  public:
                  WinAbout(CfgStrings *i_as, CfgParticles *i_tp);
    virtual      ~WinAbout();
  protected:
    virtual bool  on_delete_event(GdkEventAny *event);
    virtual void  on_hide(void);
  private:
  public:
  protected:
  private:
    CfgParticles       *tp;
    CfgStrings         *as;
  };


#endif // __AF_WIN_ABOUT_H_
