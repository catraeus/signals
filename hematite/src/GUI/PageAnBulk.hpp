// $Id: PageAnBulk.hpp 748 2023-03-05 21:20:16Z duncang $

//=================================================================================================
// Original File Name : PageAnBulk.hpp
// Original Author    : duncang
// Creation Date      : Aug 18, 2012
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#ifndef __PAGE_AN_BULK_HPP_
#define __PAGE_AN_BULK_HPP_

#include <gtkmm.h>
#include <caes/CaesTypes.hpp>
#include <caes/AudioFile/Signal.hpp>
#include "../Ctl/CtlMsgDspch.hpp"
#include "../Ana/AnBulk.hpp"
#include <caes/CaesCallBack.hpp> // For some strange reason, this being last allows Eclipse to resolve the reference.

class PageAnBulk: public Gtk::Box {
  public:
    enum eNormType {AT_NORM_RMS,  AT_NORM_PEAK,                                                                                              AT_NORM_INVALID };
    enum eAmpType  {AT_AMP_LIN,   AT_AMP_DB,    AT_AMP_BITS16, AT_AMP_BITS24, AT_AMP_BITS32, AT_AMP_BITSL16, AT_AMP_BITSL24, AT_AMP_BITSL32, AT_AMP_INVALID  };
    enum eAnType   {AT_ANA_INDEP, AT_ANA_CARR,                                                                                               AT_ANA_INVALID      };
                    PageAnBulk      ( Signal *i_sigRaw, Signal *i_sigNorm, AnBulk *i_anBulk );
    virtual        ~PageAnBulk      ( void       );
            void    OnCalcStatsRaw  ( void       );
            void    OnDataFlatten   ( void       );
            void    OnReScale       ( void       );
            void    ReFormat        ( void       );
            void    FillStatsRaw    ( void       );
            void    FillStatsFlt    ( void       );
            void    ClearStats      ( void       );
            void    SetClean        ( void       ) { dirty = false ; return        ;};
            void    SetDirty        ( void       ) { dirty = true  ; return        ;};
            bool    IsDirty         ( void       ) {                 return dirty  ;};
            AnBulk *GetAnBulk       ( void       ) {                 return anBulk;};
  private:
            void    BuildEnv        ( void       );
            void    BuildMain       ( void       );
            void    Connect         ( void       );

            bool    HndlBulkVoid    ( void   *   );

            double  ConvertLinAmp   ( double i_v );
  private:
    Signal                   *sigRaw;
    Signal                   *sigFlt;
    AnBulk                   *anBulk;


    bool                      dirty;
    bool                      bulked; // WARNING This is a variable whereas flattened has a check box for storage.
    eNormType                 normType;
    eAmpType                  ampType;
    eAnType                   anType;

//=================================================================================================
//  GUI Stuff

    Gtk::Box                  hbxStatsBulk;

//============== Vertical for Analysis Setup and Action
    Gtk::Box                  vbxAnSetup;
    Gtk::Button              *btAnaRaw;
    Gtk::Button              *btAnaFlatten;
    Gtk::Label                lblCtlPrr;
    Gtk::Entry                ebxCtlPrr;
    Gtk::CheckButton         *ckbIsFlat;



//============== Vertical for Raw DC 0
    Gtk::Frame                frmRaw0;
    Gtk::Box                  vbxRaw0;

    Gtk::Box                  hbxRawDC0;
    Gtk::Label                lblRawDC0;
    Gtk::Entry                ebxRawDC0;
    Gtk::Box                  hbxRawRms0;
    Gtk::Label                lblRawRms0;
    Gtk::Entry                ebxRawRms0;
    Gtk::Box                  hbxRawPkn0;
    Gtk::Label                lblRawPkn0;
    Gtk::Entry                ebxRawPkn0;
    Gtk::Box                  hbxRawOfn0;
    Gtk::Label                lblRawOfn0;
    Gtk::Entry                ebxRawOfn0;
    Gtk::Box                  hbxRawPkp0;
    Gtk::Label                lblRawPkp0;
    Gtk::Entry                ebxRawPkp0;
    Gtk::Box                  hbxRawOfp0;
    Gtk::Label                lblRawOfp0;
    Gtk::Entry                ebxRawOfp0;
    Gtk::Box                  hbxRawPk0;
    Gtk::Label                lblRawPk0;
    Gtk::Entry                ebxRawPk0;

//============== Vertical for Raw DC 1
    Gtk::Frame                frmRaw1;
    Gtk::Box                  vbxRaw1;

    Gtk::Box                  hbxRawDC1;
    Gtk::Label                lblRawDC1;
    Gtk::Entry                ebxRawDC1;
    Gtk::Box                  hbxRawRms1;
    Gtk::Label                lblRawRms1;
    Gtk::Entry                ebxRawRms1;
    Gtk::Box                  hbxRawPkn1;
    Gtk::Label                lblRawPkn1;
    Gtk::Entry                ebxRawPkn1;
    Gtk::Box                  hbxRawOfn1;
    Gtk::Label                lblRawOfn1;
    Gtk::Entry                ebxRawOfn1;
    Gtk::Box                  hbxRawPkp1;
    Gtk::Label                lblRawPkp1;
    Gtk::Entry                ebxRawPkp1;
    Gtk::Box                  hbxRawOfp1;
    Gtk::Label                lblRawOfp1;
    Gtk::Entry                ebxRawOfp1;
    Gtk::Box                  hbxRawPk1;
    Gtk::Label                lblRawPk1;
    Gtk::Entry                ebxRawPk1;

//============== Vertical for Flat DC 0
    Gtk::Frame                frmFlt0;
    Gtk::Box                  vbxFlt0;

    Gtk::Box                  hbxFltDC0;
    Gtk::Label                lblFltDC0;
    Gtk::Entry                ebxFltDC0;
    Gtk::Box                  hbxFltRms0;
    Gtk::Label                lblFltRms0;
    Gtk::Entry                ebxFltRms0;
    Gtk::Box                  hbxFltPkn0;
    Gtk::Label                lblFltPkn0;
    Gtk::Entry                ebxFltPkn0;
    Gtk::Box                  hbxFltOfn0;
    Gtk::Label                lblFltOfn0;
    Gtk::Entry                ebxFltOfn0;
    Gtk::Box                  hbxFltPkp0;
    Gtk::Label                lblFltPkp0;
    Gtk::Entry                ebxFltPkp0;
    Gtk::Box                  hbxFltOfp0;
    Gtk::Label                lblFltOfp0;
    Gtk::Entry                ebxFltOfp0;
    Gtk::Box                  hbxFltPk0;
    Gtk::Label                lblFltPk0;
    Gtk::Entry                ebxFltPk0;

//============== Vertical for Flat DC 1
    Gtk::Frame                frmFlt1;
    Gtk::Box                  vbxFlt1;

    Gtk::Box                  hbxFltDC1;
    Gtk::Label                lblFltDC1;
    Gtk::Entry                ebxFltDC1;
    Gtk::Box                  hbxFltRms1;
    Gtk::Label                lblFltRms1;
    Gtk::Entry                ebxFltRms1;
    Gtk::Box                  hbxFltPkn1;
    Gtk::Label                lblFltPkn1;
    Gtk::Entry                ebxFltPkn1;
    Gtk::Box                  hbxFltOfn1;
    Gtk::Label                lblFltOfn1;
    Gtk::Entry                ebxFltOfn1;
    Gtk::Box                  hbxFltPkp1;
    Gtk::Label                lblFltPkp1;
    Gtk::Entry                ebxFltPkp1;
    Gtk::Box                  hbxFltOfp1;
    Gtk::Label                lblFltOfp1;
    Gtk::Entry                ebxFltOfp1;
    Gtk::Box                  hbxFltPk1;
    Gtk::Label                lblFltPk1;
    Gtk::Entry                ebxFltPk1;

//============== Vertical for Amplitude Presentation Type - Math System
    Gtk::Box                  vbxAmpType;


    Gtk::Frame                frmNormType;
    Gtk::Box                  vbxNormType;
    Gtk::RadioButtonGroup     rbgpNormType;
    Gtk::RadioButton         *rbtNormTypeRms;
    Gtk::RadioButton         *rbtNormTypeFS;



//============== Vertical for Amplitude Presentation Type - Amplitude Type
    Gtk::Box                  vbxNumType;
    Gtk::Frame                frmNumType;
    Gtk::RadioButtonGroup     rbgpNumType;
    Gtk::RadioButton         *rbtNumTypeLin;
    Gtk::RadioButton         *rbtNumTypeDb;
    Gtk::RadioButton         *rbtBits16;
    Gtk::RadioButton         *rbtBits24;
    Gtk::RadioButton         *rbtBits32;
    Gtk::RadioButton         *rbtBitsL16;
    Gtk::RadioButton         *rbtBitsL24;
    Gtk::RadioButton         *rbtBitsL32;

    CtlMsgDspch              *ctMd;

    CbT<PageAnBulk>          *HnCbBulkVoid;


  };

#endif // __PAGE_AN_BULK_HPP_
