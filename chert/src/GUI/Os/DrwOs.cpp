// $Id: DrwOs.cpp 497 2019-08-17 20:46:44Z duncang $

//=================================================================================================
// Original File Name : DrwOs.cpp
// Original Author    : duncang
// Creation Date      : Oct 23, 2012
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include <glibmm.h>
#include "DrwOs.hpp"
#include <math.h>
#include <cairomm/context.h>

       DrwOs::DrwOs     ( Signal *i_sig ) {
  BuildEnv (i_sig);
  Connect  ();
  Init     ();
  ReGrid   ();
  show_all ();
}
       DrwOs::~DrwOs    ( void              ) {
  }
void   DrwOs::BuildEnv  ( Signal *i_sig ) {
  ctMd    = CtlMsgDspch ::GetInstance(       );
  ctRsmp  = CtlRsmp     ::GetInstance( i_sig );
  ctOsVrt = CtlOsVrt    ::GetInstance( i_sig );
  ctOsHor = CtlOsHor    ::GetInstance( i_sig );
  mdOs    = MdlOs       ::GetInstance( i_sig );

  cairoGridImage = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, 2400, 1600);
  croCntxt   = Cairo::Context::create(cairoGridImage);
  return;
}
void   DrwOs::Connect   ( void              ) {
  CbReportDraw      = NULL;
  MRU_OsDrwTrace  = NULL;

  add_events( Gdk::POINTER_MOTION_MASK      );
  add_events( Gdk::POINTER_MOTION_HINT_MASK );
  add_events( Gdk::KEY_PRESS_MASK           );
  add_events( Gdk::KEY_RELEASE_MASK         );
  add_events( Gdk::BUTTON_PRESS_MASK        );
  add_events( Gdk::BUTTON_RELEASE_MASK      );
  add_events( Gdk::ENTER_NOTIFY_MASK        );
  add_events( Gdk::SCROLL_MASK              );
  set_can_focus(true);

  signal_button_press_event()  .connect(sigc::mem_fun(*this, &DrwOs::OnButton    ) );
  signal_button_release_event().connect(sigc::mem_fun(*this, &DrwOs::OnButton    ) );
  signal_scroll_event()        .connect(sigc::mem_fun(*this, &DrwOs::OnScroll    ) );
  signal_enter_notify_event()  .connect(sigc::mem_fun(*this, &DrwOs::OnDrawFocus ) );
  //signal_motion_notify_event() .connect(sigc::mem_fun(*this, &DrwOs::OnMotion    ) );

//        MRU_ReDraw = new CbT<DrwOs>();
//        MRU_ReDraw->SetCallback(this, &DrwOs::OsDrwTrace);
//  ctMd->MSU_OsDrwReDraw = MRU_ReDraw;

        MRU_OsDrwTrace = new CbT<DrwOs>();
        MRU_OsDrwTrace->SetCallback(this, &DrwOs::OsDrwTrace);
  ctMd->MSU_OsDrwTrace = MRU_OsDrwTrace;



  return;
}
void   DrwOs::Init      ( void              ) { // Only the first time the window is built.
  //==============================================================
  // Color Scheme and other drawing stuff
  colScrnBg  .set_rgba(0.0, 0.15, 0.0, 1.0); // for now, the default dark green phosphor color.
  colScrnGrid.set_rgba(1.0, 1.0, 1.0, 1.0); // White as can be.
  m_radius       = 0.42;
  m_line_width   = 0.1;
  gridLineWidth  = 0.3267; // Seems line a very nice number
  traceLineWidth = 1.0;

  traceNom = ctRsmp->GetOsNom();;  // Wider than any possible display
  ctOsHor->SetScrSize(DEF_HOR, DEF_VRT);
  set_size_request(mdOs->GetWidth(), mdOs->GetHeight());
  return;
  }
void   DrwOs::ReBase    ( void              ) {
  return;
}




bool   DrwOs::CheckReSize(void) {
  bool wasResized;
  uint width;
  uint height;
  Gtk::Allocation a;
  a = this->get_allocation();

  wasResized = false;
  //First because on_draw is how we find out about a resize.
  width  = a.get_width();
  height = a.get_height();
  if((width != mdOs->GetWidth()) || (height != ctOsVrt->GetHeight())) {
    fprintf(stdout, "new OS size %u  %u\n", width, height);
    ctOsHor->SetScrSize(width, height);
    ReGrid();
    wasResized = true;
    }
  return wasResized;
}
void   DrwOs::ReGrid  ( void                                     ) {
  cairoGridImage->set_device_offset(0, 0); // This should probably never deviate, we're not panning.


//==================================================================================================================================
// Draw the screen darkness
  croCntxt->save();
  croCntxt->set_source_rgba(colScrnBg.get_red(), colScrnBg.get_green(), colScrnBg.get_blue(), colScrnBg.get_alpha());
  croCntxt->paint();
//==================================================================================================================================
// Draw the screen grids
  croCntxt->set_source_rgba(colScrnGrid.get_red(), colScrnGrid.get_green(), colScrnGrid.get_blue(), colScrnGrid.get_alpha());
  croCntxt->set_line_width(gridLineWidth);
  // draw 9 horizontal lines
  double xStart = 0.0;
  double xStop  = (double)mdOs->GetWidth();
  double yStart = mdOs->GetPxlVdiv();
  double yStop  = (double)ctOsVrt->GetHeight() * 0.9999999; // so that the lats line shows
  double yDel   = mdOs->GetPxlVdiv();
  for(double y = yStart; y < yStop; y += yDel) {
    croCntxt->move_to(round(xStart) + 0.5, round(y) + 0.5);
    croCntxt->line_to(round(xStop)  + 0.5, round(y) + 0.5);
    }
  // draw N vertical lines
  yStart = 0.0;
  yStop  = (double)ctOsVrt->GetHeight();
  xStart = mdOs->GetPxlVdiv();
  xStop  = (double)mdOs->GetWidth() * 0.99999; // so that the last line shows
  for(double x = mdOs->GetPxlVdiv(); x < xStop; x += mdOs->GetPxlVdiv()) {
    croCntxt->move_to(round(x) + 0.5, round(yStart) + 0.5);
    croCntxt->line_to(round(x) + 0.5, round(yStop)  + 0.5);
    }
  croCntxt->stroke();
  croCntxt->restore();
  return;
  }
void   DrwOs::on_show ( void                                     ) {
  ReGrid();
  Gtk::DrawingArea::on_show();
  return;
}
bool   DrwOs::on_draw ( const Cairo::RefPtr<Cairo::Context>& i_cr) {
  //fprintf(stdout, "o_d\n"); fflush(stdout);
  i_cr->save();
  CheckReSize();
  i_cr->restore();
  i_cr->save();
  // Paint the background screen and grid lines.
  i_cr->set_operator(Cairo::OPERATOR_SOURCE);
  i_cr->set_source(cairoGridImage, 0.0, 0.0);
  i_cr->paint();
  i_cr->restore();

  //Make a bunch of traces
  int    xDex;
  double yMidScr;
  double xStop;
  yMidScr   = mdOs->GetPxlVscrY();
  yMidScr  *=  0.5;
  xStop   = mdOs->GetPxlVscrX() * 0.9999999;
  i_cr->set_line_width(traceLineWidth);
  for(uint chDex=0; chDex<NUM_CH; chDex++) {
    if(ctOsVrt->GetEn(chDex)) { //Per Channel
      Gdk::RGBA tCol = ctOsVrt->GetCol(chDex);
      i_cr->set_source_rgba(tCol.get_red(), tCol.get_green(), tCol.get_blue(), tCol.get_alpha());
      i_cr->move_to(0.0, yMidScr);
      xDex = 0;
      for (double f = 0.0; f <= xStop; f += 1.0) {
        double r;
        r  = traceNom[chDex][xDex++];
        i_cr->line_to(f, r);
        }
      i_cr->stroke();
      }
    }
  return true;
  }
bool   DrwOs::OsDrwTrace  ( void *ddd                                ) { // only ever called from my parent WinOs
  Glib::RefPtr<Gdk::Window> win = get_window();
  Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
  if(win.get() != NULL) win->invalidate_rect(r, false); // drives on_draw to happen
  return true;
  }


bool   DrwOs::OnButton(GdkEventButton *i_e) {
  switch(i_e->type) {
  case GDK_BUTTON_PRESS:
    if(zoomState != EZS_IDLE) {
      fprintf(stdout, "VERY BAD LOGIC BAG END:  zoom pending but button press\n"); fflush(stdout);
      return false;
      }
    if(i_e->button != MBT_L) {
      fprintf(stdout, "wrong button, only left will be recognized at this time\n"); fflush(stdout);
      return false;
      }
    fprintf(stdout, "button press   %f,%f : %f %f\n", zoomStartX, zoomStartY, zoomEndX, zoomEndY); fflush(stdout);
    zoomState = EZS_DRAG;
    zoomStartX = i_e->x;
    zoomStartY = i_e->y;
    break;
  case GDK_BUTTON_RELEASE:
    if(zoomState != EZS_DRAG) {
      fprintf(stdout, "VERY BAD LOGIC BAG END:  zoom not pending but button released\n"); fflush(stdout);
      return false;
      }
    if(i_e->button != MBT_L) {
      fprintf(stdout, "wrong button, only left will be recognized at this time\n"); fflush(stdout);
      return false;
      }
    zoomState = EZS_IDLE;
    zoomEndX = i_e->x;
    zoomEndY = i_e->y;
    fprintf(stdout, "button release %f,%f : %f %f\n", zoomStartX, zoomStartY, zoomEndX, zoomEndY); fflush(stdout);
    break;
  case GDK_DOUBLE_BUTTON_PRESS:
    if(i_e->button != MBT_L) {
      fprintf(stdout, "wrong button, only left will be recognized at this time\n"); fflush(stdout);
      return false;
      }
    fprintf(stdout, "double-click ... maybe some day\n"); fflush(stdout);
    break;
  case GDK_TRIPLE_BUTTON_PRESS:
    fprintf(stdout, "wow ... triple-click ... good job\n"); fflush(stdout);
    break;
  default:
    fprintf(stderr, "UNHANDLED BUTTON EVENT %d\n", i_e->type);
    }
  return false;
  }
bool   DrwOs::OnScroll(GdkEventScroll *i_e) {

  if(i_e->direction == GDK_SCROLL_UP)
    fprintf(stdout, "scroll in  ");
  else
    fprintf(stdout, "scroll out ");
  zoomStartX = i_e->x;
  zoomStartY = i_e->y;
  zoomEndX = i_e->x;
  zoomEndY = i_e->y;
  if(i_e->state & GDK_SHIFT_MASK)
    fprintf(stdout, "   shift ");
  else
    fprintf(stdout, "no_shift ");
  if(i_e->state & GDK_CONTROL_MASK)
    fprintf(stdout, "   ctl   ");
  else
    fprintf(stdout, "no_ctl   ");
  fprintf(stdout, "%f,%f : %f %f   0x%08x\n", zoomStartX, zoomStartY, zoomEndX, zoomEndY, i_e->state); fflush(stdout);
  return true;
  }
bool   DrwOs::OnDrawFocus        (GdkEventCrossing *i_event) {
  grab_focus();
  //fprintf(stdout, "Crossed Into DrawScreen\n"); fflush(stdout);
  return false;
  }
bool   DrwOs::OnMotion(GdkEventMotion *i_e) {
  //fprintf(stdout, "mouse move     %f,%f\n", i_e->x, i_e->y); fflush(stdout);
  //fprintf(stdout, "."); fflush(stdout);
  return true;
  }
