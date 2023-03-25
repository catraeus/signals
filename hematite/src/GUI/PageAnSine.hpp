
// $Id: PageAnSine.hpp 757 2023-03-25 01:15:02Z duncang $

//=================================================================================================
// Original File Name : PageAnSine.hpp
// Original Author    : duncang
// Creation Date      : Aug 18, 2012
// Copyright          : Copyright © 2011 - 2019 by Catraeus and Duncan Gray
//
// Description        :
//    The page for the Sinusoid Analyzer.
//
/*
Remove DC0, DC1 and DC2 (offset, ramp and parabola) using LMS.
Estimate Carrier Freq, check RMS less than some number. check tilt, check parabola of freq using ZC



 */
//=================================================================================================

#ifndef __PAGE_AN_SINUS_HPP_
#define __PAGE_AN_SINUS_HPP_

#include <gtkmm.h>

#include <caes/CaesTypes.hpp>
#include <caes/CaesCallBack.hpp>

#include "../Ctl/CtlMsgDspch.hpp"

#include <caes/AudioFile/Signal.hpp>
#include <caes/CaesStat.hpp>
#include "../Ana/AnSine.hpp"

class PageAnSine: public Gtk::Box {
  public:
    enum eAmpType {AT_RAW,   AT_DBFS, AT_LINFS, AT_BITS16, AT_BITS24, AT_INVALID };
    enum eAnType  {NT_INDEP, NT_IQ,   NT_CARR,                        NT_INVALID };
    enum eChCh    {CT_CH0,   CT_CH1,                                  CT_INVALID };
                    PageAnSine     ( Signal *i_sigRaw, Signal *i_sigNorm, Signal *i_sigCarr, Signal *i_sigBase, Signal *i_sigDem, AnSine *i_anSine);
    virtual        ~PageAnSine     ( void         );

            void    ClearStats      ( void        );
            void    SetClean        ( void        ) { dirty = false; return       ;};
            void    SetDirty        ( void        ) { dirty = true ; return       ;};
            bool    IsDirty         ( void        ) {                return dirty ;};
  private:
            void    BuildEnv        ( void        );
            void    BuildMain       ( void        );
            void    Connect         ( void        );

            void    OnIndIQ         ( void       );
            void    OnCarrChChoose  ( void       );
            bool    OnSetCarrFreq   ( GdkEventFocus *i_theEvent);
            bool    OnSetAnBW       ( GdkEventFocus *i_theEvent);

            bool    HndlSineVoid   ( void    *   );

            void    ReScale         ( void        );
            void    FillStats       ( void        );

            void    OnEstZerXrs     ( void        );
            void    OnFilter        ( void        );
            void    OnDemod         ( void        );
            void    OnBaseFilt      ( void        );
            void    OnDemDecim      ( void        );

            double  ConvertJitUi    ( llong  i_ch );
            double  ConvertJitSec   ( llong  i_ch );
  public:

  private:
//    Stat                     *R; //!< Think the R language
    Signal                   *sigRaw;
    Signal                   *sigNorm;
    Signal                   *sigCarr;
    Signal                   *sigBase;
    Signal                   *sigDem;
    AnSine                   *anSine;

    bool                      dirty;
    eAnType                   anType;
    eChCh                     iqCh;
    bool                      hasCarr;


//==== One big box to hold everything
    Gtk::Box                  hbxSine;
//==== Vertical #1, control
    Gtk::Box                  vbxCtlOv;
    Gtk::Button              *btCalcEstZerXrs;
    Gtk::Button              *btCalcFilter;
    Gtk::Button              *btCalcDemod;
    Gtk::Button              *btCalcBaseFilt;
    Gtk::Button              *btCalcDemDecim;

    Gtk::Label                lblPrr;
    Gtk::Entry                ebxPrr;

//==== Vertical #2, Ch 0 results
    Gtk::Box                  vbxZer0;
    Gtk::Box                  vbxZer1;
    Gtk::Frame                frmZer0;
    Gtk::Frame                frmZer1;

    Gtk::Label                lblFrq;
    Gtk::Label                lblRmsUi;
    Gtk::Label                lblRmsSec;
    Gtk::Label                lblAmpCar;
    Gtk::Label                lblaPk;
    Gtk::Label                lblaPh;

    Gtk::Box                  hbxZerFrq0;
    Gtk::Entry                ebxZerFrq0;
    Gtk::Box                  hbxZerRmsUi0;
    Gtk::Entry                ebxZerRmsUi0;
    Gtk::Box                  hbxZerRmsSec0;
    Gtk::Entry                ebxZerRmsSec0;
    Gtk::Box                  hbxZerAmpCar0;
    Gtk::Entry                ebxZerAmpCar0;
    Gtk::Box                  hbxZeraPk0;
    Gtk::Entry                ebxZeraPk0;
    Gtk::Box                  hbxZeraPh0;
    Gtk::Entry                ebxZeraPh0;


//==== Vertical #3, Ch 1 Results
    Gtk::Box                  hbxZerFrq1;
    Gtk::Entry                ebxZerFrq1;
    Gtk::Box                  hbxZerRmsUi1;
    Gtk::Entry                ebxZerRmsUi1;
    Gtk::Box                  hbxZerRmsSec1;
    Gtk::Entry                ebxZerRmsSec1;
    Gtk::Box                  hbxZerAmpCar1;
    Gtk::Entry                ebxZerAmpCar1;
    Gtk::Box                  hbxZeraPk1;
    Gtk::Entry                ebxZeraPk1;
    Gtk::Box                  hbxZeraPh1;
    Gtk::Entry                ebxZeraPh1;


//==== Vertical #4, Analysis
    Gtk::Box                  vbxAnSetup;

    Gtk::Frame                frmAnType;
    Gtk::Box                  vbxAnType;

    Gtk::RadioButtonGroup     rbgpAnType;
    Gtk::RadioButton         *rbtAnTypeIndep;
    Gtk::RadioButton         *rbtAnTypeIQ;
    Gtk::RadioButton         *rbtAnTypeCarr;

    Gtk::Box                  hbxAnTypePad;
    Gtk::Frame                frmAnCarr;
    Gtk::Box                  vbxAnCarr;

    Gtk::Box                  hbxAnCarrPad;

    Gtk::Box                  hbxChChoose;
    Gtk::RadioButtonGroup     rbgpChChoose;
    Gtk::RadioButton         *rbtCh0;
    Gtk::RadioButton         *rbtCh1;

    Gtk::Label                lblCarrFreq;
    Gtk::Entry                ebxCarrFreq;
    sigc::connection          evSetCarrFreq;
    Gtk::Label                lblCarrAnBW;
    Gtk::Entry                ebxCarrAnBW;
    sigc::connection          evSetCarrAnBW;


    CtlMsgDspch             *ctMd;

    CbT<PageAnSine>        *HnCbSineVoid;


  };

#endif // __PAGE_AN_SINUS_HPP_
