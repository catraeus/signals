// $Id: CtlPhy.hpp 693 2022-12-28 03:44:39Z duncang $

//=================================================================================================
// Original File Name : CtlPhy.hpp
// Original Author    : duncang
// Creation Date      : Dec 25, 2011
// Copyright          : Copyright © 2011 - 2022 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#ifndef CTLALSAFACILITY_HPP_
#define CTLALSAFACILITY_HPP_

#include <gtkmm.h>
#include "../Arb/CtlArb.hpp"
#include <caes/Alsa/Alsa.hpp>
#include <caes/Alsa/AlsaStreamOut.hpp>

class CtlPhy: public Gtk::Frame {
  public:
                  CtlPhy           (const char *i_label, Alsa *i_ae_Tx, AlsaStreamOut *i_mcAlsaStream, CtlArb *i_vcGenerator);
    virtual      ~CtlPhy           (void);
            void  Build            (void);
            void  Connect          (void);

            void  OnAlsaCardChange (void);
            void  OnAlsaIfcChange  (void);
            void  OnDevTxChanged   (void);
            void  OnFacFmtChanged  (void);
            void  OnFacFSChanged   (void);

  private:
            void  AlsaCardFill     (void);
            void  AlsaIfcFill      (void);
            void  AlsaDevTxFill    (void);
            void  AlsaFmtFill      (void);
            void  AlsaFSFill       (void);

            void  OnTxCloseOpen    (void);
  private:
    Gtk::VBox                   vbx_AudioPort;

    //==============================================
    // Facilities (as opposed to control)
    Gtk::VBox                   vbx_Facility;
    //==============================================
    // Card
    Gtk::HBox                   hbx_FacCard;
    Gtk::Label                 *lbl_FacCard;
    Gtk::ComboBoxText          *cbxt_FacCard;
    sigc::connection            conn_FacCardFill;


    //==============================================
    // Interface
    Gtk::HBox                   hbx_FacIfc;
    Gtk::Label                 *lbl_FacIfc;
    Gtk::ComboBoxText          *cbxt_FacIfc;
    sigc::connection            conn_FacIfcFill;

    //==============================================
    // Device
    Gtk::HBox                   hbx_FacDevTx;
    Gtk::Label                 *lbl_FacDevTx;
    Gtk::ComboBoxText          *cbxt_FacDevTx;
    sigc::connection            conn_FacDevTxFill;
    ullong                      facDevTxDexes[MAX_NAME_LEN];

    ullong                      numDevsTx; // How many did Alsa say were TX able device
    ullong                     *devNos;    // The list of device enumerations down in ALSA that we can TX with
    ullong                     *listTxs;   // The ones in the combo dropdown

    Gtk::HBox                   hbx_PcmSpec;
    Gtk::Label                 *lbl_PcmSpec;
    Gtk::Entry                 *txt_PcmSpec;

    Gtk::HBox                   hbx_Caps1;
    Gtk::HBox                   hbx_Caps2;

    Gtk::Label                 *lbl_CapFmt;
    Gtk::ComboBoxText          *cbxt_CapFmt;
    sigc::connection            conn_CapFmt;

    Gtk::Label                 *lbl_CapChan;
    Gtk::ComboBoxText          *cbxt_CapChan;

    Gtk::Label                 *lbl_CapFS;
    Gtk::ComboBoxText          *cbxt_CapFS;
    sigc::connection            conn_CapFS;

    Gtk::HBox                   hbx_Dummy;
    Gtk::HBox                   hbx_Control;

    Gtk::ToggleButton          *tbtn_TxCloseOpen;
    sigc::connection            conn_TxCloseOpen;

    //==============================================
    // Alsa Facilities
    Alsa                       *theAlsa;
    AlsaStreamOut              *theStream;
    // And the connection to the Generator
    CtlArb                     *vcGenerator;     // derived from a Gtk::VBox.

    bool                        holdoff;
  };

#endif /* CTLALSAFACILITY_HPP_ */
