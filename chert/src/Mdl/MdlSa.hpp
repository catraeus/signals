// $Id: MdlSa.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : MdlSa.hpp
// Original Author    : duncang
// Creation Date      : Oct 23, 2013
// Copyright          : Copyright © 2013 - 2017 by Catraeus and Duncan Gray
//
//   Description:
//   Spectrum Analyzer model to justify the screen size, signal source and desired display functionality desired by the user.
//     See ScreenGrids.odt in the chert/doc section
//
//=================================================================================================

#ifndef __MDL_SA_HPP_
#define __MDL_SA_HPP_

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
  friend class CtlSaHor;
//  friend class FrmSaHor;
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
    typedef enum eFrqUnt_e {
      EF_F_ABS,    // Is absolute frequency (using the FS to calculate)
      EF_F_RELFS   // Is relative frequency (where 1 sample is 1 t_unit
    } eFrqUnt;
    typedef enum eGainF_e {
      EG_F_GRID,   // Set horizontal gain by Freq/Grid
      EG_F_SPAN    // Set horizontal gain by screen span
    } eGainF;
    typedef enum eAnch_e {
      EA_F_ST,     // Is the start  frequency
      EA_F_CN,     // Is the center frequency
      EA_F_SP      // Is the stop   frequency
    } eAnch;
    typedef enum eFftDft_e {
      EX_F_FFT,    // Don't you hate booleans that don't actually mention what the "not" version is.
      EX_F_DFT     // So I didn't make a bool isDFT (where the FFT is the "obvious" other state.)
    } eFftDt;
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
//==== Analyzer Stuff
             void     SetFS        ( double i_f );
             llong   *GetpTvAna    ( void       ) {                      return &TSmpAna                     ;}; //p meaning pointer, provided to allow the
                                                                         // OScope controller to know when to stop without
                                                                         // having the whole SpecAn in it.  The CtlOs has this model.
             void     SetTvAna     ( llong i_s );
             llong    GetTvAna     ( void       ) {                      return  TSmpAna                     ;};
             void     SetFvAna     ( llong i_f );
             llong    GetFvAna     ( void       ) {                      return  FSmpAna                     ;};
             void     SetFFT       ( void       ) { isFftDft = EX_F_FFT; return                               ;};
             void     SetDFT       ( void       ) { isFftDft = EX_F_DFT; return                               ;};
             bool     GetFFT       ( void       ) {                      return isFftDft == EX_F_FFT          ;};
             bool     GetDFT       ( void       ) {                      return isFftDft == EX_F_DFT          ;};

//==== Frequency  Stuff
             double   GetFPvDiv    ( void       ) {                      return  AScrPxlCount * 0.1              ;};
             void     SetFPvScr    ( double i_p );
             double   GetFPvScr    ( void       ) {                      return  FScrPxlCount                    ;};
             void     SetFLog      ( void       ) { SetFLog(true );      return                              ;};
             void     SetFLin      ( void       ) { SetFLog(false);      return                              ;};
             bool     IsFLog       ( void       ) {                      return  FLogLin                      ;};
             bool     IsFLin       ( void       ) {                      return !FLogLin                      ;};

             void     SetFAnchS    ( void       ) { SetFAnchX(EA_F_ST);  return                              ;};
             void     SetFAnchC    ( void       ) { SetFAnchX(EA_F_CN);  return                              ;};
             void     SetFAnchP    ( void       ) { SetFAnchX(EA_F_SP);  return                              ;};
             bool     GetFAnchX    ( void       ) {                      return Fanch                        ;};
             void     SetFAnchGrid ( bool   i_a ) { anchGrid = i_a;      return                              ;};
             void     SetFCenPos   ( double i_a );
             double   GetFCenPos   ( void       ) {                      return FCenPos                      ;};

             void     SetFStart    ( double i_s );
             double   GetFStart    ( void       ) {                      return FFStart                       ;};
             double   GetFStop     ( void       ) {                      return FFStop                        ;};
             void     SetFSpan     ( double i_s );
             double   GetFSpan     ( void       ) {                      return FFStop - FFStart               ;};
             void     SetFCen      ( double i_c );
             double   GetFCen      ( void       ) {                      return GetFSpan() * 0.5 + GetFStart()  ;};
//==== Amplitude Stuff
             void     SetAPvScr    ( double i_p );
             double   GetAPvScr    ( void       ) {                      return  AScrPxlCount                     ;};

             void     SetALog      ( void       ) { SetALog(true );      return                              ;};
             void     SetAlin      ( void       ) { SetALog(false);      return                              ;};
             bool     IsALog       ( void       ) {                      return  ALogLin                      ;};
             bool     IsALin       ( void       ) {                      return !ALogLin                      ;};
             void     SetAABot     ( double i_v );
             double   GetAABot     ( void       ) {                      return AABot                         ;};
             void     SetAATop     ( double i_v );
             double   GetAATop     ( void       ) {                      return AATop                         ;};
             ullong   GetVrtModeN  ( void       ) {                      return ESAM_COUNT                   ;};
       const char    *GetVrtModeStr( ullong i_n );
  protected:
             void     SetFStop     ( double i_s );

  private:
             void     JustifyN     ( void       );
             void     SetFLog      ( bool   i_l );
             void     SetALog      ( bool   i_l );
             void     SetFAnchX    ( eAnch  i_a );
  public:
  private:
//==== Analyzer Stuff
             llong    TSmpAna;      // Samples in the time domain lead to this spectrum
             llong    TSmpAna_prv;  // Previous value for FFT/DFT transition logic

             eFftDt   isFftDft;     // So we can forcibly ask for sub-ranging start/stop frequency interior locations.

             llong    FSmpAna;      // How many frequencies will we ask the transform to get back to us.
             llong    FSmpAna_prv;  // Previous value for FFT/DFT transition logic

//==== Amplitude Stuff
             bool     ACplx;       // vs. Real - Display forced to pos-only if Real, because of the complex-conjugate thing. Deadhead for now.
             bool     ALogLin;      // vs. Lin - Display vertical is Db based, we won't display that silly log10() vertical scale.  It doesn't ... wait for it ... scale!

             double   AScrPxlCount;
             double   AATop;
             double   AABot;

static const char    *cbxVrtMode[]; // FIXME GUI stuff shouldn't be down here!

             double   FS;
             bool     FLogLin;       // vs. Lin - Display is log frequency, positive-only therefore, essentially start-pinned.

             double   FScrPxlCount; // How many pixels wide is the draw screen supposed to be.

             eFrqUnt  FUnits;        // TODO  Some day the user will be able to work in % of FS as well as absolute frequency.
             eAnch    Fanch;         // What Anchor Mode will the Frequency be bound by?
             bool     anchGrid;      // The anchor and the grid will be the same vertical line.  Frequencies on grid on the axis labels will be relative to anchor.
             double   FGrdScrCount;  // How many lines show up in the image?  Convenience, could be derived at any time.

             double   FFGrdFirst;    // Distance in F   between the FFStart and the immediately next grid.  This is true irrespective of Anchoring.
             double   FPGrdFirst;    // Distance in Pix between the FFStart and the immediately next grid.  This is true irrespective of Anchoring.
             double   FFGrdSpace;    // Grid Spacing in Hertz.  This will be constrained to the ancient and venerable 1/2/5 sometimes
             double   FPGrdSpace;    // Grid Spacing in Pixels

             double   FFStart;       // Start is ancient SpecAn terminology since the "IF Oscillator" would sweep from a start to a stop frequency.
             double   FCenPos;       // And here is that center-anchor location relative to span.  0.0 is stupid since it is at FFStart, likewise 1.0 is at FFStop.
             double   FFCen;         // A bit of a misnomer since it can be pushed to any percentage of span by FCenPos.
             double   FPCen;         // Should always be FScrPxlCount * FCenPos.
             double   FFStop;        // Stop Frequency.  FPStop is actually being called FScrPxlCount



    static   MdlSa   *mdSa;
  };

#endif // __MDL_SA_HPP_

