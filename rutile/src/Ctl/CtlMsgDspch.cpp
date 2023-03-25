
// $Id: CtlMsgDspch.cpp 572 2021-06-21 00:42:24Z duncang $

//=================================================================================================
// Original File Name : CtlMsgDspch.cpp
// Original Author    : duncang
// Creation Date      : 2017-02-06T01:32:18,581092635+00:00
// Copyright          : Copyright © 2017 by Catraeus and Duncan Gray
//
// Description        :
//=================================================================================================


#include "CtlMsgDspch.hpp"
#include <stdlib.h>

CtlMsgDspch *CtlMsgDspch::ctMd = NULL;


             CtlMsgDspch::CtlMsgDspch             (               ) {
  MSU_WaveRshAll          = NULL;
  MSU_FaveRshAll          = NULL;
  MSU_ApodRshAll          = NULL;
  MSU_NoiseRshAll         = NULL;
  MSU_SineRshAll          = NULL;
  MSU_SincRshAll          = NULL;
  MSU_RemezRshAll         = NULL;
  MSU_FileRshAll          = NULL;
}
             CtlMsgDspch::~CtlMsgDspch            (               ) {
}
CtlMsgDspch* CtlMsgDspch::GetInstance             ( void          ) {
  if(ctMd == NULL) ctMd = new CtlMsgDspch();
  return ctMd;
}

void         CtlMsgDspch::MRD_FileChanged         ( void          ) {
  MRD_WaveChanged();
  return;
}
void         CtlMsgDspch::MRD_WaveChanged         ( void          ) {
  if(MSU_WaveRshAll  != NULL)    MSU_WaveRshAll  ->Execute(NULL);
  if(MSU_FaveRshAll  != NULL)    MSU_FaveRshAll  ->Execute(NULL);
  if(MSU_ApodRshAll  != NULL)    MSU_ApodRshAll  ->Execute(NULL);
  if(MSU_NoiseRshAll != NULL)    MSU_NoiseRshAll ->Execute(NULL);
  if(MSU_SineRshAll  != NULL)    MSU_SineRshAll  ->Execute(NULL);
  if(MSU_SincRshAll  != NULL)    MSU_SincRshAll  ->Execute(NULL);
  if(MSU_RemezRshAll != NULL)    MSU_RemezRshAll ->Execute(NULL);
  return;
}
void         CtlMsgDspch::MRD_ApodRshAll          ( void          ) {
  MRD_WaveChanged();
  return;
}
void         CtlMsgDspch::MRD_NoiseRshAll         ( void          ) {
  MRD_WaveChanged();
  return;
}
void         CtlMsgDspch::MRD_SineRshAll          ( void          ) {
  MRD_WaveChanged();
  return;
}
void         CtlMsgDspch::MRD_SincNumerics        ( void          ) {
  MRD_WaveChanged();
  return;
}
void         CtlMsgDspch::MRD_RemezRshAll         ( void          ) {
  MRD_WaveChanged();
  return;
}
