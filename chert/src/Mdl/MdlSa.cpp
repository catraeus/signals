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
//      Ampl Range mode             top,bot=TB    top,scale=TK  top,span=TN center,span=CN  center,scale=CK
const char  *MdlSa::cbxVrtMode[] = {"Top.Bottom", "Top.Scale", "Top.Span",  "Center.Span",  "Center.Scale"};

const double MdlSa::C_FREQ_MIN     = 1.0e-00;
const double MdlSa::C_FREQ_MAX     = 1.0e+05;
const double MdlSa::C_DEC_MIN      = 1.0e+00;
const double MdlSa::C_DEC_MAX      = 7.0e+00;
const double MdlSa::C_RANGE_Y_NOM  = 1.0e+10;

      double MdlSa::fEps   = 0.001D;
      double MdlSa::fNyq   = 0.500D;

            MdlSa::MdlSa        ( void        ) {

//==== Analyzer Stuff.
  TSmpAna        = EK_PXL_X_NOM;
  TSmpAna        = 800;
  TSmpAna_prv    =   0;

  isFftDft       = EX_F_DFT;

  FSmpAna        = EK_PXL_X_NOM;
  FSmpAna        = 800;
  FSmpAna_prv    =   0;


//====  Amplitude Stuff
  ACplx           = false;
  ALogLin         = true;
  AATop           =     1.0;
  AABot           =     1.0 / C_RANGE_Y_NOM;
//---- Pixel Domain
  AScrPxlCount    = EK_PXL_Y_NOM;


  FS              =     1.0;
  FLogLin         = false;

  FScrPxlCount    = EK_PXL_X_NOM;

  FUnits          = EF_F_ABS;
  Fanch           = EA_F_ST;
  anchGrid        = false;
  FGrdScrCount    =  20.0;

  FFGrdFirst      =     0.0;
  FPGrdFirst      =     0.0;
  FFGrdSpace      =     1.0; // This will be constrained to the ancient and venerable 1/2/5
  FPGrdSpace      =   100.0;

  FFStart         =      0.0D;
  FFStop          = FS * 0.5D;
  FFSpan          = FFStop - FFStart;
  FCenPos         =      0.5D;
  FFCen           = FFStop       * FCenPos;
  FPCen           = FScrPxlCount * FCenPos;

  return;
}
            MdlSa::~MdlSa       ( void        ) {
  }
MdlSa      *MdlSa::GetInstance  ( void        ) {
  if(mdSa == NULL)
    mdSa = new MdlSa();
  return mdSa;
}

void        MdlSa::SetFS        ( double  i_f ) {
  double oldFS;
  double ratio;
  // Assume that someone else is informing everyone of this catastrophic change.
  // Assume that before we were called, that the FS was validated.
  // IMPORTANT This is called before any refreshes can happen.
  fprintf(stderr, "    MdlSa::SetFS(%lf);\n", i_f);fflush(stderr);
  oldFS   = FS;
  FS      = i_f;
  ratio   = FS / oldFS;
  FFStart *= ratio;
  FFCen   *= ratio;
  FFStop  *= ratio;
  fEps     = FS * 0.00000001D; // FIXME MAGICK this is a fairly small frequency that needs validation
  fNyq     = FS * 0.5D;
  return;
}

void        MdlSa::SetFPvScr    ( double  i_p ) {
  FScrPxlCount = i_p;
  return;
}







//=================================================================================================
//=================================================================================================
//  Amplitude Stuff
//

void        MdlSa::SetAPvScr    ( double  i_p ) {
  AScrPxlCount = i_p;
  return;
}





//=================================================================================================
//=================================================================================================
//====  Analyzer Stuff
void        MdlSa::SetTvAna     ( llong   i_s ) {
  llong n = i_s;
       if(n < EK_AN_MIN)    n = EK_AN_MIN;
  else if(n > EK_AN_DFT)    n = NextPowTwo(n);
  else if(n > EK_AN_MAX)    n = EK_AN_MAX;
  TSmpAna_prv = TSmpAna;
  TSmpAna = n;
//fprintf(stderr, "MdlSa::SetTvAna     b: %6Ld    t: %6Ld   tLast: %6Ld    f: %6Ld    fLast: %6Ld\n", n, TSmpAna, TSmpAna_prv, FSmpAna, FSmpAna_prv); fflush(stderr);
  JustifyN();
  return;
}
void        MdlSa::SetFvAna     ( llong   i_s ) {
  llong n;
  n = i_s;
  if(n < EK_AN_MIN)
    n = EK_AN_MIN;
  else if(n > EK_AN_DFT)
    n = NextPowTwo(n);
  else if(n > EK_AN_MAX)
    n = EK_AN_MAX;
  FSmpAna_prv = FSmpAna;
  FSmpAna = n;
//  fprintf(stderr, "MdlSa::SetFvAna     b: %6Ld    t: %6Ld   tLast: %6Ld    f: %6Ld    fLast: %6Ld\n", n, TSmpAna, TSmpAna_prv, FSmpAna, FSmpAna_prv); fflush(stderr);
  JustifyN();
  return;
}
void        MdlSa::JustifyN     ( void        ) {
//llong ll = 0;
  enum eLoHi {LO, HI};
  eLoHi wsT, isT, wsF, isF;
  if(TSmpAna     <= EK_AN_DFT)   isT = LO;  else isT = HI;
  if(TSmpAna_prv <= EK_AN_DFT)   wsT = LO;  else wsT = HI;
  if(FSmpAna     <= EK_AN_DFT)   isF = LO;  else isF = HI;
  if(FSmpAna_prv <= EK_AN_DFT)   wsF = LO;  else wsF = HI;
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
//  fprintf(stderr, "MdlSa::JustifyN    c1: %6Ld    t: %6Ld   tLast: %6Ld    f: %6Ld    fLast: %6Ld\n", ll, TSmpAna, TSmpAna_prv, FSmpAna, FSmpAna_prv); fflush(stderr);
  if     ((isT == LO) && (wsT == LO) && (isF == LO) && (wsF == LO)) { // Everyone was and is staying low
//    fprintf(stderr, "MdlSa::JustifyN    ll\n");
  }
  else if     ((isT == HI) && (wsT == HI) && (isF == HI) && (wsF == HI)) { // Everyone was and is staying high ... but force unchanged to track changed
//    fprintf(stderr, "hh ");
    if(TSmpAna == TSmpAna_prv)    TSmpAna = FSmpAna;
    else                          FSmpAna = TSmpAna;
  }
  else if((isT != isF) && (wsT == wsF)) { // Moving one or the other across the boundary
//    fprintf(stderr, "MdlSa::JustifyN    du\n");
    if     ((wsT == LO) && (isT == HI))      FSmpAna = TSmpAna;
    else if((wsF == LO) && (isF == HI))      TSmpAna = FSmpAna;
    else if((wsT == HI) && (isT == LO))      FSmpAna = EK_AN_DFT;
    else if((wsF == HI) && (isF == LO))      TSmpAna = EK_AN_DFT;
  }
  else {  //  Impossible cases, just honk to EK_AN_DFT
//    fprintf(stderr, "MdlSa::JustifyN    xx\n");
    FSmpAna = EK_AN_DFT;
    TSmpAna = EK_AN_DFT;
  }
//  fprintf(stderr, "MdlSa::JustifyN    c2: %6Ld    t: %6Ld   tLast: %6Ld    f: %6Ld    fLast: %6Ld\n", ll, TSmpAna, TSmpAna_prv, FSmpAna, FSmpAna_prv); fflush(stderr);
  TSmpAna_prv = TSmpAna;
  FSmpAna_prv = FSmpAna;
  return;
}


//=================================================================================================
//=================================================================================================
//  Amplitude Stuff
//
void        MdlSa::SetALog      ( bool    i_l ) {
  double v;
  llong k;
  if(!i_l) {
    if(ALogLin) { // we're changing - we're going to linear.  Take the top and leave it there.  Put the bottom to 0.0
      AABot = 0.0;
    } // the else represents no change
  }
  else {
    if(!ALogLin) { // we're changing - we're going to log.  Take the top and make it reasonable even if it's currently negative.  Likewise the bottom
      if(AATop <= 0.0)
        AATop = 1.0;
      v = log10(AATop);
      v = ceil(v - DBL_EPS); // If you're really really close but just over, then be forgiving
      k = (llong)( v + DBL_EPS); // no room for stupids in the number system.
      AATop = pow10((double)k); // will be right on for numbers in the known universe.
      if(AABot <= DBL_EPS) AABot = AATop / C_RANGE_Y_NOM;
      if(AABot >= AATop   ) AABot = AATop / C_RANGE_Y_NOM;
      v = log10(AABot);
      v = floor(v + DBL_EPS); // If you're really really close but just under, then be forgiving
      k = (llong)( v + DBL_EPS); // no room for stupids in the number system.
      AABot = pow10((double)k); // will be right on for numbers in the known universe.
    }
  }
  ALogLin = i_l; // a little redundant, given all the above iffing, but not worth anything else.
  return;
}
void        MdlSa::SetAABot     ( double  i_v ) {
  double v;
  llong k;
  if(ALogLin) {
    if(i_v >= AATop - DBL_EPS)
      i_v = AATop / C_RANGE_Y_NOM;
    else {
      v = log10(i_v * 0.9999); // arbitrary for now FIXME make this a better studied fixer-upper
      v = floor(v + DBL_EPS); // If you're really really close but just under, then be forgiving
      k = (llong)( v + DBL_EPS); // no room for stupids in the number system.
      AABot = pow10((double)k); // will be right on for numbers in the known universe.
    }
  }
  else {
    if(i_v > AATop - DBL_EPS * 10.0) // another FIXME
      i_v = AATop - 1.0; // and yet another FIXME
  }
  AABot = i_v;
  return;
}
void        MdlSa::SetAATop     ( double  i_v ) {
  double v;

  if(ALogLin) {
    if(i_v <= AABot + DBL_EPS)
      i_v = AATop / C_RANGE_Y_NOM;
    else {
      v = log10(i_v);            //Convert to log
      v = ceil(v - DBL_EPS);     //Put it to an integer decade
      AATop = exp10(v);   // will be right on for numbers in the known universe.
    }
  }
  else {
    if(i_v < (AABot + DBL_EPS * 10.0)) // another FIXME
      i_v = AATop + 1.0; // and yet another FIXME
  }
  return;
}
const char *MdlSa::GetVrtModeStr( ullong  i_n ) {
  if(i_n >= ESAM_COUNT) i_n = ESAM_COUNT - 1;
  return cbxVrtMode[i_n];
}

//=================================================================================================
//=================================================================================================
//  Frequency Stuff
//
void        MdlSa::SetFLog      ( bool    i_l ) {
  FLogLin = i_l;
  if(FLogLin) { SetFStart(1.0    ); SetFStop(1.0e+5); }
  else        { SetFStart(FFStart); SetFStop(FFStop); }
  return;
}

void        MdlSa::SetFStart    ( double  i_f ) {
  double tSpan;
  double tStart = i_f;
  double tCen;
  double tStop;

  if(FLogLin) { // TODO ... LOTS of decade-wize thinking
    tStart  = dmax  (tStart,  C_FREQ_MIN          );
    tStart  = dmin  (tStart,  C_FREQ_MAX / 10.0   );
    tStart  = dmin  (tStart,  FFStop     / 10.0   );
    tStart  = log10 (tStart);
    tStart  = floor (tStart);
    tStart  = pow10 (tStart);
  }
  else {
    if(tStart < 0.0D)                      // FIXME, when we are not just a real-input spectrum we will want negative frequencies.
      tStart = 0.0D;
    switch (Fanch) {
      case EA_F_ST:                        //==== This case just slews the screen left or right unless stop would become off-screen.
        if(tStart > fNyq - fEps)               // MAGICK FIXME this is a tiny frequency near FFStop, hope it works. IMPORTANT Assume FFStop <= FS;
          tStart = fNyq - fEps;                // Not a pretty picture but hey I can cure ignorant ... I can't cure stupid.
        tSpan = FFStop - FFStart;          // IMPORTANT calc this from old FFStart & FFStop first.
        tStop = tStart + tSpan;            // Make a try at slewing.
        if(tStop > fNyq)                   // Just honk it to Nyqvist and not let the start go higher.
          tStop  = fNyq;
        tSpan = tStop - tStart;
        tCen  = tStart + FCenPos * tSpan; // Keep the absolute FFCen frequency at the relative center location.
                                           // WARNING seems like a good idea at the time.
                                           // Alternative-To would be to change FFCen, but that fails when new FFStart is past old FFCen
        break;                             // IMPORTANT tStart, tCen and tStop all have accurate values
      case EA_F_CN:                        //==== This case spoinks the gain leaving the center where it was.  Maxing out for 0 and Nyqvist. Never changing the center.
        if(tStart > FFCen - fEps)          // Is the user trying to set it past Center.
          tStart = FFCen - fEps;           // This could get ugly.
        tSpan  = FFCen - tStart;           // WARNING IMPORTANT This is NOT actually Span, you'll see in a minute.
        tSpan *= 1.0 / FCenPos;            //   Here it is, real span, look carefully at that math.  IMPORTANT, FCenPos must be greater than fEps too
        tStop  = tStart + tSpan;           //   TADA  Real stop
        if(tStop > fNyq) {                 // Oops, the new start asks for the stop to be past the Nyquist, so we'll have to constrain the requested start .
          tStop  = fNyq;                   // bear with me, This is self documenting math. As opposed to deriving the equations magically with pen and paper then writing down the whole thing here.
          tSpan  = tStop - FFCen;          // Once again, just a temp calc, not the actual span.
          tSpan *= 1.0 / (1.0 - FCenPos);  //   Here it is, real span, look carefully at that math.  IMPORTANT, FCenPos must be greater than fEps too
          tStart = tStop - tSpan;          // So we just didn't let the user make the span so big and corrected their request upward.
        }
        tCen   = FFCen;                    // Yes, just so the fall-through works.
        break;
      case EA_F_SP:                        //==== This case changes gain/span, but we have to decide whether to keep center as screen-relative or absolute freq.  Screen-rel wins the day
        if(tStart > FFStop - fEps)
          tStart = FFStop -fEps;           // Once again, uggles (is that spelled correctly?)
        tStop = FFStop;                    // Just for pass-through
        tSpan = tStop - tStart;
        tCen  = tStart + FCenPos * tSpan; // Keep the absolute FFCen frequency at the relative center location.
        break;
    }
  }
  FFStart = tStart;
  FFCen   = tCen;
  FFStop  = tStop;
  FFSpan  = tSpan;
  return;
}
void        MdlSa::SetFCen      ( double  i_f ) {
  double tSpan;
  double tStart;
  double tCen = i_f;
  double tStop;

  switch (Fanch) {
    case EA_F_ST:                         //==== Slide the gain as needed, BUT stop with the FFCen if fStop goes past fNyq
      tStart = FFStart;
           if(tCen < tStart + fEps)        tCen = tStart + fEps; // First check for ridiculous numbers compared to FFStart and nyquist
      else if(tCen > fNyq   - fEps)        tCen = fNyq   - fEps;
      tSpan  = tCen - tStart;             // Here is that math thing, look elsewhere for clues
      tSpan /= FCenPos;
      tStop  = tStart + tSpan;
      if(tStop > fNyq) {                  // Just honk it to Nyqvist and not let the FFCen go higher.
        tStop  = fNyq;
        tSpan  = tStop - tStart;
        tCen   = tStart + tSpan * FCenPos; // Sorry charlie, you can only get to this tCen to hold the relative and the start ancnor.
      }
      break;                             // IMPORTANT tStart, tCen and tStop all have accurate values
    case EA_F_CN:                        //==== Just slew around BUT stop if asking to have fStart below zero or fStop above fNyq
      tSpan  = FFSpan;
      tStart = tCen - tSpan *        FCenPos ;
      tStop  = tCen + tSpan * (1.0 - FCenPos);
           if(tStart < 0.0D) {           // Is the user trying to get FFStart below zero.
        tStart = 0.0D;
        tStop  = tSpan;
        tCen   = tSpan * FCenPos;
      }
      else if(tStop > fNyq) {            // Likewise trying to get FStop above Nyquist
        tStop  = fNyq;
        tCen   = tStop - tSpan * ( 1.0D - FCenPos);
        tStart = tStop - tSpan;
      }
      break;
    case EA_F_SP:                        //==== This case changes gain/span, But watch for FFStart below 0
      tStop  = FFStop;
      tSpan  = tStop - tCen;
      tSpan /= (1.0D - FCenPos);
      tStart = tStop - tSpan;
      if(tStart < 0.0D)
        tStart = 0.0D;                   // Once again, uggles (is that spelled correctly?)
      tSpan = tStop - tStart;
      tCen  = tStart + FCenPos + tSpan; // Keep the absolute FFCen frequency at the relative center location.
      break;
  }
  FFStart = tStart;
  FFCen   = tCen;
  FFStop  = tStop;
  FFSpan  = tSpan;
  return;
}
void        MdlSa::SetFStop     ( double  i_f ) {
  double tSpan;
  double tStart;
  double tCen;
  double tStop = i_f;

  if(FLogLin) { // TODO ... LOTS of decade-wize thinking
    tStop  = dmax  (tStop,  C_FREQ_MIN * 10.0   );
    tStop  = dmin  (tStop,  C_FREQ_MAX          );
    tStop  = dmin  (tStop,  FFStart    * 10.0   );
    tStop  = log10 (tStop);
    tStop  = floor (tStop);
    tStop  = pow10 (tStop);
  }
  else {
    if(tStop > fNyq)                       // FIXME, when we are not just a real-input spectrum we will want negative frequencies.
      tStop = fNyq;
    switch (Fanch) {
      case EA_F_ST:                        //==== This case changes gain
        tStart = FFStart;                  // Keep start where it is, we will change gain.
        if(tStop < tStart + fEps)          // MAGICK FIXME this is a tiny frequency near zero, hope it works. FIXME Assumes FFStart > 0.0;
          tStop = tStart + fEps;           // Not a pretty picture but hey I can cure ignorant ... I can't cure stupid.
        tSpan = tStop - tStart;            // IMPORTANT calc this from old FFStart & FFStop first.
        tCen  = tStart + FCenPos * tSpan;  // Keep the absolute FFCen frequency at the relative center location.
                                           // WARNING seems like a good idea at the time.
                                           // Alternative-To would be to change FFCen, but that fails when new FFStart is past old FFCen
        break;                             // IMPORTANT tStart, tCen and tStop all have accurate values
      case EA_F_CN:                        //==== This case spoinks the gain leaving the center where it was.  Maxing out for 0 and Nyqvist. Never changing the center.
        if(tStop < FFCen + fEps)           // Is the user trying to set it past Center.
          tStop = FFCen + fEps;            // This could get ugly.
        tCen   = FFCen;                    // Yes, just so the fall-through works.
        tSpan  = tStop - tCen;             // WARNING IMPORTANT This is NOT actually Span, you'll see in a minute.
        tSpan *= 1.0 / (1.0 - FCenPos);    //   Here it is, real span, look carefully at that math.  IMPORTANT, FCenPos must be greater than fEps too
        tStart = tStop - tSpan;            //   TADA  Real start
        if(tStart < 0.0D) {                // Oops, the new stop asks for the start to be below zero, so we'll have to constrain the requested stop .
          tStart = 0.0D;                   // bear with me, This is self documenting math. As opposed to deriving the equations magically with pen and paper then writing down the whole thing here.
          tSpan  = tCen - tStart;          // Once again, just a temp calc, not the actual span.
          tSpan *= 1.0 / FCenPos;          //   Here it is, real span, look carefully at that math.  IMPORTANT, FCenPos must be greater than fEps too
          tStop = tStart + tSpan;          // So we just didn't let the user make the span so big and corrected their request upward.
        }
        break;
      case EA_F_SP:                        //==== This case slews left-right
        tStart = FFStart;                  // Just for pass-through
        if(tStop < fEps)
          tStop =  fEps;                   // Once again, uggles (is that spelled correctly?)
        tSpan  = FFStop - FFStart;
        tStart = tStop  - tSpan;
        if(tStart < 0.0D)
           tStart = 0.0d;
        tSpan = tStop - tStart;
        tCen  = tStart + FCenPos + tSpan; // Keep the absolute FFCen frequency at the relative center location.
        break;
    }
  }
  FFStart = tStart;
  FFCen   = tCen;
  FFStop  = tStop;
  FFSpan  = tSpan;
  return;
  }
void        MdlSa::SetFSpan     ( double  i_f ) {
  return;
}
void        MdlSa::SetFCenPos   ( double  i_r ) {
  double tStart;
  double tStop;
  double tSpan;

  if(i_r < 0.1D)
    i_r = 0.1D;
  else if(i_r > 0.9D)
    i_r = 0.9D;
  FCenPos = i_r;
  switch (Fanch) {
    case EA_F_ST:                           //==== Just think differently.
      FFCen = FFStart + FFSpan * FCenPos;
      break;
    case EA_F_CN:                           //==== Here we slew the image keeping the actual frequency on the screen location.
      tStart = FFCen - FFSpan * FCenPos;
      tStop  = tStart + FFSpan;
      tSpan  = FFSpan;
      if(tStart < 0.0D) {                   // Moved left went past zero, scale appropriately, can only shrink, old FFCen isnt changing, so it isn't in danger.
        tStart = 0.0D;
        tStop  = FFCen / FCenPos;           // Zoink, follow that math I dare you (not that hard)
        tSpan  = tStop - tStart;
      }
      else if(tStop > fNyq) {
        tStop  = fNyq;
        tSpan  = fNyq - FFCen;
        tSpan /= (1.0D - FCenPos);
        tStart = tStop - tSpan;
      }
      FFStart = tStart;
      FFSpan  = tSpan;
      FFStop  = tStop;
      break;
    case EA_F_SP:                        //==== Just think differently.
      FFCen = FFStart + FFSpan * FCenPos;
      break;
  }
  return;
}
