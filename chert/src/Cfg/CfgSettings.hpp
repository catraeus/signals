
//=================================================================================================
// Original File Name : CfgSettings.h
// Original Author    : duncang
// Creation Date      : 2010-12-17
// Copyright          : Copyright © 2011 by Catraeus and Duncan Gray
//
// Description        :
//
//=================================================================================================


#ifndef __CFG_SETTINGS_HPP_
#define __CFG_SETTINGS_HPP_

#include <caes/CaesTypes.hpp>
#include "CfgEnv.hpp"

class CfgSettings {
  static const char*parmNames[];
  private:
                            CfgSettings         (       void              );
    virtual                ~CfgSettings         (       void              );
  public:
    static  CfgSettings    *GetInstance         (       void              );
            void            SetDirNameIn        ( const char *i_str       );
    const   char           *GetDirNameIn        (       void              ) { return dirNameIn ;};
  private:
            void            Build               (       void              );

  public:
  private:

           CfgEnv       *ce;

           char         *dirNameIn;
           char         *dirNameOut;
    static CfgSettings  *ct;
};

#endif // __CFG_SETTINGS_HPP_
