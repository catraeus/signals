
// $Id: _main.cpp 747 2023-03-05 21:15:19Z duncang $

//============================================================================
// Name        : _main.cpp
// Author      : Catraeus & Duncan Gray
// Version     :
// Copyright   : Copyright © 2014 - 2019 Catraeus & Duncan Gray
// Description : Wrapper to exercise and expose the Remez class.
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <caes/CaesRemez.hpp>
#include <caes/CaesMath.hpp>

int main(int argc, char *argv[]) {
  ldouble   *weights;
  ldouble   *desired;
  ldouble   *bands;
  ldouble   *h;
  double    *j;
  llong     i;
  llong     FIRlen;
  llong     bandCount;
  ldouble   normFreq;  // DANGER  If you make this DC (0.0) and the length is even then it'll blow up.
  bool      doNorm;

  Remez     R;



  //=========================
  // Set up the Remez
  bands      = new ldouble[   16]; // Just size it to the biggest
  weights    = new ldouble[    8]; // Just size it to the biggest
  desired    = new ldouble[    8]; // Just size it to the biggest
  h          = new ldouble[32768]; // Just size it to the biggest

#if 0

  FIRlen     = 2047;
  bandCount  =    2;

  desired[0] =    1.0;
  desired[1] =    0.0;
  desired[2] =    0.0;
  desired[3] =    0.0;
  desired[4] =    0.0;

  weights[0] =    1.0;
  weights[1] = 2150.0;
  weights[2] =    1.0;
  weights[3] =    1.0;
  weights[4] =    1.0;

  bands[0]   =                 0.0;
  bands[1]   =    ((ldouble)  431.0) / ((ldouble)48000.0);
  bands[2]   =    ((ldouble)  500.0) / ((ldouble)48000.0);
  bands[3]   =    ((ldouble)24000.0) / ((ldouble)48000.0);
  bands[4]   =    0.50000;
  bands[5]   =    0.50000;
  bands[6]   =    0.50000;
  bands[7]   =    0.50000;
  bands[8]   =    0.50000;
  bands[9]   =    0.50000;

  normFreq   =    0.00000;
  doNorm     =    true;

#else
  FIRlen     =  1997;
  bandCount  =     2;

  desired[0] =     1.0;
  desired[1] =     0.0;
  desired[2] =     0.0;
  desired[3] =     0.0;
  desired[4] =     0.0;

  weights[0] =     1.0;
  weights[1] =   633.0;
  weights[2] =     1.0;
  weights[3] =     1.0;
  weights[4] =     1.0;

  bands[0]   =                  0.0;
  bands[1]   =    ((ldouble)  500.0) / ((ldouble)48000.0);
  bands[2]   =    ((ldouble)  571.2) / ((ldouble)48000.0);
  bands[3]   =    ((ldouble)24000.0) / ((ldouble)48000.0);
  bands[4]   =    ((ldouble) 1500.0) / ((ldouble)48000.0);
  bands[5]   =    ((ldouble)24000.0) / ((ldouble)48000.0);
  bands[6]   =    0.50000;
  bands[7]   =    0.50000;
  bands[8]   =    0.50000;
  bands[9]   =    0.50000;

  normFreq   =    (bands[2] + bands[3]) / 2.00000;
  doNorm     =    true;

#endif

  fprintf(stdout, "ldouble: %ld     ldouble: %ld\n", sizeof(ldouble), sizeof(ldouble)); fflush(stdout);
  R.SetTypeBandPass();
  R.SetN(FIRlen);
  R.SetNumB(bandCount);
  R.SetAry(h);
  for(llong i = 0; i < bandCount; i++) {
    R.SetEdge(i * 2,     bands[i * 2    ]);
    R.SetEdge(i * 2 + 1, bands[i * 2 + 1]);
    R.SetG(i, desired[i]);
    R.SetW(i, weights[i]);
  }

  R.Calculate();
  if(doNorm)
    R.NormSF(normFreq);
  //ldouble corrector = 1.0 / h[(ullong)R.GetN() / 2];
  //for (i=0; i<R.GetN(); i++) h[i] *= corrector;
  for (i=0; i<R.GetN(); i++) fprintf(stdout, "%37.30Le\n", h[i]);

  ldouble peak;
  peak = -1.0;
  for(i=0; i<FIRlen; i++)
    if(peak < dabs(h[i]))
      peak = dabs(h[i]);
  for(i=0; i<FIRlen; i++)
    h[i] /= peak;

  j = new double[FIRlen];
  for(llong k=0; k<FIRlen; k++)
    j[k] = (double)(h[k]);
  FILE *blobFile = fopen("blob.raw", "wb");
  fwrite((void *)(j), sizeof(double), FIRlen, blobFile);
  fclose(blobFile);
  delete(bands);
  delete(weights);
  delete(desired);
  delete(h);
  delete(j);

  fprintf(stderr, "\n"); fflush(stderr);
  return 0;
  }
