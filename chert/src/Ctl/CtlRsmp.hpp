
// $Id: CtlRsmp.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : CtlRsmp.hpp
// Original Author    : duncang
// Creation Date      : Jun 9, 2013
// Copyright          : Copyright © 2013 - 2017 by Catraeus and Duncan Gray
//
// Description        :
/* Architecture
    This subsystem resamples one array of vectors to another array of vectors.  I don't use the
      vector class as a matter of DSP principle.  GO AWAY.
    There are two ways to figure out what the resample rate is.  Give nIn and nOut and use
      rational number theory to resample.  This is classic frac-n stuff.  Second is to take in a
      real number and nIn and calculate nOut.  This is the more general resample problem.
    Given that this is for outputs that go to dot devices, this will always be used for the frac-n
      case.
    I generally leave the highest level object to make vectors, so there are only pointers to the big
      vectors in here.
    This is a generic, n-channel, system so that the channels are double **x vectors.  That means that
      I need nIn and nOut to come in before I can work on anything.
    This is running with scissors, DSP, so I don't do vector bound checking.  GO AWAY.
    Hide all of the variables, set and get pointers and sizes.  Use accessors so that valid
      keeps us honest.
    General Startup:
      1 - make the valid bit false. - pretty simple, eh
    General procedure:
      1 - give me a new pointer to In. - invalidate

*/
// Definitions:
/*  Width - The number of samples in the big Side that represent one sample time in the small Side.
            If we are decimating, then there are more samples in the input than in the output.  If
              we are interpolating, then there are more samples in the output than in the input.
              In the frac-n case there is a third domain, virtual, that is GCF of the resample
              rate integer numbers.
              Width is max(AR, 1.0 / AR)
*/
/*  Side -  There is an Analysis Side (the output) and a Signal Side (the input.)
            The wall in between is one-way and is the analysis performed.
*/
/*  Analysis - Can be Interpolation, Transfer or Decimation.
            Interpolation when the Analysis Ratio is > 1.0 and Decimation when it is < 1.0.
              So ... Transfer is when the Analysis Ratio is 1.0.
*/
/*  Analysis Ratio - AR - Output Width divided by Input Width, simple as that.*/
/* Decimation Method
    There are several decimation methods (English method, not c+ method:)
      1. Pluck      -  There is a width of input samples and the one nearest the output position is
                       chosen.  The hard part (not very) of this algorithm is the divide to find the nearest
                       amongst the width.  The screwy part is that the "jitter" of the choice algorithm
                       makes subsequent analysis polluted by the time quantization of the selection
                       without any true interpolation between the two chosen width values.
      2. Filter     -  The output domain implies a reduction of sample rate.  This means that, to keep
                       Mr. Nyquist happy, we have to take high-frequency content out of the input.
                       This can be done by honest-to-Pete resampling or by filtering in the input domain
                       and Plucking.  I will do honest-to-Pete resampling and just slow us down.  Live
                       with it.
      3. polynomial -  So the problem with Filter as a method is that the length of the filter lets
                       trans-Nyquist content pollute the result.  Furthermore, that method is really
                       expensive because it's a convolution and because you need many more terms than here
                       with polynomial to get any given accuracy of interpolation.  Polynomial is an interpolation
                       tool to use for either improving the Pluck method or speeding up the Filter method.
                       you only need M+1 (M = polynomial order) samples and generally do M*LogM multiplies
                       to get the desired interpolated value at real t (as opposed to rational t.)  Furthermore
                       we can do the brick-wall filter in the input domain then polynomial interpolate
                       to get the output term.  Non-linear distortion due to the polynomial is made
                       as small as needed with higher M.
      4. minimax    -  So you might think that this is easy.  In the first approximation, it is.  Just take the
                       width samples and find the min and the max.  The output is two vectors (don't forget this
                       one.)  But wait, there's more.  If the boundary of the width is a fraction of the input
                       locations, then you have to do an interpolate to the neighboring width of sample's nearest
                       value to see if the minimax is at the boundary.  Ugh.  Also, you would have to do
                       an interpolate betwen every single damned width point to see if a minimax would have been
                       in the trajectory between the points.  Well, all of this is great Master's thesis work.  look
                       for it on a Catraeus blog soon to come to your neighborhood.  For now I will just look at
                       the K points in the Width and report those.
                       ALSO -- I will calculate the RMS of these Width points (but I will perform edge weighting on
                       these) to have a third vector output that will (by definition) fall between the minimax.
                       Hmmmmmmm - In what sense is the brick wall output a fairer RMS estimate? Another Master's
                       thesis.
*/
/* Signal Domain:
    We will use this to do work on complex input, for example, when this is demodulated carriers.  Heh heh, you thought
      I was just going to be Audio, didn't you?
*/

/* Analysis Domain:
    This is the type of output that will come from the resampling.  So maybe this isn't a CtlRsmp, so much as a
      time-domain-only analyzer.  First, assume that the input is a vector that represents a time-periodic, Nyquist-happy
      sample of (my personal favorite) air pressure that got turned into analog voltage that got turned into digital
      numbers.  The input must have sample rate and number of samples.  The input is a single vector, hmmmm maybe
      I should make it complex. OK, OK i'll make it complex.  Power estimation has to be on the phasor, likewise
      max, phase angle and all that, so I won't hobble the real-only analysis when the parent says not to worry about it.
*/

#ifndef __CTL_RSMP_HPP_
#define __CTL_RSMP_HPP_

#include <caes/CaesTypes.hpp>
#include <caes/CaesCallBack.hpp>
#include <caes/AudioFile/Signal.hpp>

#include <caes/CaesSpectrum.hpp>
#include <caes/CaesApodia.hpp>

#include "../Mdl/MdlOs.hpp"
#include "../Mdl/MdlSa.hpp"
#include "../Ctl/CtlMsgDspch.hpp"

class CtlRsmp {
  //===============================================================================================
  //Types
  private:
    enum eConst   {
      EK_MAX_CH      =        4,
      EK_MAX_SA_SMPS =   262144,
      EK_MAX_SA_FRQS =   262144,
      EK_MAX_OS_DOTS =     4096,
      EK_MAX_SA_DOTS =     4096,
      EK_DIV_FFT     =     2048
    };
    enum eIntOs   { EIO_PLUCK, EIO_SINX, EIO_POLY }; //!< OScope Interpolate Method
    enum eIntSa   { EIS_PLUCK, EIS_SINX, EIS_POLY }; //!< SpecAn Interpolate Method
    enum eSigDom  { ESD_REAL,  ESD_CPLX           }; //!< Signal Time Field Type
    enum eSaDom   { EAD_CPLX,  EAD_PWR            }; //!< SpecAn Frequency Field Type
    enum eSaVrt   { ESV_LIN,   ESV_LOG            }; //!< SpecAn Vertical Mutation
    enum eSaHor   { ESH_LIN,   ESH_LOG            }; //!< SpecAn Vertical Mutation
  private:
  //===============================================================================================
  //Methods
                     CtlRsmp     ( Signal *i_sig     );
    virtual         ~CtlRsmp     ( void              );
            void     BuildEnv    ( Signal *i_sig     );
            void     BuildMain   ( void              );
            void     Connect     ( void              );
  public:
    static  CtlRsmp *GetInstance ( Signal *i_sig     );

            void     SetIntOs    ( eIntOs    i_intOs );
            void     SetSigDom   ( eSigDom   i_osDom );
            void     SetSaDom    ( eSaDom    i_saDom );
            double **GetOsNom    ( void              ) { return pOs   ;};
            double **GetSaApod   ( void              ) { return pTre  ;};
            double **GetSaNom    ( void              ) { return pSa   ;};

            void     GrabHere    ( void              );
            void     ReScale     ( void              );
            bool     RsmpOsAcq   ( void     *d       );
            bool     RsmpSaAcq   ( void     *d       );
            void     CalcSpecAvg ( void              );
  //===============================================================================================
  //Fields
  public:
  private:
           eIntOs        intOs;
           eSigDom       sigDom;
           eSaDom        saDom;
           double      **pSig;
           double      **pTre;
           double      **pTim;
           double      **pFre;
           double      **pFav;
           double      **pFwork;
           double      **pFim;
           double      **pOs;
           double      **pSa;

           MdlOs        *mdOs;
           MdlSa        *mdSa;

           Apodia       *apod;
           Signal       *sig;
           SpecTran     *xfrm;

           CtlMsgDspch  *ctMd;
           CbT<CtlRsmp> *MRU_RsmpSaAcq;
           CbT<CtlRsmp> *MRU_RsmpOsAcq;

    static CtlRsmp  *ctRsmp;
  };

#endif /* __CTL_RSMP_HPP_ */
