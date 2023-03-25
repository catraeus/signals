
// $Id: CfgParticles.hpp 506 2019-12-25 15:35:12Z duncang $

//=================================================================================================
// Original File Name : CfgParticles.h
// Original Author    : duncang
// Creation Date      : Feb 14, 2010
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//
//=================================================================================================

#ifndef __CFG_PARTICLES_HPP_
#define __CFG_PARTICLES_HPP_
#include <gdkmm.h>
/* \cond HIDDEN_SYMBOLS */
class CfgParticles {
  public:
  private:
             CfgParticles();
    virtual ~CfgParticles();
  public:
    static CfgParticles *GetInstance(void);
    enum eKeys {
        K_UP     = 0xff52,
        K_LEFT   = 0xff51,
        K_DOWN   = 0xff54,
        K_RIGHT  = 0xff53,
        K_TAB    = 0xff09,
        K_ENTER  = 0xff0d,
        K_DEL    = 0xff9f,
        K_DELETE = 0xffff,
        K_BACK   = 0xff08,
        K_ESC    = 0xff1b,
        L_CHAR_MINUS = 0x002d
    };
    Glib::RefPtr<Gdk::Pixbuf> pxbf_xIconApp;
    Glib::RefPtr<Gdk::Pixbuf> pxbf_xLogoApp;

    Glib::RefPtr<Gdk::Pixbuf> pxbf_op_quit_bright;
    Glib::RefPtr<Gdk::Pixbuf> pxbf_op_fileOpen_bright;
    Glib::RefPtr<Gdk::Pixbuf> pxbf_op_helpAbout;
    Glib::RefPtr<Gdk::Pixbuf> pxbf_pn_LEDgrnOn;
    Glib::RefPtr<Gdk::Pixbuf> pxbf_pn_LEDgrnOff;
    Gdk::Color colr_Caes_Iridium;
    Gdk::Color colr_Caes_Tungsten;
    Gdk::Color colr_Caes_Carbon;
    Gdk::Color colr_Caes_RedLight;
    Gdk::Color colr_Caes_RedMid;
    Gdk::Color colr_Caes_RedDark;
    Gdk::Color colr_Caes_GreenLight;
    Gdk::Color colr_Caes_GreenDark;
    Gdk::Color colr_Caes_BlueLight;
    Gdk::Color colr_Caes_BlueDark;
    Glib::ustring cols_Caes_Iridium;
    Glib::ustring cols_Caes_Tungsten;
    Glib::ustring cols_Caes_Carbon;
    Glib::ustring cols_Caes_RedLight;
    Glib::ustring cols_Caes_RedMid;
    Glib::ustring cols_Caes_RedDark;
    Glib::ustring cols_Caes_GreenLight;
    Glib::ustring cols_Caes_GreenDark;
    Glib::ustring cols_Caes_BlueLight;
    Glib::ustring cols_Caes_BlueDark;
  private:
    static CfgParticles *cp;
  };
/* \endcond HIDDEN_SYMBOLS */

#endif /* __CFG_PARTICLES_HPP_ */
