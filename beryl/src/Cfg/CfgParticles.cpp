
// $Id: CfgParticles.cpp 500 2019-12-15 16:47:28Z duncang $

//=================================================================================================
// Original File Name : CfgParticles.cpp
// Original Author    : duncang
// Creation Date      : Nov 8, 2010
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//
//=================================================================================================

#include "CfgParticles.hpp"
#include <icon/logo_at_048.xpm>
#include <icon/logo_catraeus_048.xpm>
#include <icon/logo_catraeus_button_032.xpm>
#include <icon/op_quit_bright_032.xpm>
#include <icon/op_file_open_bright_032.xpm>
#include <icon/op_help_about_032.xpm>
#include <icon/ana_spec_032.xpm>
#include <icon/ana_scope_032.xpm>
#include <icon/xprt_start_bright_032.xpm>
#include <icon/xprt_start_dim_032.xpm>
#include <icon/xprt_stop_bright_032.xpm>
#include <icon/xprt_stop_dim_032.xpm>

CfgParticles *CfgParticles::cp = NULL;

CfgParticles::CfgParticles()
  : cols_Caes_Iridium   ("#e0e0e0")
  , cols_Caes_Tungsten  ("#c0c0c0")
  , cols_Caes_Carbon    ("#182020")
  , cols_Caes_RedLight  ("#f2ebe6")
  , cols_Caes_RedMid    ("#b06050")
  , cols_Caes_RedDark   ("#301808")
  , cols_Caes_GreenLight("#f2f1df")
  , cols_Caes_GreenDark ("#082008")
  , cols_Caes_BlueLight ("#f2f0fe")
  , cols_Caes_BlueDark  ("#101830")
{
  colr_Caes_Iridium.set(cols_Caes_Iridium);
  colr_Caes_Tungsten.set(cols_Caes_Tungsten);
  colr_Caes_Carbon.set(cols_Caes_Carbon);
  colr_Caes_RedLight.set(cols_Caes_RedLight);
  colr_Caes_RedMid.set(cols_Caes_RedMid);
  colr_Caes_RedDark.set(cols_Caes_RedDark);
  colr_Caes_GreenLight.set(cols_Caes_GreenLight);
  colr_Caes_GreenDark.set(cols_Caes_GreenDark);
  colr_Caes_BlueLight.set(cols_Caes_BlueLight);
  colr_Caes_BlueDark.set(cols_Caes_BlueDark);

  pxbf_logo_at             = Gdk::Pixbuf::create_from_xpm_data(logo_at_048_xpm);
  pxbf_logo_catraeus       = Gdk::Pixbuf::create_from_xpm_data(logo_catraeus_048_xpm);
  pxbf_icon_catraeus       = Gdk::Pixbuf::create_from_xpm_data(logo_catraeus_button_032_xpm);
  pxbf_op_quit_bright      = Gdk::Pixbuf::create_from_xpm_data(op_quit_bright_032_xpm);
  pxbf_op_file_open_bright = Gdk::Pixbuf::create_from_xpm_data(op_file_open_bright_032_xpm);
  pxbf_op_help_about       = Gdk::Pixbuf::create_from_xpm_data(op_help_about_032_xpm);
  pxbf_ana_spec            = Gdk::Pixbuf::create_from_xpm_data(ana_spec_032_xpm);
  pxbf_ana_scope           = Gdk::Pixbuf::create_from_xpm_data(ana_scope_032_xpm);
  pxbf_xprt_start_bright   = Gdk::Pixbuf::create_from_xpm_data(xprt_start_bright_032_xpm);
  pxbf_xprt_start_dim      = Gdk::Pixbuf::create_from_xpm_data(xprt_start_dim_032_xpm);
  pxbf_xprt_stop_bright    = Gdk::Pixbuf::create_from_xpm_data(xprt_stop_bright_032_xpm);
  pxbf_xprt_stop_dim       = Gdk::Pixbuf::create_from_xpm_data(xprt_stop_dim_032_xpm);
  }

CfgParticles::~CfgParticles() {
  }
CfgParticles *CfgParticles::GetInstance(void) {
  if(cp == NULL)
    cp = new CfgParticles();
  return cp;
}

