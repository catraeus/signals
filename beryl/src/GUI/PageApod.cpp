// $Id: PageApod.cpp 743 2023-02-28 03:31:29Z duncang $

//=================================================================================================
// Original File Name : WinApod.cpp
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

#include "PageApod.hpp"

     PageApod::PageApod         ( Signal *i_sig ) {
  BuildEnv     ( i_sig );
  BuildMain    (       );
  Setup        (       );
  Connect      (       );
  OnApodRshAll ( NULL  );
}
     PageApod::~PageApod        ( void          ) {
}
void PageApod::BuildEnv         ( Signal *i_sig ) {
  ctWave =     CtlWave      ::GetInstance(i_sig);
  ctApod =     CtlApod      ::GetInstance(i_sig);
  ctMd   =     CtlMsgDspch  ::GetInstance();
  mdApod =     Apodia       ::GetInstance();
  return;
}
void PageApod::BuildMain        ( void                   ) {
  char s[32768];

  set_orientation(Gtk::ORIENTATION_VERTICAL);

  hbxSpec.set_orientation(Gtk::ORIENTATION_HORIZONTAL);

  cbxShape = new Gtk::ComboBoxText();
  cbxShape->set_size_request(150, -1);
  /*FIXME*/ // Depending on the int to enum.
  for(uint i=0; i<mdApod->GetCatalogSize(); i++) {
    mdApod->GetShapeName((Apodia::eShape)i, s);
    cbxShape->append(s);
    }
  cbxShape->set_active_text("Dirichlet"); /* FIXME */ // Pre-known


  lblAlpha = new Gtk::Label("Alpha: ");
  txtAlpha = new Gtk::Entry();
  sprintf(s, "%lf", mdApod->GetAlpha());
  txtAlpha->set_text(s);

  cbAnti = new Gtk::CheckButton("Anti-filter");



  hbxVector.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  hbxVector.set_size_request(-1, 100);

  txtVector_bufr = Gtk::TextBuffer::create();
  txtVector_txtv = new Gtk::TextView(txtVector_bufr);
  txtVector_txtv->set_editable(false); // never editable
  txtVector_txtv->set_border_width(1);
  txtVector_scrl = new Gtk::ScrolledWindow();
  txtVector_scrl->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  txtVector_scrl->set_size_request(300, -1);

  hbxSpec         .pack_start( *cbxShape,        Gtk::PACK_SHRINK,        2 );
  hbxSpec         .pack_start( *lblAlpha,        Gtk::PACK_SHRINK,        2 );
  hbxSpec         .pack_start( *txtAlpha,        Gtk::PACK_SHRINK,        2 );
  hbxSpec         .pack_start( *cbAnti,          Gtk::PACK_SHRINK,        2 );

  txtVector_scrl ->add       ( *txtVector_txtv                              );
  hbxVector       .pack_start( *txtVector_scrl,  Gtk::PACK_SHRINK,        5 );
  hbxVector       .pack_start(  hbxVectorDummy,  Gtk::PACK_SHRINK,        5 );

                   pack_start(  hbxSpec,         Gtk::PACK_SHRINK,        5 );
                   pack_start(  hbxVector,       Gtk::PACK_EXPAND_WIDGET, 5 );
  return;
}
void PageApod::Setup            ( void                   ) {
  actionHoldoff = false;
  return;
}
void PageApod::Connect          ( void                   ) {
  cbxShape   ->signal_changed          ().connect( sigc::mem_fun(*this, &PageApod::OnShape         ) );
  cbAnti     ->signal_toggled          ().connect( sigc::mem_fun(*this, &PageApod::OnAnti          ) );
  txtAlpha   ->signal_activate         ().connect( sigc::mem_fun(*this, &PageApod::AlphaSigAct     ) );
  txtAlpha   ->signal_focus_out_event  ().connect( sigc::mem_fun(*this, &PageApod::AlphaSigFocOut  ) );

        MRU_ApodRshAll = new CbT<PageApod>();
        MRU_ApodRshAll->SetCallback(this, &PageApod::OnApodRshAll);
  ctMd->MSU_ApodRshAll = MRU_ApodRshAll;
  return;
}

void PageApod::OnShape          ( void                   ) {
  if(actionHoldoff) return;
  Apodia::eShape tShape;
  tShape = (Apodia::eShape)cbxShape->get_active_row_number();
  ctApod->SetShape(tShape);
  return;
  }
void PageApod::OnAlpha          ( void                   ) {
  char   s[256];
  double t;

  if(actionHoldoff) return;
  strcpy(s, txtAlpha->get_text().c_str());
  if (!IsDoubleFixed(s))
    t = mdApod->GetAlpha();
  else
    sscanf(s, "%lf", &t);
  ctApod->SetAlpha(t);

  return;
  }
void PageApod::OnAnti           ( void                   ) {
  bool anti;
  if(actionHoldoff) return;
  anti = cbAnti->get_active();
  ctApod->SetAnti(anti);
  return;
  }
bool PageApod::AlphaSigFocOut   ( GdkEventFocus *i_event ) {
  OnAlpha();
  return true;
  }
void PageApod::AlphaSigAct      ( void                   ) {
  OnAlpha();
  return;
  }

bool PageApod::OnApodRshAll     ( void          *i_dummy ) {
  char    ss[32768];
  double  dd;
  double *vec;
  llong   ll;

  actionHoldoff = true;
  //fprintf(stderr, "WinApod::OnApodRshAll()\n");fflush(stderr);

  //==  Alpha
  dd = mdApod->GetAlpha();
  sprintf(ss, "%10.8lf", dd);
  txtAlpha->set_text(ss);
  txtAlpha->set_editable(ctApod->GetAlphaEd());
  txtAlpha->set_sensitive(ctApod->GetAlphaEd());
  //==  Anti
  cbAnti->set_active(ctApod->GetAnti());

  //==  Now the big vector for our viewing pleasure
  txtVector_bufr->set_text("");
    vec = mdApod->GetWindow();
    ll = mdApod->GetN();
    for(llong g = 0; g < ll; g++) {
      dd  = vec[g];
      if(g == 0)
        sprintf(ss, "%9.5e", dd);
      else
        sprintf(ss, "\n%9.5e", dd);
      txtVector_bufr->insert_at_cursor(ss);
    }
  if(ctWave->GetTypeApod() || ctWave->GetTypeApSrc()) {
    cbxShape  ->set_sensitive(true);
  //txtAlpha  ->set_sensitive(true); // has been grayed out above if appropriate, don't trounce that.
    cbAnti    ->set_sensitive(true);
  }
  else {
    cbxShape  ->set_sensitive(false);
    txtAlpha  ->set_sensitive(false);
    cbAnti    ->set_sensitive(false);
  }
  actionHoldoff = false;
  return false;
}
