
// $Id: WinXport.cpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : WinXport.cpp
// Original Author    : duncang
// Creation Date      : Dec 20, 2016
// Copyright          : Copyright © 2016 by Catraeus and Duncan Gray
//
// Description        :
//    A GTKmm Frame to hold start stop time and all that stuff.
//
//=================================================================================================

#include <caes/CaesString.hpp>

#include "WinXport.hpp"

const char WinXport::txtCurrPosPrefix[] = "<span font=\"mono\" size=\"xx-large\" foreground=\"#00ff00\" background=\"#000000\"> ";
const char WinXport::txtCurrPosSuffix[] = " </span>";


       WinXport::WinXport        (Signal *i_sig) {

  BuildEnv        ( i_sig );
  BuildMain       (       );
  BuildTimeSlider (       );
  BuildSetup      (       );
  Connect         (       );

  int posX;
  int posY;
  int sizeX;
  int myX;
  int sizeY;
  Glib::RefPtr<Gdk::Window> rootWin;
  rootWin = this->get_root_window();
  rootWin->get_geometry(posX, posY, sizeX, sizeY);
  show_all();
  myX = this->get_allocated_width();
  hide();
  this->move(sizeX - myX - 40, 40);
  return;
}
       WinXport::~WinXport       (void) {
  return;
}
void   WinXport::BuildEnv        (Signal *i_sig) {
  cp      = CfgParticles ::GetInstance(       );
  ctOsHor = CtlOsHor     ::GetInstance( i_sig );
  ctXp    = CtlXport     ::GetInstance( i_sig );
  mdOs    = MdlOs        ::GetInstance( i_sig );
  ctMd    = CtlMsgDspch  ::GetInstance(       );
  return;
}
void   WinXport::BuildMain       (void) {
  set_title("Transport");
  set_size_request(600, 40);

  set_resizable(false);
  tbXprt = new Gtk::Toolbar();
  tbXprt->set_toolbar_style(Gtk::ToolbarStyle::TOOLBAR_ICONS);
  hbxTbar.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
  uint xbSize;
  xbSize  = cp->pxbf_xprt_start_dim->get_width();
  xbSize += cp->pxbf_xprt_stop_bright->get_width();
  hbxTbar.set_size_request(xbSize, 0);

    tbtnXprtFirst    = new Gtk::ToggleToolButton();
    tbtnXprtPrev     = new Gtk::ToggleToolButton();
    tbtnXprtStop     = new Gtk::ToggleToolButton();
    tbtnXprtStart    = new Gtk::ToggleToolButton();
    tbtnXprtNext     = new Gtk::ToggleToolButton();
    tbtnXprtLast     = new Gtk::ToggleToolButton();
    tbtnXprtWhole    = new Gtk::ToggleToolButton();

    tbtnXprtFirst ->set_stock_id(Gtk::Stock::MEDIA_PREVIOUS );
    tbtnXprtPrev  ->set_stock_id(Gtk::Stock::MEDIA_REWIND   );
    tbtnXprtStop  ->set_stock_id(Gtk::Stock::MEDIA_STOP     );
    tbtnXprtStart ->set_stock_id(Gtk::Stock::MEDIA_PLAY     );
    tbtnXprtNext  ->set_stock_id(Gtk::Stock::MEDIA_FORWARD  );
    tbtnXprtLast  ->set_stock_id(Gtk::Stock::MEDIA_NEXT     );
    tbtnXprtWhole ->set_stock_id(Gtk::Stock::FULLSCREEN     );

    tbtnXprtFirst ->set_active( false );
    tbtnXprtPrev  ->set_active( false );
    tbtnXprtStop  ->set_active( true  );
    tbtnXprtStart ->set_active( false );
    tbtnXprtNext  ->set_active( true  );
    tbtnXprtLast  ->set_active( false );
    tbtnXprtWhole ->set_active( false );

    tbtnXprtFirst ->set_use_action_appearance(false);
    tbtnXprtPrev  ->set_use_action_appearance(false);
    tbtnXprtStop  ->set_use_action_appearance(false);
    tbtnXprtStart ->set_use_action_appearance(false);
    tbtnXprtNext  ->set_use_action_appearance(false);
    tbtnXprtLast  ->set_use_action_appearance(false);
    tbtnXprtWhole ->set_use_action_appearance(false);

    tbXprt->append(*tbtnXprtFirst, sigc::mem_fun(*this, &WinXport::OnFirst ));
    tbXprt->append(*tbtnXprtPrev , sigc::mem_fun(*this, &WinXport::OnPrev  ));
    tbXprt->append(*tbtnXprtStop , sigc::mem_fun(*this, &WinXport::OnStop  ));
    tbXprt->append(*tbtnXprtStart, sigc::mem_fun(*this, &WinXport::OnStart ));
    tbXprt->append(*tbtnXprtNext , sigc::mem_fun(*this, &WinXport::OnNext  ));
    tbXprt->append(*tbtnXprtLast , sigc::mem_fun(*this, &WinXport::OnLast  ));
    tbXprt->append(*tbtnXprtWhole, sigc::mem_fun(*this, &WinXport::OnWhole ));

    lblCurrPosN.set_use_markup(true);
    lblCurrPosN.set_size_request(150,0);
    lblCurrPosT.set_use_markup(true);


  hbxTbar      .pack_start     (*tbXprt,          Gtk::PACK_EXPAND_WIDGET,   0 );
  evxCurrPosN  .add            ( lblCurrPosN                                   );
  hbxTbar      .pack_start     ( evxCurrPosN,     Gtk::PACK_SHRINK,          5 );
  evxCurrPosT  .add            ( lblCurrPosT                                   );
  hbxTbar      .pack_start     ( evxCurrPosT,     Gtk::PACK_SHRINK,          5 );
  vbxMain      .set_orientation(                  Gtk::ORIENTATION_VERTICAL    );
  vbxMain      .pack_start     ( hbxTbar,         Gtk::PACK_SHRINK,          3 );
  vbxMain      .pack_start     ( hbxTimeSlider,   Gtk::PACK_SHRINK,          3 );
                add            ( vbxMain                                       );


  return;
}

void   WinXport::BuildTimeSlider (void) {

  frmTimeSlider  = new Gtk::Frame                        ("Time"                               );
  vbxTimeSlider                        .set_orientation  (         Gtk::ORIENTATION_VERTICAL   );
  hbxTimeNumeric                       .set_orientation  (         Gtk::ORIENTATION_HORIZONTAL );
  hbxSliderMech                        .set_orientation  (         Gtk::ORIENTATION_HORIZONTAL );

  adjTime        =     Gtk::Adjustment::create           (0.0, 0.0, 1.0, 0.01, 0.1, 0.0        );
  adjTime                             ->set_lower        (0.0                                  );
  adjTime                             ->set_upper        (1.0                                  );
  sclTimeSlider  = new Gtk::Scale                        (adjTime, Gtk::ORIENTATION_HORIZONTAL );
  sclTimeSlider                       ->set_digits       (4                                    );

  hbxTimeSlider                        .set_orientation  (         Gtk::ORIENTATION_HORIZONTAL );
  hbxTimeSlider                        .set_size_request (0, 0                                 );

  hbxSliderMech   .pack_start(*sclTimeSlider,    Gtk::PACK_EXPAND_WIDGET, 3 );
  vbxTimeSlider   .pack_start( hbxTimeNumeric,   Gtk::PACK_SHRINK,        3 );
  vbxTimeSlider   .pack_start( hbxSliderMech,    Gtk::PACK_SHRINK,        3 );
  frmTimeSlider  ->add       ( vbxTimeSlider                                );
  hbxTimeSlider   .pack_start(*frmTimeSlider,    Gtk::PACK_EXPAND_WIDGET, 3 );

  adjTime->set_value(0.0);
  return;
  }
void   WinXport::BuildSetup      (void) {
  running       = false;
  sliderHoldOff = false;
  XpTimN(NULL);
  return;
}
void   WinXport::Connect         (void) {

  ctXp->SetParentWin(this);

  evxCurrPosN   . signal_button_release_event().connect(sigc::mem_fun(*ctXp, &CtlXport::OnChangeN   ));
  evxCurrPosT   . signal_button_release_event().connect(sigc::mem_fun(*ctXp, &CtlXport::OnChangeT   ));
  sclTimeSlider ->signal_value_changed       ().connect(sigc::mem_fun(*this, &WinXport::OnTimeSlide ));


        MRU_XpButSet = new CbT<WinXport>();
        MRU_XpButSet->SetCallback(this, &WinXport::XpButSet);
  ctMd->MSU_XpButSet =                         MRU_XpButSet;

        MRU_XpTimN     = new CbT<WinXport>();
        MRU_XpTimN    ->SetCallback(this, &WinXport::XpTimN);
  ctMd->MSU_XpTimN     =                         MRU_XpTimN;
  return;
}



bool   WinXport::XpButSet        (void *i_dummy) {
  uint butSet = *(uint *)i_dummy;
  ctXp->KillButtons();
  tbtnXprtFirst->set_active((butSet & CtlXport::eAct::XA_FIRST) != 0);
  tbtnXprtPrev ->set_active((butSet & CtlXport::eAct::XA_PREV ) != 0);
  tbtnXprtStop ->set_active((butSet & CtlXport::eAct::XA_STOP ) != 0);
  tbtnXprtStart->set_active((butSet & CtlXport::eAct::XA_START) != 0);
  tbtnXprtNext ->set_active((butSet & CtlXport::eAct::XA_NEXT ) != 0);
  tbtnXprtLast ->set_active((butSet & CtlXport::eAct::XA_LAST ) != 0);
  tbtnXprtWhole->set_active((butSet & CtlXport::eAct::XA_WHOLE) != 0);
  ctXp->LiveButtons();
  return false;
}
bool   WinXport::XpTimN          (void *i_dummy) {
  char   a[256];
  char   b[256];
  double N;
  uint i;
  if(sliderHoldOff) return false;
  sliderHoldOff = true;
  N = mdOs->GetPosN();
  sprintf(a, "%'9.2lf", N);
  b[0] = '\0';
  for(i=0; i<(16 - strlen(a)); i++)
    b[i] = ' ';
  b[i] = '\0';
  strcat(b, a);
  strcpy(a, b);
  strcpy(b, txtCurrPosPrefix);
  strcat(b, a);
  strcat(b, txtCurrPosSuffix);
  lblCurrPosN.set_markup(b);

  SecToHMS(a, mdOs->GetPosT(), true);
  strcpy(b, txtCurrPosPrefix);
  strcat(b, a);
  strcat(b, txtCurrPosSuffix);
  lblCurrPosT.set_markup(b);

  N  = mdOs->GetDurT();
  if(N < 1.0e-6) N = 1.0;
  N  = 1.0 / N;
  N *= mdOs->GetPosT();
  adjTime->set_value(N);
  sliderHoldOff = false;
  return false;
}


void   WinXport::OnTimeSlide     (void) {
  double numT;
  if(sliderHoldOff) return;
  numT = sclTimeSlider->get_adjustment()->get_value();
  ctXp->OnTimeSlide(numT);
  return;
  }

