// $Id: FrmSaAp.cpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : FrmSaAp.cpp
// Original Author    : duncang
// Creation Date      : Aug 28, 2013
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include <caes/CaesTypes.hpp>
#include <caes/CaesString.hpp>

#include "FrmSaAp.hpp"

     FrmSaAp::FrmSaAp() {
  BuildEnv();
  BuildMain();
  BuildSetup();
  Connect();
  }
     FrmSaAp::~FrmSaAp() {
  }

void FrmSaAp::BuildEnv (void) {
//  ctOsHor = CtlOsHor   ::GetInstance();
//  sig     = Signal     ::GetInstance();
  apod    = Apodia     ::GetInstance();
  ctMd    = CtlMsgDspch::GetInstance();
  return;
}
void FrmSaAp::BuildSetup(void) {
  //OnShape();
  Apodia::eShape tShape;
  tShape = (Apodia::eShape)cbxShape->get_active_row_number();
  apod->SetShape(tShape); /*FIXME*/ // MAGIC Row Number maps to eShape
  apod->BuildWindow();
  return;
}
void FrmSaAp::BuildMain(void) {
  set_label("Apodization");
  hbxMain.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  cbxShape = new Gtk::ComboBoxText();
  cbxShape->set_size_request(300, -1);
  /*FIXME*/ // The unordered set, the enum, of apodization shapes has been one-to-one associated here with a well ordered
            //   finite supported integer variable.
  for(uint i=0; i<apod->GetCatalogSize(); i++) {
    char s[32768];
    apod->GetShapeName((Apodia::eShape)i, s);
    cbxShape->append(s);
    }
  cbxShape->set_active_text("Dirichlet");

  char s[256];

  lblAlpha = new Gtk::Label("Alpha: ");
  txtAlpha = new Gtk::Entry();
  sprintf(s, "%lf", apod->GetAlpha());
  txtAlpha->set_text(s);

  hbxMain.pack_start(*cbxShape,  Gtk::PACK_SHRINK, 2);
  hbxMain.pack_start(*lblAlpha,  Gtk::PACK_SHRINK, 2);
  hbxMain.pack_start(*txtAlpha,  Gtk::PACK_SHRINK, 2);

  add(hbxMain);

  show_all();
  return;
}
void FrmSaAp::Connect(void) {
  cbxShape->signal_changed().connect( sigc::mem_fun(*this, &FrmSaAp::OnShape) );
  txtAlpha->signal_activate().connect( sigc::mem_fun(*this, &FrmSaAp::AlphaSigAct) );
  txtAlpha->signal_focus_out_event().connect( sigc::mem_fun(*this, &FrmSaAp::AlphaSigFocOut) );
  return;
}
void FrmSaAp::OnShape(void) {
  char   ss[32768];
  double dd;

  Apodia::eShape tShape;
  tShape = (Apodia::eShape)cbxShape->get_active_row_number();
  apod->SetShape(tShape); /*FIXME*/ // MAGIC Row Number maps to eShape
  if(apod->GetAlphaRange() == 0.0) {
    sprintf(ss, "%10.8lf", 0.0);
    txtAlpha->set_text(ss);
    txtAlpha->set_editable(false);
    txtAlpha->set_sensitive(false);
    }
  else {
    dd = apod->GetAlpha();
    sprintf(ss, "%10.8lf", dd);
    txtAlpha->set_sensitive(false);
    txtAlpha->set_text(ss);
    txtAlpha->set_editable(true);
    txtAlpha->set_sensitive(true);
    }
  ExecuteChange();
  return;
  }
void FrmSaAp::ExecuteChange(void) {
  apod->BuildWindow();
  ctMd->CtEm_SaReScale();
  return;
  }
void FrmSaAp::ChangedAlpha(void) {
  char   s[256];
  double t;

  strcpy(s, txtAlpha->get_text().c_str());
  if (!IsDoubleFixed(s))
    t = apod->GetAlpha();
  else
    sscanf(s, "%lf", &t);
  apod->SetAlpha(t);

  sprintf(s, "%10.8lf", t);
  txtAlpha->set_text(s);
  ExecuteChange();
  return;
  }
bool FrmSaAp::AlphaSigFocOut(GdkEventFocus* i_event) {
  ChangedAlpha();
  return true;
  }
void FrmSaAp::AlphaSigAct(void) {
  ChangedAlpha();
  return;
  }
