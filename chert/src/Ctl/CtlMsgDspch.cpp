// $Id: CtlMsgDspch.cpp 491 2019-06-15 23:52:25Z duncang $

//=================================================================================================
// Original File Name : CtlMsgDspch.hpp
// Original Author    : duncang
// Creation Date      : 2016-12-25T02:05:39,414584205+00:00
// Copyright          : Copyright © 2016 by Catraeus and Duncan Gray
//
//
//=================================================================================================


#include "CtlMsgDspch.hpp"
#include <stdlib.h>
#include <stddef.h>

CtlMsgDspch *CtlMsgDspch::ctMd = NULL;


             CtlMsgDspch::CtlMsgDspch             (               ) {

  MSU_XpButSet             = NULL; // WinXport
  MSU_XpTimN               = NULL; // WinXport
  CtHn_XportStop           = NULL; // WinXport
  CtHn_XptRshTime          = NULL; // WinXport

  MSU_OsHorReBase          = NULL; // CtlOsHor

  MSU_OsHorRshAll          = NULL; // FrmOsHor

  MSU_OsVrtRshAxis         = NULL; // FrmOsAxisV
  MSU_OsVrtRshAll          = NULL; // FrmOsVrt
  MSU_OsVrtReSkin          = NULL; // FrmOsVrt

  MSU_RsmpOsAcq            = NULL;
  MSU_OsDrwTrace           = NULL; // DrwOs

  CtHn_SaHorReBase         = NULL; // CtlSaHor & CtlSaVrt

  MSU_SaHorRshAll          = NULL; // FrmSaHor
  CtHn_SaFrqReGrid         = NULL;

  MSU_SaVrtRshAll          = NULL; // nowhere yet
  MSU_SaVrtRshAxis         = NULL;
  MSU_SaStatMsg            = NULL;

  MSU_RsmpSaAcq            = NULL;
  MSU_SaDrwTrace           = NULL; // DrwSa

}
             CtlMsgDspch::~CtlMsgDspch            (               ) {
}
CtlMsgDspch* CtlMsgDspch::GetInstance             ( void          ) {
  if(ctMd == NULL) ctMd = new CtlMsgDspch();
  return ctMd;
}

// The whole damned file structure underneath
void         CtlMsgDspch::CtEm_FileReStart         ( void          ) {
  if(CtHn_XportStop      != NULL)     CtHn_XportStop     ->Execute(NULL);
  if(MSU_OsHorReBase     != NULL)     MSU_OsHorReBase    ->Execute(NULL);
  if(CtHn_SaHorReBase    != NULL)     CtHn_SaHorReBase   ->Execute(NULL);
  if(MSU_RsmpOsAcq       != NULL)     MSU_RsmpOsAcq      ->Execute(NULL);
  if(MSU_RsmpSaAcq       != NULL)     MSU_RsmpSaAcq      ->Execute(NULL);
  MRD_TraceDataHit();
  return;
}

// Transport kinds of things
void         CtlMsgDspch::MRD_XpButSet            ( uint *i_m     ) {
  if(MSU_XpButSet != NULL)  MSU_XpButSet->Execute((void *)i_m);
  return;
}
void         CtlMsgDspch::MRD_XpTimN              ( void          ) {
  if(MSU_XpTimN   != NULL)    MSU_XpTimN  ->Execute(NULL);
  return;
}


void         CtlMsgDspch::MRD_OsHorNumerics       ( void          ) {
  if(MSU_OsHorRshAll     != NULL)    MSU_OsHorRshAll    ->Execute(NULL);
  if(MSU_RsmpOsAcq       != NULL)    MSU_RsmpOsAcq      ->Execute(NULL);
  if(MSU_XpTimN          != NULL)    MSU_XpTimN         ->Execute(NULL);
  MRD_TraceDataHit();
  return;
}

// OScope Vertical kinds of things
void         CtlMsgDspch::MRD_OsVrtNumerics       ( void          ) { // Please refill all vertical info
  if(MSU_OsVrtRshAll     != NULL)    MSU_OsVrtRshAll    ->Execute(NULL);
  if(MSU_OsVrtRshAxis    != NULL)    MSU_OsVrtRshAxis   ->Execute(NULL);
  if(MSU_OsDrwTrace      != NULL)    MSU_OsDrwTrace     ->Execute(NULL);
  return;
}

// OScope Drawing kinds of things
void         CtlMsgDspch::MRD_OsNewColors         ( void          ) {
  //fprintf(stderr, "CtlMsgDspch::MRD_OsNewColors()\n"); fflush(stderr);
  if(MSU_OsVrtReSkin     != NULL)    MSU_OsVrtReSkin    ->Execute(NULL);
  if(MSU_OsDrwTrace      != NULL)    MSU_OsDrwTrace     ->Execute(NULL);
  return;
}

// SpecAn Horizontal kinds of things
void         CtlMsgDspch::MRD_SaHorNumerics       ( void          ) { // Simple reflection action, no real data.
  if(MSU_SaHorRshAll     != NULL)    MSU_SaHorRshAll    ->Execute(NULL);
  if(MSU_RsmpSaAcq       != NULL)    MSU_RsmpSaAcq      ->Execute(NULL);
  MRD_TraceDataHit();
  return;
}
void         CtlMsgDspch::CtEm_SaFrqReGrid        ( void          ) {
  if(CtHn_SaFrqReGrid    != NULL)    CtHn_SaFrqReGrid      ->Execute(NULL);
  return;
};

// SpecAn Vertical kinds of things
void         CtlMsgDspch::MRD_SaVrtNumerics      ( void          ) { // Please refill all vertical info
  if(MSU_SaVrtRshAll     != NULL)    MSU_SaVrtRshAll    ->Execute(NULL);
  if(MSU_SaVrtRshAxis    != NULL)    MSU_SaVrtRshAxis   ->Execute(NULL);
  if(MSU_SaDrwTrace      != NULL)    MSU_SaDrwTrace     ->Execute(NULL);
  return;
}

void         CtlMsgDspch::MRD_SaStatMsg          ( char   *i_s   ) {
  if(MSU_SaStatMsg       != NULL)    MSU_SaStatMsg      ->Execute((void *)i_s);

  return;
}



// The whole damned machine needs to repaint its screens
void         CtlMsgDspch::MRD_TraceDataHit        ( void          ) {
  if(MSU_OsDrwTrace      != NULL)    MSU_OsDrwTrace     ->Execute(NULL);
  if(MSU_SaDrwTrace      != NULL)    MSU_SaDrwTrace     ->Execute(NULL);
  return;
}
