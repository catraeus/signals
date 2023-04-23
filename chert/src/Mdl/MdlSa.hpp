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

             void     SetFS        ( double i_f );

             double   GetPxlVdivX  ( void       ) {                      return  pxlVscrY * 0.1              ;};
             double   GetAPxlFirst ( void       ) {                      return  APxlTop                   ;};
             void     SetPxlVscrX  ( double i_p );
             double   GetPxlVscrX  ( void       ) {                      return  FScrPxlCount                    ;};
             llong   *GetSmpVanaP  ( void       ) {                      return &TSmpAna                     ;}; //P meaning pointer, provided to allow the
                                                                         // OScope controller to know when to stop without
                                                                         // having the whole SpecAn in it.  The CtlOs does have this model.
             void     SetSmpVana   ( llong i_s );
             llong    GetSmpVana   ( void       ) {                      return  TSmpAna                     ;};
             void     SetFrqVana   ( llong i_f );
             llong    GetFrqVana   ( void       ) {                      return  FSmpAna                     ;};

             void     JustifyN     ( void       );

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

             void     SetLogF      ( void       ) { SetLogF(true );      return                              ;};
             void     SetLinF      ( void       ) { SetLogF(false);      return                              ;};
             void     SetLogF      ( bool   i_l );
             bool     IsLogF       ( void       ) {                      return  isLogF                      ;};
             bool     IsLinF       ( void       ) {                      return !isLogF                      ;};
             void     SetAnchX     ( eAnch  i_a );
             void     SetAnchS     ( void       ) { SetAnchX(EA_F_ST);   return                              ;};
             void     SetAnchC     ( void       ) { SetAnchX(EA_F_CN);   return                              ;};
             void     SetAnchP     ( void       ) { SetAnchX(EA_F_SP);   return                              ;};
             bool     GetAnchX     ( void       ) {                      return Fanch                        ;};
             void     SetGainF     ( bool   i_l );
             bool     GetGainF     ( void       );
             void     SetFmin      ( double i_s );
             double   GetFmin      ( void       ) {                      return FFStart                       ;};
             void     SetFcen      ( double i_s );
             double   GetFcen      ( void       ) {                      return FFCen                         ;};
             void     SetFmax      ( double i_s );
             double   GetFmax      ( void       ) {                      return FFStop                        ;};
             void     SetSpan      ( double i_s );
             double   GetSpan      ( void       ) {                      return FFStop - FFStart               ;};
             void     SetCenter    ( double i_c );
             double   GetCenter    ( void       ) {                      return GetSpan() * 0.5 + GetFmin()  ;};
  private:
             double   FS;

             llong    TSmpAna;      // Samples in the time domain lead to this spectrum
             llong    FSmpAna;      // How many frequencies will we ask the transform to get back to us.
             llong    TSmpAna_prv;  // Previous value for FFT/DFT transition logic
             llong    FSmpAna_prv;  // Previous value for FFT/DFT transition logic
             eFftDt   isFftDft;     // So we can forcibly ask for sub-ranging start/stop frequency interior locations.

             bool     isCplx;       //!<vs. Real - Display forced to pos-only if Real, because of the complex-conjugate thing. Deadhead for now.
             bool     isLogY;       //!<vs. Lin - Display vertical is Db based, we won't display that silly log10() vertical scale.  It doesn't ... wait for it ... scale!

             double   pxlVscrY;
             double   APxlTop;
             double   vMax;
             double   vMin;

static const char    *cbxVrtMode[];

             bool     isLogF;       //!<vs. Lin - Display is log frequency, positive-only therefore, essentially start-pinned.

             double   FScrPxlCount; // How many pixels wide is the draw screen supposed to be.

             eFrqUnt  FUnits;        // TODO  Some day the user will be able to work in % of FS as well as absolute frequency.
             eAnch    Fanch;         // What Anchor Mode will the Frequency be bound by?

             double   FGrdScrCount;  // How many lines show up in the image?
             bool     gridAnchLock;  // Shall we force the gridding to always be snapped to the anchor position?
             double   FFAncLoc;      // Distance in F   from FFStart      to the (dimmerly drawn) anchor marker.
             double   FPAncLoc;      // Distance in Pix from Screen Left to the (dimmerly drawn) anchor marker.
             double   FFGrdFirst;    // Distance in F   between the FFStart and the immediately next grid.  This is true irrespective of Anchoring.
             double   FPGrdFirst;    // Distance in Pix between the FFStart and the immediately next grid.  This is true irrespective of Anchoring.
             double   FFGrdSpacing;  // Grid Spacing in Hertz.  This will be constrained to the ancient and venerable 1/2/5 sometimes
             double   FPGrdSpacing;  // Grid Spacing in Pixels

             double   FFStart;       // Start is ancient SpecAn terminology since the "IF Oscillator" would sweep from a start to a stop frequency.
             double   FFCen;         // A bit of a misnomer since it can be pushed to any percentage of span by FCenRel.
             double   FPCen;         // Should always be FScrPxlCount * FCenRel.
             double   FCenRel;       // And here is that center-anchor location relative to span.  0.0 is stupid since it is at FFStart, likewise 1.0 is at FFStop.
             double   FFStop;        // Stop Frequency.  FPStop is actually being called FScrPxlCount



    static   MdlSa   *mdSa;
  };

#endif // __MDL_SA_HPP_

