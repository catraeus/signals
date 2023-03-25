// $Id: CtlOsVrt.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : CtlOsVrt.hpp
// Original Author    : duncang
// Creation Date      : 2017-01-24T01:42:55,212117768+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================
/*! \brief  Controling the vertical things.  All viewish.

This is a single blob that has 4 dups of pretty much everything in it.  That gives us:
  The ability to have channels know things about each other, like I/Q maybe.
  4:1 message reduction.  I'm on a diet you know.
*/

#ifndef __CTL_OS_VRT_HPP_
#define __CTL_OS_VRT_HPP_

#include <gtkmm.h>

#include <caes/CaesTypes.hpp>
#include <caes/AudioFile/Signal.hpp>

#include "../../Mdl/MdlOs.hpp"
#include "../CtlMsgDspch.hpp"

class CtlOsVrt {
  public:
    enum eConst {
      COVK_MAX_CH = 4
    };
  private:
  private:
                      CtlOsVrt      ( Signal *i_sig );
    virtual          ~CtlOsVrt      ( void );
  public:
    static  CtlOsVrt *GetInstance   ( Signal *i_sig );
  private:
            void      BuildEnv      ( Signal *i_sig            );
            void      BuildMain     ( void                     );
            void      BuildSetup    ( void                     );
            void      Connect       ( void                     );
  public:
            bool      OnColChange   ( GdkEventButton *e       , int i_ch, Gtk::Window    *i_p );
            void      SetEn         ( bool      i_en,  uint i_ch ) { en [i_ch] = i_en  ; return           ; };
            bool      GetEn         (                  uint i_ch ) {                     return en[i_ch]  ; };
            void      SetCol        ( Gdk::RGBA i_col, uint i_ch ) { col[i_ch] = i_col ; return           ; };
            Gdk::RGBA GetCol        (                  uint i_ch ) {                     return col[i_ch] ; };

            uint      GetHeight     ( void                       ) {                     return mdOs->GetPxlVscrY();};

            llong     GetPxlMaxV    ( void                       ) {return (llong)MdlOs::EK_PX_Y_MAX; };
            void      SetVoltVscr   ( double i_d                 );
  private:
  public:
  private:
            bool            en[COVK_MAX_CH];
            Gdk::RGBA       col[COVK_MAX_CH];
    static  CtlOsVrt       *ctOsVrt;

            Gtk::Window    *parent;
            MdlOs          *mdOs;
            CtlMsgDspch    *ctMd;
};

#endif // __CTL_OS_VRT_HPP_
