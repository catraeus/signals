
// $Id: CfgParticles.cpp 763 2023-03-25 01:24:59Z duncang $

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

#include <icon/logo_at_016.xpm>

#include <icon/logo_at_064.xpm>

#include <icon/op_quit_bright_032.xpm>
#include <icon/op_file_open_bright_032.xpm>
#include <icon/op_help_about_032.xpm>


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
  colr_Caes_Iridium    .set( cols_Caes_Iridium    );
  colr_Caes_Tungsten   .set( cols_Caes_Tungsten   );
  colr_Caes_Carbon     .set( cols_Caes_Carbon     );
  colr_Caes_RedLight   .set( cols_Caes_RedLight   );
  colr_Caes_RedMid     .set( cols_Caes_RedMid     );
  colr_Caes_RedDark    .set( cols_Caes_RedDark    );
  colr_Caes_GreenLight .set( cols_Caes_GreenLight );
  colr_Caes_GreenDark  .set( cols_Caes_GreenDark  );
  colr_Caes_BlueLight  .set( cols_Caes_BlueLight  );
  colr_Caes_BlueDark   .set( cols_Caes_BlueDark   );

  // the Pixbuf needs a whole GTK Application environment.  Therefore, this needs
  //   to be called only after a Gtk::Application has been called.
  pxbf_xIconApp            = Gdk::Pixbuf::create_from_xpm_data(logo_at_016_xpm);

  pxbf_xLogoApp            = Gdk::Pixbuf::create_from_xpm_data(logo_at_064_xpm);





  pxbf_op_quit_bright      = Gdk::Pixbuf::create_from_xpm_data(op_quit_bright_032_xpm);
  pxbf_op_file_open_bright = Gdk::Pixbuf::create_from_xpm_data(op_file_open_bright_032_xpm);
  pxbf_op_help_about       = Gdk::Pixbuf::create_from_xpm_data(op_help_about_032_xpm);






}

CfgParticles::~CfgParticles() {
}
CfgParticles *CfgParticles::GetInstance(void) {
  if(cp == NULL)
    cp = new CfgParticles();
  return cp;
}

