// $Id: DrwOs.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : DrwOs.hpp
// Original Author    : duncang
// Creation Date      : Oct 23, 2012
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#ifndef __DRW_OS_HPP_
#define __DRW_OS_HPP_

#include <gtkmm/drawingarea.h>

#include <caes/CaesCallBack.hpp>

#include "../../Ctl/Os/CtlOsHor.hpp"
#include "../../Ctl/Os/CtlOsVrt.hpp"
#include "../../Mdl/MdlOs.hpp"


#include "../../Ctl/CtlRsmp.hpp"
#include "../../Ctl/CtlMsgDspch.hpp"


class DrwOs : public Gtk::DrawingArea {
  public:
  private:
  enum eConst {
    NUM_CH    =    4,
    MAX_HORIZ = 4096,
    DEF_HOR   =  800,
    DEF_VRT   =  400,
    MBT_L                =    1,
    MBT_M                =    2,
    MBT_R                =    3
  };
  enum eZoomState {
    EZS_IDLE,
    EZS_DRAG,
    EZS_SCROLL
    };
  public:
                    DrwOs         ( Signal *i_sig );
    virtual        ~DrwOs         ( void       );
            CbV    *CbReportDraw; // Tell the scopeH that it's time to get the next one.
            llong   GetHeight     ( void       )  { return ctOsVrt->GetHeight() ;};
            double *GetTrace      ( llong i_ch )  { return traceNom[i_ch]  ;};
            void    ReBase        ( void       );
            bool    OsDrwTrace    ( void *ddd  );
  private:
            void    BuildEnv      ( Signal *i_sig );
            void    Connect       ( void       );
            void    Init          ( void       );

            bool    CheckReSize   ( void       );
            void    ReGrid        ( void       );

            bool    OnButton      ( GdkEventButton   *i_e     );
            bool    OnScroll      ( GdkEventScroll   *i_e     );
            bool    OnDrawFocus   ( GdkEventCrossing *i_event );
            bool    OnMotion      ( GdkEventMotion   *i_e     );
  protected:
  //Override default signal handler:
    virtual void    on_show       ( void                                   );
    virtual bool    on_draw       ( const Cairo::RefPtr<Cairo::Context>& cr);
  public:
  private:
          Cairo::RefPtr<Cairo::ImageSurface> cairoGridImage;
          Cairo::RefPtr<Cairo::Context>      croCntxt;
  public:
  protected:
    double           m_radius;
    double           m_line_width;
  private:

  public:
    double         **traceNom;
    CtlOsVrt        *ctOsVrt;
    CtlOsHor        *ctOsHor;
    MdlOs           *mdOs;


    Gdk::RGBA        colScrnBg;
    Gdk::RGBA        colScrnGrid;
    double           gridLineWidth;
    double           traceLineWidth;


//===============================================================================================
// State Control
  private:
    eZoomState       zoomState;
    double           zoomStartX;
    double           zoomStartY;
    double           zoomEndX;
    double           zoomEndY;

    CtlRsmp         *ctRsmp;
    CtlMsgDspch     *ctMd;
    CbT<DrwOs>      *MRU_OsDrwTrace;
    CbT<DrwOs>      *MRU_ReDraw;
  };

#endif // __DRW_OS_HPP_
