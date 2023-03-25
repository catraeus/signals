// $Id: PageAnBulk.cpp 756 2023-03-25 00:45:33Z duncang $

//=================================================================================================
// Original File Name : PageAnBulk.cpp
// Original Author    : duncang
// Creation Date      : Aug 18, 2012
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//    The one and only
//
//=================================================================================================

#include <math.h>

#include <caes/CaesString.hpp>
#include <caes/AudioFile/Signal.hpp>

#include "PageAnBulk.hpp"
#include "WinMain.hpp"

        PageAnBulk::PageAnBulk         ( Signal *i_sigRaw, Signal *i_sigNorm, AnBulk *i_anBulk )
: sigRaw  ( i_sigRaw  )
, sigFlt  ( i_sigNorm )
, anBulk  ( i_anBulk  ) {
  BuildEnv();
  BuildMain();
  Connect();
  }
        PageAnBulk::~PageAnBulk        ( void        ) {
  }
void    PageAnBulk::ReFormat           ( void        ) {
  eNormType newNormType;
  eAmpType  newAmpType;

  if     (rbtNormTypeRms->get_active())
    newNormType = AT_NORM_RMS;
  else
    newNormType = AT_NORM_PEAK;

  if     (rbtNumTypeLin->get_active())
    newAmpType = AT_AMP_LIN;
  else if(rbtNumTypeDb->get_active())
    newAmpType = AT_AMP_DB;
  else if(rbtBits16->get_active())
    newAmpType = AT_AMP_BITS16;
  else if(rbtBits24->get_active())
    newAmpType = AT_AMP_BITS24;
  else if(rbtBits32->get_active())
    newAmpType = AT_AMP_BITS32;
  else if(rbtBitsL16->get_active())
    newAmpType = AT_AMP_BITSL16;
  else if(rbtBitsL24->get_active())
    newAmpType = AT_AMP_BITSL24;
  else if(rbtBitsL32->get_active())
    newAmpType = AT_AMP_BITSL32;
  else
    newAmpType = AT_AMP_INVALID;

  if((newAmpType == ampType) && (newNormType == normType)) {
    if(!dirty)
      return;
    }
  ampType  = newAmpType;
  normType = newNormType;
  return;
}
void    PageAnBulk::FillStatsRaw       ( void        ) {
  char tStr[256];
  dirty = false;

  if(!bulked) return;

  sprintf(tStr, "%lf", ConvertLinAmp(      anBulk->GetRawM  (0))  );
  ebxRawDC0.set_text(tStr);
  sprintf(tStr, "%lf", ConvertLinAmp(      anBulk->GetRawS  (0))  );
  ebxRawRms0.set_text(tStr);
  sprintf(tStr, "%lf", ConvertLinAmp(      anBulk->GetRawNv (0))  );
  ebxRawPkn0.set_text(tStr);
  IntWithComma       (tStr,                anBulk->GetRawNo (0))   ;
  ebxRawOfn0.set_text(tStr);
  sprintf(tStr, "%lf", ConvertLinAmp(      anBulk->GetRawXv (0))  );
  ebxRawPkp0.set_text(tStr);
  IntWithComma       (tStr,                anBulk->GetRawXo (0))   ;
  ebxRawOfp0.set_text(tStr);
  double bb;
  if(fabs(anBulk->GetRawXv(0)) > fabs(anBulk->GetRawNv(0)))
    bb = fabs(anBulk->GetRawXv(0));
  else
    bb = fabs(anBulk->GetRawNv(0));
  sprintf(tStr, "%lf", ConvertLinAmp(bb));
  ebxRawPk0.set_text(tStr);

  llong chtest;
  chtest = sigRaw->GetCh();
  if(chtest == 2) {
    sprintf(tStr, "%lf", anBulk->GetRawPrr());
    ebxCtlPrr.set_text(tStr);
    sprintf(tStr, "%lf", ConvertLinAmp(      anBulk->GetRawM  (1))  );
    ebxRawDC1.set_text (tStr);
    sprintf(tStr, "%lf", ConvertLinAmp(      anBulk->GetRawS  (1))  );
    ebxRawRms1.set_text(tStr);
    sprintf(tStr, "%lf", ConvertLinAmp(      anBulk->GetRawNv (1))  );
    ebxRawPkn1.set_text(tStr);
    IntWithComma       (tStr,                anBulk->GetRawNo (1))   ;
    ebxRawOfn1.set_text(tStr);
    sprintf(tStr, "%lf", ConvertLinAmp(      anBulk->GetRawXv (1))  );
    ebxRawPkp1.set_text(tStr);
    IntWithComma       (tStr,                anBulk->GetRawXo (1))   ;
    ebxRawOfp1.set_text(tStr);
    double bb;
    if(fabs(anBulk->GetRawXv(1)) > fabs(anBulk->GetRawNv(1)))
      bb = fabs(anBulk->GetRawXv(1));
    else
      bb = fabs(anBulk->GetRawNv(1));
    sprintf(tStr, "%lf", ConvertLinAmp(bb));
    ebxRawPk1.set_text(tStr);
    }
  else {
    ebxCtlPrr.set_text("");
    ebxRawDC1.set_text("");
    ebxRawRms1.set_text("");
    ebxRawPkn1.set_text("");
    ebxRawOfn1.set_text("");
    ebxRawPkp1.set_text("");
    ebxRawOfp1.set_text("");
    ebxRawPk1.set_text("");
    }

  return;
  }
void    PageAnBulk::FillStatsFlt       ( void        ) {
  char tStr[256];
  if(!bulked)                  return;
  if(!ckbIsFlat->get_active()) return;
  dirty = false;

  sprintf(tStr, "%lf", ConvertLinAmp(      anBulk->GetFltM  (0))  );
  ebxFltDC0.set_text(tStr);
  sprintf(tStr, "%lf", ConvertLinAmp(      anBulk->GetFltS  (0))  );
  ebxFltRms0.set_text(tStr);
  sprintf(tStr, "%lf", ConvertLinAmp(      anBulk->GetFltNv (0))  );
  ebxFltPkn0.set_text(tStr);
  IntWithComma       (tStr,                anBulk->GetFltNo (0))   ;
  ebxFltOfn0.set_text(tStr);
  sprintf(tStr, "%lf", ConvertLinAmp(      anBulk->GetFltXv (0))  );
  ebxFltPkp0.set_text(tStr);
  IntWithComma       (tStr,                anBulk->GetFltXo (0))   ;
  ebxFltOfp0.set_text(tStr);
  double bb;
  if(fabs(anBulk->GetFltXv(0)) > fabs(anBulk->GetFltNv(0)))
    bb = fabs(anBulk->GetFltXv(0));
  else
    bb = fabs(anBulk->GetFltNv(0));
  sprintf(tStr, "%lf", ConvertLinAmp(bb));
  ebxFltPk0.set_text(tStr);

  if(sigFlt->GetCh() == 2) {
    sprintf(tStr, "%lf", anBulk->GetFltPrr());
    ebxCtlPrr.set_text(tStr);
    sprintf(tStr, "%lf", ConvertLinAmp(      anBulk->GetFltM  (1))  );
    ebxFltDC1.set_text (tStr);
    sprintf(tStr, "%lf", ConvertLinAmp(      anBulk->GetFltS  (1))  );
    ebxFltRms1.set_text(tStr);
    sprintf(tStr, "%lf", ConvertLinAmp(      anBulk->GetFltNv (1))  );
    ebxFltPkn1.set_text(tStr);
    IntWithComma       (tStr,                anBulk->GetFltNo (1))   ;
    ebxFltOfn1.set_text(tStr);
    sprintf(tStr, "%lf", ConvertLinAmp(      anBulk->GetFltXv (1))  );
    ebxFltPkp1.set_text(tStr);
    IntWithComma       (tStr,                anBulk->GetFltXo (1))   ;
    ebxFltOfp1.set_text(tStr);
    double bb;
    if(fabs(anBulk->GetFltXv(1)) > fabs(anBulk->GetFltNv(1)))
      bb = fabs(anBulk->GetFltXv(1));
    else
      bb = fabs(anBulk->GetFltNv(1));
    sprintf(tStr, "%lf", ConvertLinAmp(bb));
    ebxFltPk1.set_text(tStr);
    }
  else {
    ebxCtlPrr.set_text("");
    ebxFltDC1.set_text("");
    ebxFltRms1.set_text("");
    ebxFltPkn1.set_text("");
    ebxFltOfn1.set_text("");
    ebxFltPkp1.set_text("");
    ebxFltOfp1.set_text("");
    ebxFltPk1.set_text("");
    }

  return;
}
double  PageAnBulk::ConvertLinAmp      ( double  i_v ) {
  i_v = normType == AT_NORM_RMS ? i_v : i_v * sqrt(2.0);
  switch(ampType) {
    case AT_AMP_LIN:
      return i_v;
      break;
    case AT_AMP_DB:
      return 20.0 * log10(fabs(i_v));
      break;
    case AT_AMP_BITS16:
      return i_v * pow(2.0, 15.0);
      break;
    case AT_AMP_BITS24:
      return i_v * pow(2.0, 23.0);
      break;
    case AT_AMP_BITS32:
      return i_v * pow(2.0, 31.0);
      break;
    case AT_AMP_BITSL16:
      return log(abs(i_v) * pow(2.0, 15.0))/log(2.0);
      break;
    case AT_AMP_BITSL24:
      return log(abs(i_v) * pow(2.0, 23.0))/log(2.0);
      break;
    case AT_AMP_BITSL32:
      return log(abs(i_v) * pow(2.0, 31.0))/log(2.0);
      break;
    default:
      return i_v;
      break;
    }
  return 0.0;
  }
void    PageAnBulk::OnCalcStatsRaw     ( void        ) {
  anBulk->CalcRaw();
  if(anBulk->GetValid()) {
    dirty = true;
    bulked = true;
    FillStatsRaw();
    btAnaFlatten->set_sensitive(TRUE);
  }
  return;
  }
void    PageAnBulk::OnDataFlatten      ( void        ) {
  anBulk->CalcNorm();
  if(anBulk->GetValid()) {
    dirty = true;
    ckbIsFlat->set_active(true);
    FillStatsFlt();
    }
  return;
}
void    PageAnBulk::OnReScale          ( void        ) {
  ReFormat();
  FillStatsRaw();
  FillStatsFlt();
  return;
}


bool    PageAnBulk::HndlBulkVoid       ( void   *    ) {
  fprintf(stderr, "PageAnBulk::HndlBulkVoid()\n"); fflush(stderr);
  SetDirty();
  ClearStats();
  return true;
}


void    PageAnBulk::ClearStats         ( void        ) {
  btAnaFlatten->set_sensitive(FALSE);
  ckbIsFlat->set_active(0);
  ReFormat();
  bulked = false;
  if(!dirty)
    return;
  dirty = false;

  ebxRawDC0.set_text("");
  ebxRawRms0.set_text("");
  ebxRawPkn0.set_text("");
  ebxRawOfn0.set_text("");
  ebxRawPkp0.set_text("");
  ebxRawOfp0.set_text("");
  ebxRawPk0.set_text("");

  ebxCtlPrr.set_text("");
  ebxRawDC1.set_text("");
  ebxRawRms1.set_text("");
  ebxRawPkn1.set_text("");
  ebxRawOfn1.set_text("");
  ebxRawPkp1.set_text("");
  ebxRawOfp1.set_text("");
  ebxRawPk1.set_text("");


  ebxFltDC0.set_text("");
  ebxFltRms0.set_text("");
  ebxFltPkn0.set_text("");
  ebxFltOfn0.set_text("");
  ebxFltPkp0.set_text("");
  ebxFltOfp0.set_text("");
  ebxFltPk0.set_text("");

  ebxCtlPrr.set_text("");
  ebxFltDC1.set_text("");
  ebxFltRms1.set_text("");
  ebxFltPkn1.set_text("");
  ebxFltOfn1.set_text("");
  ebxFltPkp1.set_text("");
  ebxFltOfp1.set_text("");
  ebxFltPk1.set_text("");

  return;
  }
void    PageAnBulk::BuildEnv           ( void        ) {
  dirty    = true;
  bulked   = false;
  ampType  = AT_AMP_INVALID;
  normType = AT_NORM_INVALID;
  anType   = AT_ANA_INVALID;
  ctMd     = CtlMsgDspch::GetInstance();
  return;
}
void    PageAnBulk::BuildMain          ( void        ) {

  HnCbBulkVoid = new CbT<PageAnBulk>;

//=================================================================================================
  this            -> set_orientation     ( Gtk::ORIENTATION_VERTICAL        );
  hbxStatsBulk    .  set_orientation     ( Gtk::ORIENTATION_HORIZONTAL      );



//============== Vertical for Analysis Setup and Action
  vbxAnSetup      .  set_orientation     ( Gtk::ORIENTATION_VERTICAL        );

  btAnaRaw        =  new Gtk::Button     ("Analyze Raw",   true             );
  btAnaFlatten    =  new Gtk::Button     ("Flatten",       true             );
  btAnaFlatten->set_sensitive(FALSE);
  lblCtlPrr       .  set_text            ("Pearson's Corr R:"               );
  ebxCtlPrr       .  set_width_chars     (13                                );
  ebxCtlPrr       .  set_editable        (false                             );
  ckbIsFlat       = new Gtk::CheckButton ("Flattened",     false            );
  ckbIsFlat       -> set_state           (Gtk::StateType::STATE_INSENSITIVE );
  ckbIsFlat       -> set_active          (false                             );




//============== Vertical for Raw DC 0
  frmRaw0         .set_label        (     "Channel 0 - Raw"       );
  vbxRaw0         .set_orientation  ( Gtk::ORIENTATION_VERTICAL   );

  hbxRawDC0       .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  lblRawDC0       .set_text         (     "DC:"                   );
  lblRawDC0       .set_width_chars  (  7                          );
  lblRawDC0       .set_alignment    ( Gtk::ALIGN_END              );
  ebxRawDC0       .set_width_chars  ( 13                          );
  ebxRawDC0       .set_editable     ( false                       );

  hbxRawRms0      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  lblRawRms0      .set_text         (     "RMS:"                  );
  lblRawRms0      .set_width_chars  (  7                          );
  lblRawRms0      .set_alignment    ( Gtk::ALIGN_END              );
  ebxRawRms0      .set_width_chars  ( 13                          );
  ebxRawRms0      .set_editable     ( false                       );

  hbxRawPkn0      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  lblRawPkn0      .set_text         (     "Pk N:"                 );
  lblRawPkn0      .set_width_chars  (  7                          );
  lblRawPkn0      .set_alignment    ( Gtk::ALIGN_END              );
  ebxRawPkn0      .set_width_chars  ( 13                          );
  ebxRawPkn0      .set_editable     ( false                       );

  hbxRawOfn0      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  lblRawOfn0      .set_text         (     "Off N:"                );
  lblRawOfn0      .set_width_chars  (  7                          );
  lblRawOfn0      .set_alignment    ( Gtk::ALIGN_END              );
  ebxRawOfn0      .set_width_chars  ( 13                          );
  ebxRawOfn0      .set_editable     ( false                       );

  hbxRawPkp0      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  lblRawPkp0      .set_text         (     "Pk P:"                 );
  lblRawPkp0      .set_width_chars  (  7                          );
  lblRawPkp0      .set_alignment    ( Gtk::ALIGN_END              );
  ebxRawPkp0      .set_width_chars  ( 13                          );
  ebxRawPkp0      .set_editable     ( false                       );

  hbxRawOfp0      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  lblRawOfp0      .set_text         (     "Off P:"                );
  lblRawOfp0      .set_width_chars  (  7                          );
  lblRawOfp0      .set_alignment    ( Gtk::ALIGN_END              );
  ebxRawOfp0      .set_width_chars  ( 13                          );
  ebxRawOfp0      .set_editable     ( false                       );

  hbxRawPk0       .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  lblRawPk0       .set_text         (     "Pk Abs:"               );
  lblRawPk0       .set_width_chars  (  7                          );
  lblRawPk0       .set_alignment    ( Gtk::ALIGN_END              );
  ebxRawPk0       .set_width_chars  ( 13                          );
  ebxRawPk0       .set_editable     ( false                       );




//============== Vertical for Raw DC 1
  frmRaw1         .set_label        (     "Channel 1 - Raw"       );
  vbxRaw1         .set_orientation  ( Gtk::ORIENTATION_VERTICAL   );

  hbxRawDC1       .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxRawDC1       .set_width_chars  (13                           );
  ebxRawDC1       .set_editable     ( false                       );

  hbxRawRms1      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxRawRms1      .set_width_chars  (13                           );
  ebxRawRms1      .set_editable     ( false                       );

  hbxRawPkn1      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxRawPkn1      .set_width_chars  (13                           );
  ebxRawPkn1      .set_editable     ( false                       );

  hbxRawOfn1      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxRawOfn1      .set_width_chars  (13                           );
  ebxRawOfn1      .set_editable     ( false                       );

  hbxRawPkp1      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxRawPkp1      .set_width_chars  (13                           );
  ebxRawPkp1      .set_editable     ( false                       );

  hbxRawOfp1      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxRawOfp1      .set_width_chars  (13                           );
  ebxRawOfp1      .set_editable     ( false                       );

  hbxRawPk1       .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxRawPk1       .set_width_chars  (13                           );
  ebxRawPk1       .set_editable     ( false                       );




//============== Vertical for Flat DC 0
  frmFlt0         .set_label        (     "Channel 0 - Flat"      );
  vbxFlt0         .set_orientation  ( Gtk::ORIENTATION_VERTICAL   );

  hbxFltDC0       .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxFltDC0       .set_width_chars  (13                          );
  ebxFltDC0       .set_editable     ( false                      );

  hbxFltRms0      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxFltRms0      .set_width_chars  (13                          );
  ebxFltRms0      .set_editable     ( false                      );

  hbxFltPkn0      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxFltPkn0      .set_width_chars  (13                          );
  ebxFltPkn0      .set_editable     ( false                      );

  hbxFltOfn0      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxFltOfn0      .set_width_chars  (13                          );
  ebxFltOfn0      .set_editable     ( false                      );

  hbxFltPkp0      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxFltPkp0      .set_width_chars  (13                          );
  ebxFltPkp0      .set_editable     ( false                      );

  hbxFltOfp0      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxFltOfp0      .set_width_chars  (13                          );
  ebxFltOfp0      .set_editable     ( false                      );

  hbxFltPk0       .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxFltPk0       .set_width_chars  (13                          );
  ebxFltPk0       .set_editable     ( false                      );









//============== Vertical for Flat DC 1
  frmFlt1         .set_label        (     "Channel 1 - Flat"      );
  vbxFlt1         .set_orientation  ( Gtk::ORIENTATION_VERTICAL   );

  hbxFltDC1       .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxFltDC1       .set_width_chars  (13                          );
  ebxFltDC1       .set_editable     ( false                      );

  hbxFltRms1      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxFltRms1      .set_width_chars  (13                          );
  ebxFltRms1      .set_editable     ( false                      );

  hbxFltPkn1      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxFltPkn1      .set_width_chars  (13                          );
  ebxFltPkn1      .set_editable     ( false                      );

  hbxFltOfn1      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxFltOfn1      .set_width_chars  (13                          );
  ebxFltOfn1      .set_editable     ( false                      );

  hbxFltPkp1      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxFltPkp1      .set_width_chars  (13                          );
  ebxFltPkp1      .set_editable     ( false                      );

  hbxFltOfp1      .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxFltOfp1      .set_width_chars  (13                          );
  ebxFltOfp1      .set_editable     ( false                      );

  hbxFltPk1       .set_orientation  ( Gtk::ORIENTATION_HORIZONTAL );
  ebxFltPk1       .set_width_chars  (13                          );
  ebxFltPk1       .set_editable     ( false                      );



//============== Vertical for Amplitude Presentation Type




//============== Vertical for Amplitude Presentation Type
  vbxAmpType      .set_orientation       ( Gtk::ORIENTATION_VERTICAL   );

  vbxNormType     .set_orientation       ( Gtk::ORIENTATION_VERTICAL   );
  frmNormType     .set_label             (     "Normalizaton"   );
  rbtNormTypeRms  = new Gtk::RadioButton ("1.0 = RMS"           );
  rbtNormTypeFS   = new Gtk::RadioButton ("1.0 = Sine Peak"     );

  rbgpNormType    = rbtNormTypeRms->get_group();
  rbtNormTypeFS   ->set_group(rbgpNormType);

  vbxNumType      .set_orientation       ( Gtk::ORIENTATION_VERTICAL   );
  frmNumType      .set_label             (     "Number Scale"   );
  rbtNumTypeLin   = new Gtk::RadioButton ("linear"              );
  rbtNumTypeDb    = new Gtk::RadioButton ("dB"                  );
  rbtBits16       = new Gtk::RadioButton ("bits (16)"           );
  rbtBits24       = new Gtk::RadioButton ("bits (24)"           );
  rbtBits32       = new Gtk::RadioButton ("bits (32)"           );
  rbtBitsL16      = new Gtk::RadioButton ("log2 (16)"           );
  rbtBitsL24      = new Gtk::RadioButton ("log2 (24)"           );
  rbtBitsL32      = new Gtk::RadioButton ("log2 (32)"           );

  rbgpNumType = rbtNumTypeLin->get_group();
  rbtNumTypeDb  ->set_group(rbgpNumType);
  rbtBits16    ->set_group(rbgpNumType);
  rbtBits24    ->set_group(rbgpNumType);
  rbtBits32    ->set_group(rbgpNumType);
  rbtBitsL16   ->set_group(rbgpNumType);
  rbtBitsL24   ->set_group(rbgpNumType);
  rbtBitsL32   ->set_group(rbgpNumType);







  this                         ->pack_start   (  hbxStatsBulk        , Gtk::PACK_SHRINK, 3);
    hbxStatsBulk                .pack_start   (  vbxAnSetup          , Gtk::PACK_SHRINK, 3);
      vbxAnSetup                .pack_start   ( *btAnaRaw            , Gtk::PACK_SHRINK, 3);
      vbxAnSetup                .pack_start   ( *btAnaFlatten        , Gtk::PACK_SHRINK, 3);
      vbxAnSetup                .pack_start   ( *ckbIsFlat           , Gtk::PACK_SHRINK, 3);
      vbxAnSetup                .pack_start   (  lblCtlPrr           , Gtk::PACK_SHRINK, 3);
      vbxAnSetup                .pack_start   (  ebxCtlPrr           , Gtk::PACK_SHRINK, 3);
    hbxStatsBulk                .pack_start   (  frmRaw0             , Gtk::PACK_SHRINK, 3);
      frmRaw0                   .add          (  vbxRaw0                                  );
        vbxRaw0                 .pack_start   (  hbxRawDC0           , Gtk::PACK_SHRINK, 3);
          hbxRawDC0             .pack_start   (  lblRawDC0           , Gtk::PACK_SHRINK, 3);
          hbxRawDC0             .pack_start   (  ebxRawDC0           , Gtk::PACK_SHRINK, 3);
        vbxRaw0                 .pack_start   (  hbxRawRms0          , Gtk::PACK_SHRINK, 3);
          hbxRawRms0            .pack_start   (  lblRawRms0          , Gtk::PACK_SHRINK, 3);
          hbxRawRms0            .pack_start   (  ebxRawRms0          , Gtk::PACK_SHRINK, 3);
        vbxRaw0                 .pack_start   (  hbxRawPkn0          , Gtk::PACK_SHRINK, 3);
          hbxRawPkn0            .pack_start   (  lblRawPkn0          , Gtk::PACK_SHRINK, 3);
          hbxRawPkn0            .pack_start   (  ebxRawPkn0          , Gtk::PACK_SHRINK, 3);
        vbxRaw0                 .pack_start   (  hbxRawOfn0          , Gtk::PACK_SHRINK, 3);
          hbxRawOfn0            .pack_start   (  lblRawOfn0          , Gtk::PACK_SHRINK, 3);
          hbxRawOfn0            .pack_start   (  ebxRawOfn0          , Gtk::PACK_SHRINK, 3);
        vbxRaw0                 .pack_start   (  hbxRawPkp0          , Gtk::PACK_SHRINK, 3);
          hbxRawPkp0            .pack_start   (  lblRawPkp0          , Gtk::PACK_SHRINK, 3);
          hbxRawPkp0            .pack_start   (  ebxRawPkp0          , Gtk::PACK_SHRINK, 3);
        vbxRaw0                 .pack_start   (  hbxRawOfp0          , Gtk::PACK_SHRINK, 3);
          hbxRawOfp0            .pack_start   (  lblRawOfp0          , Gtk::PACK_SHRINK, 3);
          hbxRawOfp0            .pack_start   (  ebxRawOfp0          , Gtk::PACK_SHRINK, 3);
        vbxRaw0                 .pack_start   (  hbxRawPk0           , Gtk::PACK_SHRINK, 3);
          hbxRawPk0             .pack_start   (  lblRawPk0           , Gtk::PACK_SHRINK, 3);
          hbxRawPk0             .pack_start   (  ebxRawPk0           , Gtk::PACK_SHRINK, 3);
    hbxStatsBulk                .pack_start   (  frmRaw1             , Gtk::PACK_SHRINK, 3);
      frmRaw1                   .add          (  vbxRaw1                                 );
        vbxRaw1                 .pack_start   (  hbxRawDC1           , Gtk::PACK_SHRINK, 3);
          hbxRawDC1             .pack_start   (  ebxRawDC1           , Gtk::PACK_SHRINK, 3);
        vbxRaw1                 .pack_start   (  hbxRawRms1          , Gtk::PACK_SHRINK, 3);
          hbxRawRms1            .pack_start   (  ebxRawRms1          , Gtk::PACK_SHRINK, 3);
        vbxRaw1                 .pack_start   (  hbxRawPkn1          , Gtk::PACK_SHRINK, 3);
          hbxRawPkn1            .pack_start   (  ebxRawPkn1          , Gtk::PACK_SHRINK, 3);
        vbxRaw1                 .pack_start   (  hbxRawOfn1          , Gtk::PACK_SHRINK, 3);
          hbxRawOfn1            .pack_start   (  ebxRawOfn1          , Gtk::PACK_SHRINK, 3);
        vbxRaw1                 .pack_start   (  hbxRawPkp1          , Gtk::PACK_SHRINK, 3);
          hbxRawPkp1            .pack_start   (  ebxRawPkp1          , Gtk::PACK_SHRINK, 3);
        vbxRaw1                 .pack_start   (  hbxRawOfp1          , Gtk::PACK_SHRINK, 3);
          hbxRawOfp1            .pack_start   (  ebxRawOfp1          , Gtk::PACK_SHRINK, 3);
        vbxRaw1                 .pack_start   (  hbxRawPk1           , Gtk::PACK_SHRINK, 3);
          hbxRawPk1             .pack_start   (  ebxRawPk1           , Gtk::PACK_SHRINK, 3);
    hbxStatsBulk                .pack_start   (  frmFlt0             , Gtk::PACK_SHRINK, 3);
      frmFlt0                   .add          (  vbxFlt0                                 );
        vbxFlt0                 .pack_start   (  hbxFltDC0           , Gtk::PACK_SHRINK, 3);
          hbxFltDC0             .pack_start   (  ebxFltDC0           , Gtk::PACK_SHRINK, 3);
        vbxFlt0                 .pack_start   (  hbxFltRms0          , Gtk::PACK_SHRINK, 3);
          hbxFltRms0            .pack_start   (  ebxFltRms0          , Gtk::PACK_SHRINK, 3);
        vbxFlt0                 .pack_start   (  hbxFltPkn0          , Gtk::PACK_SHRINK, 3);
          hbxFltPkn0            .pack_start   (  ebxFltPkn0          , Gtk::PACK_SHRINK, 3);
        vbxFlt0                 .pack_start   (  hbxFltOfn0          , Gtk::PACK_SHRINK, 3);
          hbxFltOfn0            .pack_start   (  ebxFltOfn0          , Gtk::PACK_SHRINK, 3);
        vbxFlt0                 .pack_start   (  hbxFltPkp0          , Gtk::PACK_SHRINK, 3);
          hbxFltPkp0            .pack_start   (  ebxFltPkp0          , Gtk::PACK_SHRINK, 3);
        vbxFlt0                 .pack_start   (  hbxFltOfp0          , Gtk::PACK_SHRINK, 3);
          hbxFltOfp0            .pack_start   (  ebxFltOfp0          , Gtk::PACK_SHRINK, 3);
        vbxFlt0                 .pack_start   (  hbxFltPk0           , Gtk::PACK_SHRINK, 3);
          hbxFltPk0             .pack_start   (  ebxFltPk0           , Gtk::PACK_SHRINK, 3);
    hbxStatsBulk                .pack_start   (  frmFlt1             , Gtk::PACK_SHRINK, 3);
      frmFlt1                   .add          (  vbxFlt1                                 );
        vbxFlt1                 .pack_start   (  hbxFltDC1           , Gtk::PACK_SHRINK, 3);
          hbxFltDC1             .pack_start   (  ebxFltDC1           , Gtk::PACK_SHRINK, 3);
        vbxFlt1                 .pack_start   (  hbxFltRms1          , Gtk::PACK_SHRINK, 3);
          hbxFltRms1            .pack_start   (  ebxFltRms1          , Gtk::PACK_SHRINK, 3);
        vbxFlt1                 .pack_start   (  hbxFltPkn1          , Gtk::PACK_SHRINK, 3);
          hbxFltPkn1            .pack_start   (  ebxFltPkn1          , Gtk::PACK_SHRINK, 3);
        vbxFlt1                 .pack_start   (  hbxFltOfn1          , Gtk::PACK_SHRINK, 3);
          hbxFltOfn1            .pack_start   (  ebxFltOfn1          , Gtk::PACK_SHRINK, 3);
        vbxFlt1                 .pack_start   (  hbxFltPkp1          , Gtk::PACK_SHRINK, 3);
          hbxFltPkp1            .pack_start   (  ebxFltPkp1          , Gtk::PACK_SHRINK, 3);
        vbxFlt1                 .pack_start   (  hbxFltOfp1          , Gtk::PACK_SHRINK, 3);
          hbxFltOfp1            .pack_start   (  ebxFltOfp1          , Gtk::PACK_SHRINK, 3);
        vbxFlt1                 .pack_start   (  hbxFltPk1           , Gtk::PACK_SHRINK, 3);
          hbxFltPk1             .pack_start   (  ebxFltPk1           , Gtk::PACK_SHRINK, 3);
    hbxStatsBulk                .pack_start   (  vbxAmpType          , Gtk::PACK_SHRINK, 3);
      vbxAmpType                .pack_start   (  frmNormType         , Gtk::PACK_SHRINK, 3);
        frmNormType             .add          (  vbxNormType                               );
          vbxNormType           .pack_start   ( *rbtNormTypeRms      , Gtk::PACK_SHRINK, 3);
          vbxNormType           .pack_start   ( *rbtNormTypeFS       , Gtk::PACK_SHRINK, 3);
      vbxAmpType                .pack_start   (  frmNumType          , Gtk::PACK_SHRINK, 3);
        frmNumType              .add          (  vbxNumType                               );
          vbxNumType            .pack_start   ( *rbtNumTypeLin        , Gtk::PACK_SHRINK, 3);
          vbxNumType            .pack_start   ( *rbtNumTypeDb         , Gtk::PACK_SHRINK, 3);
          vbxNumType            .pack_start   ( *rbtBits16           , Gtk::PACK_SHRINK, 3);
          vbxNumType            .pack_start   ( *rbtBits24           , Gtk::PACK_SHRINK, 3);
          vbxNumType            .pack_start   ( *rbtBits32           , Gtk::PACK_SHRINK, 3);
          vbxNumType            .pack_start   ( *rbtBitsL16          , Gtk::PACK_SHRINK, 3);
          vbxNumType            .pack_start   ( *rbtBitsL24          , Gtk::PACK_SHRINK, 3);
          vbxNumType            .pack_start   ( *rbtBitsL32          , Gtk::PACK_SHRINK, 3);
  return;
}
void    PageAnBulk::Connect            ( void        ) {
  btAnaRaw        -> signal_clicked().connect(sigc::mem_fun(*this,  &PageAnBulk    ::OnCalcStatsRaw    ));
  btAnaFlatten    -> signal_clicked().connect(sigc::mem_fun(*this,  &PageAnBulk    ::OnDataFlatten     ));

  rbtNumTypeLin    -> signal_clicked().connect(sigc::mem_fun(*this,  &PageAnBulk    ::OnReScale         ));
  rbtNormTypeRms  -> signal_clicked().connect(sigc::mem_fun(*this,  &PageAnBulk    ::OnReScale         ));
  rbtNormTypeFS   -> signal_clicked().connect(sigc::mem_fun(*this,  &PageAnBulk    ::OnReScale         ));
  rbtBits16       -> signal_clicked().connect(sigc::mem_fun(*this,  &PageAnBulk    ::OnReScale         ));
  rbtBits24       -> signal_clicked().connect(sigc::mem_fun(*this,  &PageAnBulk    ::OnReScale         ));
  rbtBits32       -> signal_clicked().connect(sigc::mem_fun(*this,  &PageAnBulk    ::OnReScale         ));
  rbtBitsL16      -> signal_clicked().connect(sigc::mem_fun(*this,  &PageAnBulk    ::OnReScale         ));
  rbtBitsL24      -> signal_clicked().connect(sigc::mem_fun(*this,  &PageAnBulk    ::OnReScale         ));
  rbtBitsL32      -> signal_clicked().connect(sigc::mem_fun(*this,  &PageAnBulk    ::OnReScale         ));

  HnCbBulkVoid    ->SetCallback(this, &PageAnBulk::HndlBulkVoid);
  ctMd->HCB_AnBulkVoid = HnCbBulkVoid;

  return;
}
