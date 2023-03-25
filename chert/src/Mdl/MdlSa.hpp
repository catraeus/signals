// $Id: MdlSa.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : MdlSa.hpp
// Original Author    : duncang
// Creation Date      : Oct 23, 2013
// Copyright          : Copyright © 2013 - 2017 by Catraeus and Duncan Gray
//
//!< \brief Spectrum Analyzer model to justify the screen size, signal source and desired display functionality desired by the user.
//
//=================================================================================================

#ifndef __MDL_SA_HPP_
#define __MDL_SA_HPP_
/*! The horizontal guts that the user influences but might not really care about

Division of Labor
-----------------
The controller is the function that marshalls all views against the model.
Only the model persists data.
The model must be rigorously monitored (in design) to be only minimum/sufficient ... as little derived as possible.
The model must minimize the duplicaiton of data.

Model contains
--------------
  top/bottom in amplitude
  dB/Lin in amplitude
  start/stop in frequency
  log/lin in frequency
  Apodization settings
  Number of freq points of the freq transformed space.
  Number of time points of the time-side input. (we aren't an inverse transformer.)
  Number of vertical pixels on the screen
  Number of horizontal pixels on the screen


Nomenclature
------------
  start   -- Lowest freq, at the left end of the screen
  center  -- Center freq, at the equilateral middle of the view screen.  Not relevant in Log
  stop    -- Highest freq, at the right edge of the screen
  span    -- The difference between the right edge and the left edge (Hz or decades, whole number decades please)
  top     -- Highest amplitude, top edge of the view screen
  bottom  -- Lowest amplitude, bottom edge of the view screen

Ranges and enums
-----------
  Source Mode { Real, Complex} (This is fundamentally a vertical spec, but influences what happens here.
  Sweep Mode  { Log, Linear} in Real modes, the lowest freq is 0
  Freq Range mode  ?SweepMode == Linear ... { (start,stop   =SP) | (start,span  =SN) | (start,scale=SK) | (center,span=CN) | (center,scale=CK) }
                   :SweepMode == Log    ... { (start|decades=SD) | (stop|decades=PD) }
  Ampl Mode   { dB, Lin   } in power spectrum modes, the lowest amplitude is 0.
  Ampl Range mode  (top,bot=TB) | (top,scale=TK) | (top,span=TN) | (center,span=CN) | (center,scale=CK) }


There are three sampled domains, the time signal, the frequency signal and the screen dots.

Time Signal is all taken care of in ScopeVert.  Watch out for the end times when the scope display demand is not the same
    length of samples as the freq analysis demand.

Frequency Signal is defined here.  It is the array of values from some number of frequencies.  There are a few problems to solve.
    Apodization needs to be handled here.
    Short sequences use DFT and long sequences use FFT.
       Both DFT and FFT have N time elements generally not exactly displayed over in the scope.  Some
           future revision of chert will highlite the portion of the time display that yields the frequency anlysis.
       DFT demands P analysis points.  All can be in-range for display.
       FFT demands P analysi spoints, P = N, BUT for real input it is redundant in the second half.  So anlaysi sof real inputs
           will generally only display half of the FFT's P points.

The fastest way to analyze a truncated time signal is with an equal number of complex sinusoids from DC to the nyquist frequency.
If it is a pure real input, then the half-spectrum is sufficient, and the negative frequencies will be the complex conjugate
of the positives, else negative frequencies need analysis.

If you ever want frequencies in between these discrete frequencies, the sinc() will do the job.  It's synthetic and meaningless
unless you want a nice picture on the screen.  For that, any other method might be good for interpolation.  Zero-order hold,
straight-line interpolation, pretty much anything but sinc().  HOWEVER, I really hate the jaggedy look in the low frequencies of
a log-f plot, so I might do more there.  I really like low integer odd-order polynomial fits myself.

So the steps will be:
1.  Get the time array.
2.  If the time array is too long, abort. (for now)
3.  Calculate the same N frequency points by either FFT (if 2^N) or by DFT.
4.  If there are more points in F than the screen has, then we need the user to make the decimation choices.
5.  Else if the user wants min-max, smoothed, whatever, we're hozed for now.
6.  Else, the screen will do the straight-line interpolation connect.

Input real vs. complex:
-----------------------
Complex, of course, only if the input has an even number of channels.

Display/settings modes:
-----------------------
isLog, isCentered, isCplx

So, isLog I struggle with ... because ... it is a positive-only thing ... but ... you could flip the complex spectra around
and look at their negatives as positives.  So what are the use cases?
 - near-carrier phase noise.  Is a power-spectrum only, so the negative frequencies fold over, no problem - do log.  Weeeellll
but actually you'd really want to see pos-neg asymmetries, now wouldn't you.  Pos/neg overlay!  Patent it!  Invented
Thurs 2010-10-24 8:05 Central DST Time, US, Van Alstyne TX 75495.
 - coherent-carrier demodulated down to DC (but we have to synthesize the carrier frequency) just doesn't make sense as log.
 - broadband baseband stuff ... audio channels, noise-floor analysis, impulse responses.  Can be log or linear and only makes sense
as Real in the time domain stuff.
 - But damn, what about a really cool filter that has a complex component, Hilbert kind of stuff. Linear or log+flipped.

OK, so that answers it.  I will have a Log with Complex then a Flip and an overlay of flipped/unflipped!  Like I said above
Patent it.
 - Linear -- { (start,center) | (start,stop) | (center,stop) | (start,span) | (center,span) | (stop,span) }
 - Log -- { (start,stop) | (start|decades) | (stop|decades) }

Persistance:
 - Linear --
 - Log --
*/

#include <math.h>

#include <caes/CaesTypes.hpp>
#include <caes/CaesCallBack.hpp>

#include <caes/CaesMath.hpp>

#include "../Ctl/CtlMsgDspch.hpp"

class MdlSa {
  public:
   //      Ampl Range mode  (top,bot=TB) | (top,scale=TK) | (top,span=TN) | (center,span=CN) | (center,scale=CK) }
  enum eSaAmpMode {
    ESAM_TB = 0,
    ESAM_TK = 1,
    ESAM_TN = 2,
    ESAM_CN = 3,
    ESAM_CK = 4,
    ESAM_COUNT = 5
  };
  private:
    enum eConst {
      EK_PXL_X_MIN =     400,
      EK_PXL_X_NOM =    2048,
      EK_PXL_X_MAX =    4096,
      EK_PXL_Y_MIN =     300,
      EK_PXL_Y_NOM =     400,
      EK_PXL_Y_MAX =    4096,
      EK_CH_MAX    =       4,
      EK_AN_MIN    =       4,
      EK_AN_DFT    =    2048,
      EK_AN_MAX    =  262144
    };
  public:
  private:
    static const double C_FREQ_MIN;
    static const double C_FREQ_MAX;
    static const double C_DEC_MIN;
    static const double C_DEC_MAX;
    static const double C_RANGE_Y_NOM;
  private:
                      MdlSa        ( void       );
    virtual          ~MdlSa        ( void       );
  public:
    static   MdlSa   *GetInstance  ( void       );
             double   GetPxlVdivX  ( void       ) {                      return  pxlVscrY * 0.1              ;};
             void     SetPxlVscrX  ( double i_p );
             double   GetPxlVscrX  ( void       ) {                      return  pxlVscrX                    ;};
             llong   *GetSmpVanaP  ( void       ) {                      return &smpVana                     ;}; //P meaning pointer, provided to allow the
                                                                         // OScope controller to know when to stop without
                                                                         // having the whole SpecAn in it.  The CtlOs does have this model.
             void     SetSmpVana   ( llong i_s );
             llong    GetSmpVana   ( void       ) {                      return  smpVana                     ;};
             void     SetFrqVana   ( llong i_f );
             llong    GetFrqVana   ( void       ) {                      return  frqVana                     ;};

             void     JustifyN     ( void       );

             void     SetAvg       ( bool   i_a ) { isAvg = i_a;         return                              ;};
             bool     GetAvg       ( void       ) {                      return  isAvg                       ;};

             void     SetPxlVscrY  ( double i_p );
             double   GetPxlVscrY  ( void       ) {                      return pxlVscrY                     ;};

             void     SetLogY      ( void       ) { SetLogY(true );      return                              ;};
             void     SetLinY      ( void       ) { SetLogY(false);      return                              ;};
             void     SetLogY      ( bool   i_l );
             bool     IsLogY       ( void       ) {                      return  isLogY                      ;};
             bool     IsLinY       ( void       ) {                      return !isLogY                      ;};
             void     SetVmin      ( double i_v );
             double   GetVmin      ( void       ) {                      return vMin                         ;};
             void     SetVmax      ( double i_v );
             double   GetVmax      ( void       ) {                      return vMax                         ;};
             ullong   GetVrtModeN  ( void       ) {                      return ESAM_COUNT                   ;};
       const char    *GetVrtModeStr( ullong i_n );

             void     SetLogX      ( void       ) {SetLogX(true );       return                              ;};
             void     SetLinX      ( void       ) {SetLogX(false);       return                              ;};
             void     SetLogX      ( bool   i_l );
             bool     IsLogX       ( void       ) {                      return  isLogX                      ;};
             bool     IsLinX       ( void       ) {                      return !isLogX                      ;};
             void     SetCentered  ( bool   i_l ) { isCentered = i_l;    return                              ;};
             bool     IsCentered   ( void       ) {                      return isCentered                   ;};
             void     SetSpanned   ( bool   i_l );
             bool     GetSpanned   ( void       );
             void     SetFmin      ( double i_s );
             double   GetFmin      ( void       ) {                      return fMin                         ;};
             void     SetFmax      ( double i_s );
             double   GetFmax      ( void       ) {                      return fMax                         ;};
             void     SetSpan      ( double i_s );
             double   GetSpan      ( void       ) {                      return fMax - fMin                  ;};
             void     SetCenter    ( double i_c );
             double   GetCenter    ( void       ) {                      return GetSpan() * 0.5 + GetFmin()  ;};
  private:
             bool    isCplx;       //!<vs. Real - Display forced to pos-only if Real, because of the complex-conjugate thing. Deadhead for now.
             bool    isLogY;       //!<vs. Lin - Display vertical is Db based, we won't display that silly log10() vertical scale.  It doesn't ... wait for it ... scale!
             bool    isAvg;

             double  pxlVscrY;
             double  vMax;
             double  vMin;

static const char   *cbxVrtMode[];

             bool    isLogX;       //!<vs. Lin - Display is log frequency, positive-only therefore, essentially start-pinned.
             bool    isCentered;   //!<vs. start-span or start-stop - Display is center-pinned, not start-pinned.  Linear only
             bool    isDelNfreq;

             llong   smpVana;      //!<Samples in the time domain lead to this spectrum?
             llong   frqVana;
             llong   smpVanaLast;
             llong   frqVanaLast;
             double  pxlVscrX;

             double  fMin;
             double  fMax;

    static   MdlSa  *mdSa;
  };

#endif // __MDL_SA_HPP_

