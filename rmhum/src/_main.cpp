
// $Id: _main.cpp 591 2021-08-29 00:51:43Z duncang $

//=================================================================================================
// Original File Name : _main.cpp -- for project rmhum
// Original Author    : duncang
// Creation Date      : 2011-12-17
// Copyright          : Copyright © 2011-2017 by Catraeus and Duncan Gray
//
// Description        :
//     chert is an oscilloscope/specan combo to shuttle through a wave file.
//
//=================================================================================================

#include <stdio.h>
#include <caes/CaesTypes.hpp>
#include <caes/CaesApodia.hpp>

double apodVec[811];

int main(int argc, char *argv[], char **envp) {
  Apodia *theApod;
  llong   apodSize;


  theApod = Apodia::GetInstance();
  theApod->SetShape(Apodia::eShape::EAT_DOLPH);
  theApod->SetAlpha(0.0001);
  apodSize = 811;
  theApod->SetN(apodSize);
  theApod->BuildWindow();
  for(llong i=0; i<apodSize; i++) {
    apodVec[i] = 1.0;
  }
  theApod->DoIt(apodVec);

  for(llong i=0; i<apodSize; i++) {
    fprintf(stdout, "%45.32f\n", apodVec[i]);
  }
	return 0;
}
