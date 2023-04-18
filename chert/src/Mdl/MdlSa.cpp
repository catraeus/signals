// $Id: MdlSa.cpp 511 2020-06-21 17:17:47Z duncang $

//=================================================================================================
// Original File Name : MdlSa.cpp
// Original Author    : duncang
// Creation Date      : Oct 23, 2013
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include "MdlSa.hpp"
#include <stdio.h>
#include <stddef.h>
#include <math.h>

      MdlSa *MdlSa::mdSa = NULL;
//      Ampl Range mode  (top,bot=TB) | (top,scale=TK) | (top,span=TN) | (center,span=CN) | (center,scale=CK) }
const char  *MdlSa::cbxVrtMode[] = {"Top.Bottom", "Top.Scale", "Top.Span", "Center.Span", "Center.Scale"};

const double MdlSa::C_FREQ_MIN     = 1.0e-00;
const double MdlSa::C_FREQ_MAX     = 1.0e+05;
const double MdlSa::C_DEC_MIN      = 1.0e+00;
const double MdlSa::C_DEC_MAX      = 7.0e+00;
const double MdlSa::C_RANGE_Y_NOM  = 1.0e+10;

            MdlSa::MdlSa        ( void        ) {

  isCplx         = false;
  isLogX         = false;
  isLogY         = true;
  pxlVscrX       = EK_PXL_X_NOM;
  pxlVscrY       = EK_PXL_Y_NOM;
  smpVana        = EK_PXL_X_NOM;
  frqVana        = EK_PXL_X_NOM;
  anchX          = EA_F_ST;
  fMin           =     0.0;
  fCen           = 12000.0;
  fMax           = 24000.0;
  vMax           =     1.0;
  vMin           =     1.0 / C_RANGE_Y_NOM;
  isDelNfreq     = false;
  isAvg          = false;
  smpVana        = 800;
  frqVana        = 800;
  smpVanaLast    =   0;
  frqVanaLast    =   0;

  grdVscrX       =  20.0;
  freqVgrdX      =   1.0; // This will be constrained to the ancient and venerable 1/2/5
  pxlVgrdX       = 100.0;
  grdDom         = EF_F_ABS;

//  gak            = 1234;
//if(__sync_bool_compare_and_swap (&gak, 1234, 5678)) {fprintf(stderr, "ho  ho  ho\n" ); fflush(stderr);}
//else                                                {fprintf(stderr, "boo hoo hoo\n"); fflush(stderr);}

}
            MdlSa::~MdlSa       ( void        ) {
  }
MdlSa      *MdlSa::GetInstance  ( void        ) {
  if(mdSa == NULL)
    mdSa = new MdlSa();
  return mdSa;
}

void        MdlSa::SetPxlVscrX  ( double  i_p ) {
  pxlVscrX = i_p;
  return;
}
void        MdlSa::SetPxlVscrY  ( double  i_p ) {
  pxlVscrY = i_p;
  return;
}
void        MdlSa::SetSmpVana   ( llong   i_s ) {
  llong n;
  n = i_s;
  if(n < EK_AN_MIN)
    n = EK_AN_MIN;
  else if(n > EK_AN_DFT)
    n = NextPowTwo(n);
  else if(n > EK_AN_MAX)
    n = EK_AN_MAX;
  smpVana = n;
  fprintf(stderr, "    b: %6Ld    t: %6Ld   tLast: %6Ld    f: %6Ld    fLast: %6Ld\n", n, smpVana, smpVanaLast, frqVana, frqVanaLast); fflush(stderr);
  JustifyN();
  return;
}
void        MdlSa::SetFrqVana   ( llong   i_s ) {
  llong n;
  n = i_s;
  if(n < EK_AN_MIN)
    n = EK_AN_MIN;
  else if(n > EK_AN_DFT)
    n = NextPowTwo(n);
  else if(n > EK_AN_MAX)
    n = EK_AN_MAX;
  frqVana = n;
  fprintf(stderr, "    b: %6Ld    t: %6Ld   tLast: %6Ld    f: %6Ld    fLast: %6Ld\n", n, smpVana, smpVanaLast, frqVana, frqVanaLast); fflush(stderr);
  JustifyN();
  return;
}
void        MdlSa::JustifyN     ( void        ) {
  llong ll = 0;
  enum eLoHi {LO, HI};
  eLoHi wsT, isT, wsF, isF;
  if(smpVana     <= EK_AN_DFT)   isT = LO;  else isT = HI;
  if(smpVanaLast <= EK_AN_DFT)   wsT = LO;  else wsT = HI;
  if(frqVana     <= EK_AN_DFT)   isF = LO;  else isF = HI;
  if(frqVanaLast <= EK_AN_DFT)   wsF = LO;  else wsF = HI;
  // wsT  isT  wsF  IsF   action
  // lo   lo   lo   lo    nothing but accept and move on
  // hi   hi   hi   hi    harmonize to changed one
  // lo   lo   lo   hi    force other upward
  // lo   hi   lo   lo    force other upward
  // hi   lo   hi   hi    force other downward
  // hi   hi   hi   lo    force other downward
  // lo   lo   hi   lo    impossible - was mixed
  // lo   lo   hi   hi    impossible - was mixed
  // lo   hi   hi   hi    impossible - was mixed
  // hi   lo   lo   lo    impossible - was mixed
  // hi   hi   lo   lo    impossible - was mixed
  // hi   hi   lo   hi    impossible - was mixed
  // lo   hi   lo   hi    impossible - both change
  // lo   hi   hi   lo    impossible - both change
  // hi   lo   lo   hi    impossible - both change
  // hi   lo   hi   lo    impossible - both change
  fprintf(stderr, "   c1: %6Ld    t: %6Ld   tLast: %6Ld    f: %6Ld    fLast: %6Ld\n", ll, smpVana, smpVanaLast, frqVana, frqVanaLast); fflush(stderr);
  if     ((isT == LO) && (wsT == LO) && (isF == LO) && (wsF == LO)) { // Everyone was and is staying low
    fprintf(stderr, "ll ");
  }
  else if     ((isT == HI) && (wsT == HI) && (isF == HI) && (wsF == HI)) { // Everyone was and is staying high ... but force unchanged to track changed
    fprintf(stderr, "hh ");
    if(smpVana == smpVanaLast)    smpVana = frqVana;
    else                          frqVana = smpVana;
  }
  else if((isT != isF) && (wsT == wsF)) { // Moving one or the other across the boundary
    fprintf(stderr, "du ");
    if     ((wsT == LO) && (isT == HI))      frqVana = smpVana;
    else if((wsF == LO) && (isF == HI))      smpVana = frqVana;
    else if((wsT == HI) && (isT == LO))      frqVana = EK_AN_DFT;
    else if((wsF == HI) && (isF == LO))      smpVana = EK_AN_DFT;
  }
  else {  //  Impossible cases, just honk to EK_AN_DFT
    fprintf(stderr, "xx ");
    frqVana = EK_AN_DFT;
    smpVana = EK_AN_DFT;
  }
  fprintf(stderr, "c2: %6Ld    t: %6Ld   tLast: %6Ld    f: %6Ld    fLast: %6Ld\n", ll, smpVana, smpVanaLast, frqVana, frqVanaLast); fflush(stderr);
  smpVanaLast = smpVana;
  frqVanaLast = frqVana;
  return;
}
void        MdlSa::SetLogY      ( bool    i_l ) {
  double v;
  llong k;
  if(!i_l) {
    if(isLogY) { // we're changing - we're going to linear.  Take the top and leave it there.  Put the bottom to 0.0
      vMin = 0.0;
    } // the else represents no change
  }
  else {
    if(!isLogY) { // we're changing - we're going to log.  Take the top and make it reasonable even if it's currently negative.  Likewise the bottom
      if(vMax <= 0.0)
        vMax = 1.0;
      v = log10(vMax);
      v = ceil(v - DBL_EPS); // If you're really really close but just over, then be forgiving
      k = (llong)( v + DBL_EPS); // no room for stupids in the number system.
      vMax = pow10((double)k); // will be right on for numbers in the known universe.
      if(vMin <= DBL_EPS) vMin = vMax / C_RANGE_Y_NOM;
      if(vMin >= vMax   ) vMin = vMax / C_RANGE_Y_NOM;
      v = log10(vMin);
      v = floor(v + DBL_EPS); // If you're really really close but just under, then be forgiving
      k = (llong)( v + DBL_EPS); // no room for stupids in the number system.
      vMin = pow10((double)k); // will be right on for numbers in the known universe.
    }
  }
  isLogY = i_l; // a little redundant, given all the above iffing, but not worth anything else.
  return;
}
void        MdlSa::SetVmin      ( double  i_v ) {
  double v;
  llong k;
  if(isLogY) {
    if(i_v >= vMax - DBL_EPS)
      i_v = vMax / C_RANGE_Y_NOM;
    else {
      v = log10(i_v * 0.9999); // arbitrary for now FIXME make this a better studied fixer-upper
      v = floor(v + DBL_EPS); // If you're really really close but just under, then be forgiving
      k = (llong)( v + DBL_EPS); // no room for stupids in the number system.
      vMin = pow10((double)k); // will be right on for numbers in the known universe.
    }
  }
  else {
    if(i_v > vMax - DBL_EPS * 10.0) // another FIXME
      i_v = vMax - 1.0; // and yet another FIXME
  }
  vMin = i_v;
  return;
}
void        MdlSa::SetVmax      ( double  i_v ) {
  double v;

  if(isLogY) {
    if(i_v <= vMin + DBL_EPS)
      i_v = vMax / C_RANGE_Y_NOM;
    else {
      v = log10(i_v);            //Convert to log
      v = ceil(v - DBL_EPS);     //Put it to an integer decade
      vMax = exp10(v);   // will be right on for numbers in the known universe.
    }
  }
  else {
    if(i_v < (vMin + DBL_EPS * 10.0)) // another FIXME
      i_v = vMax + 1.0; // and yet another FIXME
  }
  return;
}
const char *MdlSa::GetVrtModeStr( ullong  i_n ) {
  if(i_n >= ESAM_COUNT) i_n = ESAM_COUNT - 1;
  return cbxVrtMode[i_n];
}

void        MdlSa::SetLogX      ( bool    i_l ) {
  isLogX = i_l;
  if(isLogX) {
    SetFmin(1.0);
    SetFmax(1.0e+5);
  }
  else {
    SetFmin(0.0);
    SetFmax(2.4e+4);
  }
  return;
}
void        MdlSa::SetAnchX     ( eAnch   i_a ) {
  fprintf(stderr, "Way down in the model, the anchor was dropped.\n");fflush(stderr);
  anchX = i_a;
  return;
}
void        MdlSa::SetFmin      ( double  i_f ) {
  double ss;
  if(isLogX) {
    ss = dmax(C_FREQ_MIN, i_f);
    ss = dmin(ss, C_FREQ_MAX / 10.0 );
    ss = dmin(ss, fMax / 10.0 );
    ss = log10(ss);
    ss = floor(ss);
    ss = pow10(ss);
    }
  else {
    ss = dmax(-C_FREQ_MAX, i_f);
    ss = dmin(ss, C_FREQ_MAX - 1.0);
    ss = dmin(ss, fMax - 1.0);
    }
  fMin = ss;
  return;
  }
void        MdlSa::SetFcen      ( double  i_f ) {
  return;
}
void        MdlSa::SetFmax      ( double  i_f ) {
  double ss;
  if(isLogX) {
    ss = dmax(C_FREQ_MIN * 10.0, i_f);
    ss = dmin(ss, C_FREQ_MAX);
    ss = dmax(ss, fMin * 10.0);
    ss = log10(ss);
    ss = floor(ss);
    ss = pow10(ss);
  }
  else {
    ss = dmin(C_FREQ_MAX, i_f);
    ss = dmax(C_FREQ_MIN, i_f);
    ss = dmax(fMin + 1.0, i_f);
    }
  fMax = ss;
  return;
  }
void        MdlSa::SetSpan      ( double  i_span ) {
  return;
  }

void        MdlSa::SetCenter    ( double  i_center ) {
  return;
  }
