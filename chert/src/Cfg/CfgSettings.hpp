
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
#include <map>
#include "CfgEnv.hpp"

class CfgSettings {
  private:
    typedef enum eScope_e {
      CTES_RUN,
      CTES_USER,
      CTES_GLOBAL
    } eScope;
    static const char*parmNames[];
    struct sParms {
      char   *parmValue;
      eScope  scope;
    };
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
           std::map<char *, sParms *>    parmMap;
    static CfgSettings  *ct;
};

#endif // __CFG_SETTINGS_HPP_
