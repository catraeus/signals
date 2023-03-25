// $Id: DrwSa.cpp 511 2020-06-21 17:17:47Z duncang $

//=================================================================================================
// Original File Name : DrwSa.cpp
// Original Author    : duncang
// Creation Date      : Oct 17, 2012
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//
//
//=================================================================================================

#include "DrwSa.hpp"

#include <glibmm.h>
#include <math.h>
#include <cairomm/context.h>

double *DrwSa::logGridList = 0;
int     DrwSa::busy = 0;

        DrwSa::DrwSa      ( Signal *i_sig ) {
  BuildEnv   ( i_sig );
  BuildSetup (       );
  BuildMain  (       );
  Connect    (       );
  ReGrid     (       );
  show_all();
  }
        DrwSa::~DrwSa     ( void ) {
}
void    DrwSa::BuildEnv   ( Signal *i_sig ) {
  ctSaHor = CtlSaHor    :: GetInstance( i_sig );
  ctRsmp  = CtlRsmp     :: GetInstance( i_sig );
  mdSa    = MdlSa       :: GetInstance(       );
  ctMd    = CtlMsgDspch :: GetInstance(       );

  if(logGridList == 0) {
    logGridList = new double[100];
    for(int i=0; i<10; i++) {
      logGridList[i] = log10((double)(i + 1));
      }
    }
  return;
}
void    DrwSa::BuildMain  ( void ) {
  set_size_request(EK_PXL_X_NOM, EK_PXL_Y_NOM);
  cis_grid = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, EK_PXL_X_MAX, EK_PXL_Y_MAX);
  cd       = Cairo::Context::create(cis_grid);
  return;
}
void    DrwSa::BuildSetup ( void ) {
  m_line_width = 0.10;
  m_radius     = 0.42;
  hScale       = ES_LIN;
  vScale       = ES_DB;
  ff           = ctRsmp->GetSaNom(); // WARNING Don't allocate the arrays, they get pointered from the resampler's allocation.
  busy         = 0;
  return;
}
void    DrwSa::Connect    ( void ) {
  MSU_SaReSize = NULL;

  MRU_SaDrwTrace             = new CbT<DrwSa>();
  MRU_SaDrwTrace            ->SetCallback(this, &DrwSa::SaDrwTrace);
  ctMd->MSU_SaDrwTrace     = MRU_SaDrwTrace;
  busy = 0;
  return;
}



void    DrwSa::ReGrid       ( void ) {
  double xStart;
  double xStop;
  double yStart;
  double yStop;

  xStop = get_allocated_width();
  yStop = get_allocated_height();
  mdSa->SetPxlVscrX(xStop);
  mdSa->SetPxlVscrY(yStop);
  m_line_width = 0.3267;
  cis_grid->set_device_offset(0, 0);

  cd->set_line_width(m_line_width);

  //cd->save();
  cd->set_source_rgba(0.0, 0.15, 0.0, 1.0); // green of the scope screen dim phosphor
  cd->paint();
  cd->set_source_rgba(1.0, 1.0, 1.0, 1.0); // white of the grid line
    // draw 9 horiz lines
  xStart = 0.0;
  xStop  = mdSa->GetPxlVscrX() * 0.9999;
  yStart = mdSa->GetPxlVdivX();
  yStop  = mdSa->GetPxlVscrY() * 0.9999;
  cd->set_line_width(m_line_width * 2);
  for(double y = yStart; y < yStop; y += mdSa->GetPxlVdivX()) {
    cd->move_to(round(xStart) + 0.5, round(y) + 0.5);
    cd->line_to(round(xStop)  + 0.5, round(y) + 0.5);
    cd->stroke();
    }
  yStart = 0.00;
  if(mdSa->IsLogX()) {
    double decadeWidth;
    double numDecades;
    double fMin;
    numDecades  = mdSa->GetFmax();
    fMin = mdSa->GetFmin();
    if(fMin < .001) fMin = numDecades / 100000.0;
    numDecades /= fMin;
    numDecades  = log10(numDecades);
    decadeWidth  = 1.0 / numDecades;
    decadeWidth = mdSa->GetPxlVscrX() * decadeWidth;

    for(double decadeBase = 0.0; decadeBase < numDecades; decadeBase += 1.0) {
      for(int i=1; i<10; i++) {
        double x = decadeBase + logGridList[i];
        x *= decadeWidth;
        if(i == 9)
          cd->set_line_width(0.6534);
        else
          cd->set_line_width(0.2327);
        cd->move_to(round(x) + 0.5, round(yStart) + 0.5);
        cd->line_to(round(x) + 0.5, round(yStop) + 0.5);
        cd->stroke();
        }
      }
    }
  else { // Linear Grid Maker
    // draw N vert lines
    xStart = mdSa->GetPxlVdivX();
    xStop  = mdSa->GetPxlVscrX()* 0.99999;
    cd->set_line_width(0.6534);
   for(double x = xStart; x < xStop; x += xStart) {
      cd->move_to(round(x) + 0.5, round(yStart) + 0.5);
      cd->line_to(round(x) + 0.5, round(yStop) + 0.5);
      cd->stroke();
      }
    }
  //cd->restore();
  double tB;
  tB = mdSa->GetPxlVscrX();
  if(MSU_SaReSize != 0) {
    MSU_SaReSize->Execute(&tB);
    }
  return;
  }
void    DrwSa::CheckResize  ( void ) {
  Gtk::Allocation allocation = get_allocation();
  int width  = allocation.get_width();
  int height = allocation.get_height();
  if((width != mdSa->GetPxlVscrX()) || (height != mdSa->GetPxlVscrY())) {
    ctSaHor->SetScrSize(width, height);
    ReGrid();
    }
  return;
}
void    DrwSa::on_show      ( void                                     ) {
  ReGrid();
  Gtk::DrawingArea::on_show();
  return;
}
bool    DrwSa::on_draw      ( const Cairo::RefPtr<Cairo::Context>& cr ) {
  double  scaleF;
  ullong  numSa;
  double  r;
  double  fC;
  double *pAry;

  cr->save();
  CheckResize();
  cr->restore();
  cr->save();
  cr->set_operator(Cairo::OPERATOR_SOURCE);
  cr->set_source(cis_grid, 0.0, 0.0);
  cr->paint();
  cr->restore();

  cr->set_source_rgba(1.0, 0.7, 0.0, 1.0); // Orange
  cr->set_line_width(0.707);
  cr->move_to(0.0, mdSa->GetPxlVscrY() / 2.0);
  scaleF = 1.0;
  numSa  = (ullong)mdSa->GetPxlVscrX();
  pAry   = ff[0];
  for (ullong ii=0; ii < numSa; ii++) {
    fC = (double)ii * scaleF;

    r  = pAry[ii];
    if(ii == 0)
      cr->move_to(fC, r);
    else
      cr->line_to(fC, r);
    }
  cr->stroke();
  busy = 0;
  return true;
}

bool    DrwSa::SaDrwTrace  ( void *i_d) {
  //if(busy) {fprintf(stderr, "oops %6d\n", rand()); fflush(stderr);}
  Glib::RefPtr<Gdk::Window> win = get_window();
  Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
  if(win.get() != NULL) {
    busy = 1;
    win->invalidate_rect(r, false); // drives on_draw to happen
  }
  return true;
}