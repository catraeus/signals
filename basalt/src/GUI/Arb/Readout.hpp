
// $Id: Readout.hpp 7 2014-10-16 01:36:47Z duncang $

//=================================================================================================
// Original File Name : Readout.h
// Original Author    : duncang
// Creation Date      : Dec 11, 2010
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//
//=================================================================================================

#ifndef READOUT_H_
#define READOUT_H_

#include <pangomm.h>
#include <glib.h>

class Readout {
  public:
    enum eSys{EURO, ANGLO, SI};
  public:
                           Readout();
    virtual               ~Readout();
    void           SetMinValue(double i_minValue);
    void           SetMaxValue(double i_maxValue);
            void           SetDigits(long d);
            long           GetDigits(void);
            void           SetDecPos(long p);
            long           GetDecPos(void);
            void           SetValue(double d);
            void           SetValue(void);
            void           SetValueByPos(char c);
            void           SetValueByInc(void);
            void           SetValueByDec(void);
            void           Invert(void);
            double         GetValue(void);

            void           SetCurPos(int cp);
            int            GetCurPos(void);

            void           SetBright(bool hl);
            bool           GetBright(void);
            Glib::ustring  GetPangoMarkup(void);
            void           SetUnits(const char *s);
            void           SetUnits(Glib::ustring s);

  private:
            void           SetUnits(void);
            void           MakeNumStr(void);
            void           PrependZeros(char *s);
            long           ValueD2L(double d);
            double         ValueL2D(long d);
  public:
    eSys          system;
  private:
    Glib::ustring pangoMark; // don't thrash the heap, keep this alive for the duration even though it has no public availability.
    Glib::ustring startStr;
    Glib::ustring hlStr;
    Glib::ustring endStr;
    Glib::ustring unitStr;
    Glib::ustring numStr;

    char         *valueCStr;
    char         *valueCStrLED;
    double        minValue;
    double        maxValue;
    double        valueD;
    long          valueL;
    bool          bright;
    int           curPos;

    Glib::ustring units;
    long          numDigits;
    long          decPos;
    long          decPow;
    uint         *digits;
    long          sign;

    char          addPeriod;
    char          addComma;
  };

#endif /* READOUT_H_ */
