// $Id: MdlOs.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : MdlOs.hpp
// Original Author    : duncang
// Creation Date      : Oct 19, 2013
// Copyright          : Copyright © 2013 - 2017 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================
//!<brief An Oscilloscope presents information from a SIGNAL SPACE in the form of a SCREEN SPACE.
/*
The signal and the screen are two SPACES.  There is a TRANSFORM that converts the signal space
  into a sensible screen space to be viewed by a user.  There are various control parameters that allow
  the user to focus in on any sub-section of the signal space that she desires.
TUTORIAL  The screen space is a sampled space, in pixels.  It is quantized in the abcissa variable
            and it is quantized in the ordinate variable.  This is a cartesian graphical data presentation.
          The signal space is a sampled space, quantized in the abcissa.  The ordinate IS NOT quantized
            (to the extent that an IEEE double type is practically representative of a real number as
            opposed to an integer)
          In both spaces, the ordinate is time and the abcissa is representative (ultimately) of air pressure
            given that this scope is for musical signal analysis.
          The job is to take a compact range of the signal space and transform it into the screen space.
            The map is not multiple, it's even affine at that for the O-Scope (as opposed to a log-log plot
            in the SpecAn.  WARNING We might present the vertical as a log signal somehow smoothed, but
            that needs some further analysis.  That would be done in the resampler.
The MdlOs keeps track of the two spaces.  It keeps track of the gain and offset of the non-rotational
  affine transformation.  The transformation is exclusively FROM the signal space TO the screen space.

*/

#ifndef __MDL_OS_HPP_
#define __MDL_OS_HPP_

#include <gtkmm.h>

#include <caes/CaesTypes.hpp>
#include <caes/CaesCallBack.hpp>
#include <caes/AudioFile/Signal.hpp>

#include "../Ctl/CtlMsgDspch.hpp"

class MdlOs {
  private:

  public:
    enum eConst {
      EK_PX_X_MIN =  200,
      EK_PX_X_NOM =  800,
      EK_PX_X_MAX = 1440,
      EK_PX_Y_MIN =  200,
      EK_PX_Y_NOM =  600,
      EK_PX_Y_MAX = 1440,
      EK_MAX_CH   =    4
    };
    enum eLoc {XL_FIRST, XL_MID, XL_LAST, XL_WHOLE};
    enum eDir {XD_FWD, XD_REV, XD_WHOLE};
  private:
                      MdlOs           ( Signal *i_sig );
    virtual          ~MdlOs           ( void        );
  public:
    static  MdlOs    *GetInstance     ( Signal *i_sig );
  private:
//==============================================  Setup  ========================================
            void      BuildEnv        ( void        );
            void      BuildSpace      ( void        );
            void      Connect         ( void        );
  public:
//==============================================  Infrastructure  ===============================
            void      OsReBase        ( void        );
            void      SetHeight       ( uint    i_h );
            uint      GetHeight       ( void        ) { return pxlVscrY                             ;};
            void      SetWidth        ( uint    i_w );
            uint      GetWidth        ( void        ) { return pxlVscrX                             ;};
//==============================================  Horizontal Dynamics  ==========================
            void      GoFirst         ( void        );
            void      Advance         ( void        );
            void      GoLast          ( void        );
            void      SetPosT         ( double  i_T );
            double    GetPosT         ( void        ) { return posT                                 ;};
            void      SetPosN         ( double  i_N );
            double    GetPosN         ( void        ) { return posT * sig->GetFS()                  ;};
            double    GetDurT         ( void        ) { return (double)(sig->GetN()) / sig->GetFS() ;};

            bool      DirIsFwd        ( void ) { return dir == XD_FWD                     ;};
            void      SetDirFwd       ( void );
            bool      DirIsRev        ( void ) { return dir == XD_REV                     ;};
            void      SetDirRev       ( void );
            bool      DirIsWhole      ( void ) { return dir == XD_WHOLE                   ;};
            void      SetDirWhole     ( void );
            bool      GetPegged       ( void ) { return pegged                            ;};

//==============================================  Horizontal Numerics  ==========================
            void      SetSmpVanaP     ( llong *i_p ) { smpVanaP = i_p;   return          ;};
            llong     GetSmpVana      ( void ) { return *smpVanaP                         ;};

            void      SetTimVrsh      ( double i_t );
            double    GetTimVrsh      ( void ) { return timVrsh                           ;};
            void      SetSmpVrsh      ( double i_t );
            double    GetSmpVrsh      ( void ) { return timVrsh * sig->GetFS()            ;};

            void      SetSrlRto       ( double i_r );
            double    GetSrlRto       ( void ) { return smpVsrd / smpVscr  ;};
            void      SetPbkRto       ( double i_r );
            double    GetPbkRto       ( void ) { return timVrsh / smpVscr * sig->GetFS()  ;};

            void      SetTimVpxl      ( double i_t);
            double    GetTimVpxl      ( void ) { return smpVscr / sig->GetFS() / pxlVscrX ;};
            void      SetTimVdiv      ( double i_t );
            double    GetTimVdiv      ( void ) { return smpVscr / sig->GetFS() / pxlVscrX * pxlVdiv      ;};
            void      SetTimVscr      ( double i_t );
            double    GetTimVscr      ( void ) { return smpVscr / sig->GetFS()            ;};

            void      SetSmpVpxl      ( double i_s );
            double    GetSmpVpxl      ( void ) { return smpVscr / pxlVscrX                ;};
            void      SetSmpVdiv      ( double i_s );
            double    GetSmpVdiv      ( void ) { return smpVscr / pxlVscrX * pxlVdiv      ;};
            void      SetSmpVscr      ( double i_s );
            double    GetSmpVscr      ( void ) { return smpVscr                           ;};

            void      SetTimVsrd      ( double i_t );
            double    GetTimVsrd      ( void ) { return smpVsrd / sig->GetFS()            ;};
            void      SetSmpVsrd      ( double i_s );
            double    GetSmpVsrd      ( void ) { return smpVsrd                           ;};

            double    GetPxlVdiv      ( void ) { return pxlVdiv                           ;};
            double    GetPxlVscrX     ( void ) { return pxlVscrX                          ;};

            double    GetPxlVscrY     ( void ) { return pxlVscrY                          ;};

            double    GetPxlMinY      ( void ) { return pxlVscrY                          ;};
            double    GetPxlMaxY      ( void ) { return 0.0                               ;};

//==============================================  Vertical Numerics  ============================
            double    GetVoltVpxl     ( void ) { return voltVscr / pxlVscrY               ;};

            double    GetVoltVscr     ( void ) { return voltVscr                          ;};
            void      SetVoltVscr     ( double i_d );
            double    GetVoltMin      ( void );
            double    GetVoltMax      ( void );


  private:
//==============================================  Horizontal ====================================
            //==  The DrawOScope transforms a signal with a range of [-1 ... +1] into the vertical screen space.
            //      But maybe some day I can reduce math ops by having the resampler do this.
            double           timVrsh;       //!<How often does the user see a new image. Called Refresh to not confuse with a Stride.
            double           smpVsrd;       //!<Samples per Stride X

            uint             pxlVscrX;      //!<Pixels per Screen X
            double           smpVscr;       //!<Samples per Screen X
            llong          *smpVanaP;      //!<How we do striding calculations to know to stop.  How many does the SpecAn expect?
                                            //!<Set in the SpecAn world, needed here when changed.  FIXME Thread Liability.
            double           pxlVdiv;       //!<Always the same x and y


            eDir             dir;           //!<Which direction will the next stride move in.
            double           posT;          //!<The current position in the strm that will yield the next grab (in sec).
            bool             pegged;

//==============================================  Vertical  =====================================
            double           voltVscr;      //!<Screen is nominal +1V to -1V, top to bottom
            double           sigPinV;
            double           scrPinV;

            uint             pxlVscrY;      //!<Pixels per Screen Y

//==============================================  Infrastructure ================================
            Signal          *sig;

    static  MdlOs           *mdOs;           //!<Singleton instance pointer
  };

#endif // __MDL_OS_HPP_
