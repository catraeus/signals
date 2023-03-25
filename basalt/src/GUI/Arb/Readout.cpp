
// $Id: Readout.cpp 405 2018-01-20 22:18:32Z duncang $

//=================================================================================================
// Original File Name : Readout.cpp
// Original Author    : duncang
// Creation Date      : Dec 11, 2010
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//
/*

The representation is fixed-point positive and negative
The usable part is double
You can only ever set by double

The display has settings:
A number of digits, note that the readout will have one more because of a potential minus sign
A number of digits past the decimal mark
A min valueD
A max valueD

The display has dynamically:
a valueD
a current position

so
The number of digits must be one greater than the fractional digits
Given a number of digits and a number of fractional digits
   The min and max must be checked for the big end positive and negative
   The min and max must be checked for nearness to zero.

The font used is a special one that has points and commas built into the characters, no goofy
looking display to take up either.  Only goofy incrementing of characters to add commas, points etc.

If the current position is left of the most significant digit, then fill in with zeroes
Put the negative sign (if present) left of the left-most printing character.

It is wise, oh programmer, to set the digits & decimals first, then set the limits.
    That is the natural flow of the truncations that I have implemented.

*/
//
//=================================================================================================

#include "Readout.hpp"
#include <caes/CaesTypes.hpp>
#include <iostream>
#include <string.h>
#include <math.h>
#include "malloc.h"

               Readout::Readout() {
  digits        = new uint[12];
  sign          =     1;
  minValue      =    10.0;
  maxValue      = 10000.0;
  curPos        =     0;
  bright        = false;
  numDigits     =    12;
  decPos        =     0;
  decPow        =     1;
  valueCStr     = new char[256];
  valueCStrLED  = new char[256];

  system    = ANGLO;
  pangoMark = "";
  numStr    = "";
  hlStr     = "<span  color='#ffa080'>";
  endStr    = "</span>";
  startStr  = "<span font='FreeMonoLED 48' color='#ff0000'>";


  addPeriod = '\020';
  addComma  = '\100';
  SetDecPos(6);
  SetUnits("Hz");
  SetValue(0.0);
  }
               Readout::~Readout() {
  }
Glib::ustring  Readout::GetPangoMarkup(void) {
  pangoMark = startStr;
  pangoMark = pangoMark + numStr;
  pangoMark = pangoMark + endStr;
  pangoMark = pangoMark + unitStr;
  //fprintf(stdout, "Readout::GetPangoMarkup   %s\n", pangoMark.c_str());
  return pangoMark;
  }
void           Readout::SetMinValue(double i_minValue) {
  double dd;
  long   ll;

  dd = pow(10.0, numDigits - decPos);
  ll = ValueD2L(dd) - 1L;
  dd = ValueL2D(ll);
  if(i_minValue > dd)
    minValue =  dd; // we got problems, bucko, so I'll just fix it best I can.
  else if(i_minValue < -dd)
    minValue = -dd;
  else if(i_minValue > maxValue)
    minValue = maxValue;
  else
    minValue = i_minValue;
  SetValue(valueD);
  return;
  }
void           Readout::SetMaxValue(double i_maxValue) {
  double dd;
  long   ll;

  dd = pow(10.0, numDigits - decPos);
  ll = ValueD2L(dd) - 1L;
  dd = ValueL2D(ll);
  if(i_maxValue < -dd)
    maxValue = -dd; // we got problems, bucko, so I'll just fix it best I can.
  else if(i_maxValue > dd)
    maxValue = dd;
  else if(i_maxValue < minValue)
    maxValue = minValue;
  else
    maxValue = i_maxValue;
  SetValue(valueD);
  return;
  }
void           Readout::SetUnits(Glib::ustring s) {
  units   = s;
  SetUnits();
  return;
  }
void           Readout::SetUnits(const char *s) {
  units   = s;
  SetUnits();
  return;
  }
void           Readout::SetUnits(void) {
  unitStr = "<span font='Monospace 24'>   ";
  unitStr = unitStr + units;
  unitStr = unitStr + endStr;
  MakeNumStr();
  return;
  }
void           Readout::SetDigits(long i_digits) {
  if(i_digits > 12)
    numDigits = 12;
  else if(i_digits < 4)
    numDigits = 4;
  else
    numDigits = i_digits;
  SetDecPos(decPos);
  return;
  }
void           Readout::SetDecPos(long i_decPos) {
  decPos = i_decPos;
  if(decPos > numDigits)
    decPos = numDigits;
  decPow = 1;
  for(uint i=0; i<(uint)decPos; i++) {
    decPow *= 10;
    }
  SetMinValue(minValue);
  SetMaxValue(maxValue);
  return;
  }
void           Readout::MakeNumStr(void) {
  //char a[256];
  int  sigPos;

  sigPos = -1;

  //sprintf(a, "%%%ld.0lf", numDigits);
  //sprintf(valueCStrLED, a, valueD * (double)decPow);
  for(int i=numDigits - 1; i>=0; i--) {
    valueCStrLED[numDigits - i - 1] = digits[i] + '0';
    if((digits[i] > 0) && (sigPos < 0))
      sigPos = numDigits - i - 1;
    }
  if(sigPos < 0)
    sigPos = curPos;
  else if(sigPos > curPos)
    sigPos = curPos;
  if(sigPos > (numDigits - decPos - 1))
    sigPos = numDigits - decPos - 1;

  if(sign == -1) {
    sigPos--;
    valueCStrLED[sigPos] = '-';
    }
  for(int i=0; i<sigPos; i++)
    valueCStrLED[i] = ' ';
  valueCStrLED[numDigits] = '\0';

  numStr.clear();
  for(int i=0; i<numDigits; i++) {
    Glib::ustring cc;
    cc = valueCStrLED[i];
    if((i == curPos) && bright)
      numStr = numStr + hlStr;
    if((i==(decPos - 4)) && (valueCStrLED[i] >= '0') && (valueCStrLED[i] <= '9'))
      valueCStrLED[i] += addComma;
    else if(i == (decPos - 1)) {
      valueCStrLED[i] += addPeriod;
      }
    cc = valueCStrLED[i];
    numStr = numStr + cc;
    if((i == curPos) && bright)
      numStr = numStr + endStr;
    }
  return;
  }
void           Readout::SetBright(bool hl) {
  bright = hl;
  MakeNumStr();
  return;
  }
bool           Readout::GetBright(void) {
  return bright;
  }
void           Readout::Invert(void) {
  valueD *= -1.0;
  SetValue(valueD);
  return;
  }
long           Readout::ValueD2L(double d) {
  long k;
  k = (long)floor(d * decPow + DBL_ROUNDER);
  //fprintf(stdout, "Readout::ValueD2L(%lf) = %ld\n", d, k);
  return k;
  }
double         Readout::ValueL2D(long k) {
  double d;

  d = (double)k / decPow;
  //fprintf(stdout, "Readout::ValueL2D(%ld) = %lf\n", k, d);
  return d;
  }
void           Readout::SetValue(double d) {
  long ll;

  if(d < minValue)
    valueD = minValue;
  else if(d > maxValue)
    valueD = maxValue;
  else
    valueD = d;
  valueL = ValueD2L(valueD);
  ll = valueL;
  if(ll < 0) {
    sign = -1;
    ll = -ll;
    }
  else
    sign = 1;
  uint i;
  for(i=0; ((i<(uint)numDigits) && (ll>0)); i++) {
    digits[i] = ll % 10;
    ll -= digits[i];
    ll /= 10;
    }
  for(; i<12; i++) {
    digits[i] = 0;
    }
  //for(i=0; i<12; i++)
  //  fprintf(stdout, "%u", digits[i]);
  //fprintf(stdout, "\n");
  MakeNumStr();
  return;
  }
void           Readout::SetValueByPos(char c) {
  char   a[32];
  double d;

  if((c < '0') || (c > '9'))
    return;
  sprintf(a, "%%%ld.0f", numDigits);
  sprintf(valueCStr, a, valueD*1000000.0);
  PrependZeros(valueCStr);
  valueCStr[curPos] = c;
  sscanf(valueCStr, "%lf", &d);
  d /= 1000000.0;
  SetCurPos(curPos+1);
  SetValue(d);
  }
void           Readout::SetValueByInc(void) {
  double p;

  p = (double)(numDigits - decPos - curPos - 1);
  p = pow(10.0, p);
  p += valueD;
  SetValue(p);
  }
void           Readout::SetValueByDec(void) {
  double p;

  p = (double)(numDigits - decPos - curPos - 1);
  p = pow(10.0, p);
  p *= -1.0;
  p += valueD;
  SetValue(p);
  }
double         Readout::GetValue(void) {
  return valueD;
  }
int            Readout::GetCurPos(void) {
  return curPos;
  }
void           Readout::SetCurPos(int cp) {
  if(cp < 0)
    curPos = 0;
  else if(cp > (numDigits-1))
    curPos = numDigits-1;
  else
    curPos = cp;
  MakeNumStr();
  return;
  }
void           Readout::PrependZeros(char *s) {
  for(int i=0; (i<numDigits) && (s[i] == ' '); i++)
    if(i >= curPos)
      s[i] = '0';
  return;
  }
