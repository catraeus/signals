// $Id: MdlOs.cpp 497 2019-08-17 20:46:44Z duncang $

//=================================================================================================
// Original File Name : MdlOs.cpp
// Original Author    : duncang
// Creation Date      : Oct 19, 2013
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include "MdlOs.hpp"
#include <gtkmm.h>

MdlOs *MdlOs::mdOs = NULL;

       MdlOs::MdlOs         ( Signal *i_sig )
: sig (i_sig) {
  BuildEnv  ();
  BuildSpace();
  Connect   ();
  return;
}
       MdlOs::~MdlOs        ( void             ) {

}
void   MdlOs::BuildEnv      ( void             ) {
  smpVanaP     = NULL;
  return;
}
void   MdlOs::BuildSpace    ( void             ) {

  timVrsh   =  0.05;
  smpVsrd   = EK_PX_X_NOM;

  pxlVscrX  = EK_PX_X_NOM;
  smpVscr   = EK_PX_X_NOM;
 if(smpVanaP != NULL) *smpVanaP  = smpVscr;

  pxlVscrY  = EK_PX_Y_NOM;
  pxlVdiv   = pxlVscrY / 10.0;  // FIXME  It will be more intuitive to have divVscrY then derive when asked

  dir       = XD_FWD;
  posT      =   0.000;
  pegged    = true;

  voltVscr  = 2.0;
  sigPinV   = 0.0;
  scrPinV   = pxlVscrY / 2.0;

  return;
}
void   MdlOs::Connect       ( void             ) {
  return;
}
MdlOs *MdlOs::GetInstance   ( Signal *i_sig    ) {
  if(mdOs == NULL)
    mdOs = new MdlOs(i_sig);
  return mdOs;
}

void   MdlOs::OsReBase      ( void             ) {
  double tN;

  tN = (double)sig->GetN();
  if(tN < 1.0) tN = 1.0;
  posT = 0.0;

  SetSmpVpxl(1.0);
  if(smpVscr > tN) {
    SetSmpVscr(tN);
  }
  else {
    SetSmpVscr(GetSmpVscr());
  }
  return;
}


void   MdlOs::GoFirst       ( void             ) {
  SetPosT(0.0);
  return;
}
void   MdlOs::Advance       ( void             ) {
  if(dir == XD_FWD)
    posT += smpVsrd / sig->GetFS();
  else if(dir == XD_REV)
    posT -= smpVsrd / sig->GetFS();
  else { // XD_WHOLE
    posT = 0.0;
    if(sig->GetN() > pxlVscrX)
      dir = XD_FWD;
  }
  SetPosT(posT);
  return;
}
void   MdlOs::GoLast        ( void             ) {
  SetPosN(sig->GetN());
  return;
}


void   MdlOs::SetDirFwd       ( void ) {
  dir = XD_FWD;
  SetPosT(posT);
  return;
}
void   MdlOs::SetDirRev       ( void ) {
  dir = XD_REV;
  SetPosT(posT);
  return;
}
void   MdlOs::SetDirWhole     ( void ) {
  dir = XD_WHOLE;
  SetSmpVsrd(0.0);
  posT = 0.0;
  SetSmpVscr(sig->GetN());
  return;
}

void   MdlOs::SetVoltVscr     ( double i_d ) {
  voltVscr = i_d;
  return;
}
double MdlOs::GetVoltMin             ( void ) {
  double tt;

  tt  = pxlVscrY;
  tt -= scrPinV;   // This is how far the peg is from the bottom (in pixels)
  tt *= voltVscr;  // pxl * volt / scr
  tt /= pxlVscrY;  // volts as if the peg were at zero
  tt  = -1.0 * tt; //  Since the above found how far the bottom of the screen is BELOW the peg
  tt += sigPinV;   //  Compensated for peg offsetting
  return tt;
}
double MdlOs::GetVoltMax             ( void ) {
  double tt;

  tt = scrPinV;    // distance from pin to top of screen (in pixels)
  tt *= voltVscr;  // pxl * volt / scr
  tt /= pxlVscrY;  // volts as if the peg were at zero
  tt += sigPinV;   //  Compensated for peg offsetting

  return tt;
}




void   MdlOs::SetTimVrsh      ( double i_t ) {
  if(i_t <= 0.05)
    i_t = 0.05;
  if(i_t >= 2.0)
    i_t = 2.0;
  timVrsh = i_t;
  fprintf(stdout, "MdlOs::SetTimVrsh timVrsh: %lf\n", timVrsh);fflush(stdout);
  return;
};
void   MdlOs::SetSmpVrsh      ( double i_t ) {
  double tt;
  tt  = i_t;           // smp  per refresh
  tt /= sig->GetFS();  // time per refresh
  SetTimVrsh(tt);
  return;
};

void   MdlOs::SetSrlRto     ( double i_r ) {
  SetTimVsrd(i_r * GetTimVscr());
  return;
}
void   MdlOs::SetPbkRto     ( double i_r ) {
  // eventually grow this to do by holding either tRsh or tStr
  SetTimVsrd(GetTimVrsh() * i_r);
  return;
}

void   MdlOs::SetWidth      ( uint   i_width   ) {
  // eventually grow this to do by holding smpVpxl or smpVscr
  double tt;
  tt = i_width;
  tt  = (double)i_width * GetSmpVpxl();
  pxlVscrX = (double)i_width;
  SetSmpVscr(tt);
  return;
}
void   MdlOs::SetHeight     ( uint   i_height  ) {
  pxlVscrY = i_height;
  scrPinV  = pxlVscrY / 2.0;
  pxlVdiv  = (double)i_height / 10.0;
  return;
}

void   MdlOs::SetTimVpxl(double i_t) {
  double tt;
  tt = i_t;            // time per pixel
  tt *= GetTPvScr(); // time per screen
  tt *= sig->GetFS();  // samples per screen
  smpVscr = tt;
  if(smpVscr <= 0.0)
    smpVscr = 1.0;
  smpVsrd = smpVscr;
  if(smpVscr > (double)(sig->GetN())) {
    smpVscr = (double)(sig->GetN());
    smpVsrd = 0.0;
  }
  fprintf(stdout, "MdlOs::SetTimVpxl smpVscr: %lf\n", smpVscr);fflush(stdout);
  SetPosT(posT);
  return;
}
void   MdlOs::SetTimVdiv(double i_t) {
  double tt;
  tt = i_t;            // time per division
  tt /= GetPxlVdiv();  // time per pixel
  tt *= GetTPvScr(); // time per screen
  tt *= sig->GetFS();  // samples per screen
  smpVscr = tt;
  if(smpVscr <= 0.0)
    smpVscr = 1.0;
  fprintf(stdout, "MdlOs::SetTimVdiv smpVscr: %lf\n", smpVscr);fflush(stdout);
  SetPosT(posT);
  return;
}
void   MdlOs::SetTimVscr(double i_t) {
  double tt;
  tt = i_t;            // time per screen
  tt *= sig->GetFS();  // samples per screen
  SetSmpVscr(tt);
  fprintf(stdout, "MdlOs::SetTimVscr smpVscr: %lf\n", smpVscr);fflush(stdout);
  return;
}

void   MdlOs::SetSmpVpxl( double i_s ) {
  double tt;
  tt  = i_s;            // smp per pixel
  tt *= GetTPvScr();  // smp per screen
  smpVscr = tt;
  if(smpVscr <= 0.0)
    smpVscr = 1.0;
  smpVsrd = smpVscr;
  if(smpVscr > (double)(sig->GetN())) {
    smpVscr = (double)(sig->GetN());
    smpVsrd = 0.0;
  }
  fprintf(stdout, "MdlOs::SetSmpVpxl smpVscr: %lf\n", smpVscr);fflush(stdout);
  SetPosT(posT);
  return;
}
void   MdlOs::SetSmpVdiv( double i_s ) {
  double tt;
  tt  = i_s;            // smp per division
  tt /= GetPxlVdiv();   // smp per pixel
  tt *= GetTPvScr();  // smp per screen
  smpVscr = tt;
  if(smpVscr <= 0.0)
    smpVscr = 1.0;
  fprintf(stdout, "MdlOs::SetSmpVdiv smpVscr: %lf\n", smpVscr);fflush(stdout);
  SetPosT(posT);
  return;
}
void   MdlOs::SetSmpVscr( double i_s ) {
  smpVscr = i_s;
  pegged = false;
  if(smpVscr <= 1.0)
    smpVscr = 1.0;
  if(smpVscr > ((double)(sig->GetN()) - .00001)) {
    smpVscr = (double)(sig->GetN());
    smpVsrd = 0.0;
    pegged = true;
  }
  //if(smpVanaP != NULL) *smpVanaP = smpVscr;
  //fprintf(stdout, "MdlOs::SetSmpVscr smpVscr: %lf\n", smpVscr);fflush(stdout);
  SetPosT(posT);
  return;
}


void   MdlOs::SetTimVsrd(double i_t) {
  double tt;
  tt  = i_t;           // time per stride
  tt *= sig->GetFS();  // samples per stride;
  SetSmpVsrd(tt);
  return;
}
void   MdlOs::SetSmpVsrd(double i_s) {
  smpVsrd = i_s;
  SetPosT(posT);
  return;
}


void   MdlOs::SetPosN       ( double i_N       ) {
  SetPosT((double)i_N / sig->GetFS());
  return;
}
void   MdlOs::SetPosT       ( double i_T       ) {
  double tPosN;
  double tN;     // How many samples in the signal?
  double tR;     // How many samples on the screen?
  double tD;     // How many samples in a stride?
  double tA;     // How many samples for the SpecAn?
  double tWidth; // How many samples to the next fetch posN?
  double tTest;

  posT  = i_T;
  tPosN = GetPosN();
  tN    = (double)sig->GetN();
  tR    = GetSmpVscr();
  tD    = GetSmpVsrd();
  tA = 1;
  if(smpVanaP != NULL) tA    = *smpVanaP;
  if(tN < 1.0) tN = 1.0;
                  tWidth = tA;
  if(tD > tWidth) tWidth = tD;
  if(tR > tWidth) tWidth = tR;
  tTest = tN - tPosN - tWidth - 1.0000001;
  if(tTest <= 0.0) {
    tPosN = tN - tWidth;
    posT = tPosN / sig->GetFS();
    pegged = false;
    if(dir == XD_FWD) {
      pegged = true;
      dir = XD_REV; // WARNING autoreverse
    }
  }
  else
    pegged = false;
  if(posT <= 0.0) {
    posT = 0.0;
    pegged = false;
    if(dir == XD_REV) {
      pegged = true;
      dir = XD_FWD; // WARNING autoreverse
    }
  }
  sig->SetPosFrames((llong)(floor(posT * sig->GetFS())));
  return;
  }

//=======================================================================================================


