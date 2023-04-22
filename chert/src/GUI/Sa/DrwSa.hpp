
// $Id: DrwSa.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : DrwSa.cpp
// Original Author    : duncang
// Creation Date      : Oct 17, 2012
// Copyright          : Copyright © 2011 - 2014 by Catraeus and Duncan Gray
//
// Description        :
/*
   This is the dark green draw screen of the spectrum anaylzer.
   It has:
   grid
   markers
   trace

   It does:
   spectrum analyze
   apodization
   decimation/interpolation

   It takes in:
   number of time points
   screen size
   log/lin horiz setting
   log/lin/db vert setting
   (vert lin)
     vert scale
   (vert dB or log)
     vert scale, vert offset bottom
     vert scale, vert offset mid
     vert scale, vert offset top
     vert bottom, vert top
   (horiz lin)
     start, stop
     anchor, span anchor_f, anchor_pct

*/
//
//=================================================================================================

#ifndef __DRW_SA_HPP_
#define __DRW_SA_HPP_

#include <gtkmm/drawingarea.h>

#include <caes/CaesCallBack.hpp>

#include "../../Ctl/Sa/CtlSaHor.hpp"
#include "../../Ctl/CtlRsmp.hpp"

#include "../../Mdl/MdlSa.hpp"
#include "../../Ctl/CtlMsgDspch.hpp"

class DrwSa : public Gtk::DrawingArea {
  private:
    enum eConst {
      EK_CH_MAX    =    4,
      EK_PXL_X_NOM =  800,
      EK_PXL_X_MAX = 1800,
      EK_PXL_Y_NOM =  400,
      EK_PXL_Y_MAX = 1800
    };
  public:
    enum eScale {ES_LOG, ES_LIN, ES_DB};
                    DrwSa         ( Signal *i_sig );
    virtual        ~DrwSa         ( void          );
  private:
            void    BuildEnv      ( Signal *i_sig );
            void    BuildMain     ( void          );
            void    BuildSetup    ( void          );
            void    Connect       ( void          );
  public:
            bool    OnSaDrwTrace  ( void *i_d     );
            void    OnReGrid      ( void          );
  private:
            void    CheckResize   ( void          );
  protected:
  //Override default signal handler:
    virtual void    on_show       ( void                                   );
    virtual bool    on_draw       ( const Cairo::RefPtr<Cairo::Context>& cr);
  private:
    Cairo::RefPtr<Cairo::ImageSurface> cis_grid; //!< The screen background
    Cairo::RefPtr<Cairo::Context>      cd;


    double           m_line_width;
    double           m_radius;
    static double   *logGridList;

    eScale           hScale;
    eScale           vScale;

    double         **ff;  // the transformed and resampled frequency points

    CtlSaHor        *ctSaHor;

    CtlRsmp         *ctRsmp;
    MdlSa           *mdSa;
    CtlMsgDspch     *ctMd;

    CbT<DrwSa>      *CbHn_SaDrwTrace;
  public:
    CbV             *MSU_SaReSize;
    static int       busy;

  };

#endif // __DRW_SA_HPP_

