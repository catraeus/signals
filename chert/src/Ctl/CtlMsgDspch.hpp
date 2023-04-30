// $Id: CtlMsgDspch.hpp 634 2022-11-19 22:52:03Z duncang $

//=================================================================================================
// Original File Name : MsgHub.hpp
// Original Author    : duncang
// Creation Date      : 2016-12-25T02:05:39,414584205+00:00
// Copyright          : Copyright © 2016 by Catraeus and Duncan Gray
//
//
//=================================================================================================

/*! \brief Message Dispatch Controller. */
/*
 Created by int main();
 Useable by all - #included in all
 events and actions are initiated by all other entities by calling a method in here.
 this dispatcher has callbacks executed by above to allow CtlMsgDspch to push information and initiate action right back at-ya.

 Downward - Methods in here   - These should be verbs about what just happened, now what you are requesting to do.
 Upward   - Callbacks in here - These should be verbs about what you are requesting to do.
 THIS MEANS THAT THE MESSAGE DISPATCHER IS THE REALLY WISE ONE THAT YOU PUT ALL OF THAT INTELLIGENCE INTO.  BE CAREFUL OH GENTLE PROGRAMMER.

 PLEASE try to use specialized controllers and models close to the views to condense traffic as much as possible.
 PLEASE make struct objects to pass complicated data back and forth as opposed to a flurry of message dispatches.
 PLEASE always always always call this object ctMd ( camel case for for ConTroller MessageDispatcher.

 By having this be at the bottom instead of at the top, each subsystem can Connect to these callbacks
 when it comes alive.  Otherwise, this would have to have a huge list of includes (everybody) and a
 Connect callback executed at the right time by each one.  That is just as valid as this, but takes (I think) more
 lines of code than this.

 Here is what we call things here in CtlMsgDspch
 MRD means Message Rcv Down.  Since CtlMsgDspch is a singleton at the bottom, we get messages from "above."
                              Also, since CtlMsgDspch is  include in everything, all others can reference by call.
 MSU means Message Send Up.   Since CtlMsgDspch is a singleton at the bottom, we send messages from "below."
                              Also, because of include hell, these have to be executed as callbacks.
 And up in the higher level objects, the exact same interface has the complementarily TLA'd callbacks/functions:
 MSD - NEVER NEEDED BECAUSE OF THE CALLBACK ASSYMMETRY -- just call ctMd->MRD_BlaBlaBla();
 MRU - What callbacks are called up high.  It is called OnBlaBlaBla for the Method in the higher-up.

 Since a method call from above uses only one named function (the member method in CtlMsgDspch) there is no name
   multiplicity possible in MRD_... activity.  BUT, there have to be two names in the opposite direction.
   IF we keep the names identicle using the following pattern:


     In the upper class called UpperClass here, there is stuff that has happened that results in:
     void  UpperClass::OnStuffHappens(who knows what) {
       ...
       ctMd->MRD_DidBar(void *i_theStuff);
     }


     In the one and only CtlMsgDspch instance
     in its header file:
       void              MRD_DidBar(void *theStuff);
       CbV              *MSU_DoFoo;
     in its c++ file constructor:
       MSU_DoFoo = NULL
     In its c++ file controller method that is responding to a MRD_DidBar()
       if(MSU_DoFoo != NULL) // Guard against not having a callback set yet.
         MSU_DoFoo->Execute(theStuff); // but, of course, there is no reason not to make a new struct
                                       // to send upward since the CtlMsgDspch is so wise and all-knowing

     And in the upper object called HighClass in the example
     In its header file:
       CbT<HighClass>   *MRU_DoFoo;
       MRU_DoFoo       = new CbT<HighClass>();
       void              DoFoo(void *msg);

     In its c++ file, in its InterConnect() function:
       MRU_DoFoo->SetCallback(this, &HighClass::OnDoFoo);
       ctMd->MSU_DoFoo = MSU_DoFoo;  // Oh look, the name is the same.
     And then it has to have a really cool method
       void HighClass::DoFoo(void *msg)


 Remember that the callback signature is:
 void    HighClass::DoFoo(void *msg);
 */

#ifndef __CTL_MSG_DSPCH_HPP_
#define __CTL_MSG_DSPCH_HPP_

#include <caes/CaesTypes.hpp>
#include <caes/CaesCallBack.hpp>

class CtlMsgDspch {
  private:
                                 CtlMsgDspch           (                  );
    virtual                     ~CtlMsgDspch           (                  );
  public:
    static  CtlMsgDspch         *GetInstance           ( void             );  // I think it's pretty obvious why this is a singleton.

            void                 CtEm_FileReStart      ( void             );

            void                 MRD_XpButSet          ( uint *i_butMask  );
               CbV *MSU_XpButSet;
            void                 Emit_XpTimAdv         ( void             );
               CbV *CtHn_XpTimAdv;

               CbV *CtHn_XportStop;   // Handle a need to stop the transport.
               CbV *CtHn_XptRshTime;  // Handle the fact that the controller moved time forward.


            void                 MRD_OsHorNumerics     ( void             );
               CbV *MSU_OsHorReBase;
               CbV *MSU_OsHorRshAll;

            void                 MRD_OsVrtNumerics     ( void             );
               CbV *MSU_OsVrtRshAll;
               CbV *MSU_OsVrtRshAxis;
               CbV *MSU_OsVrtReSkin;

            void                 MRD_OsNewColors       ( void             );

               CbV *MSU_OsDrwTrace;

            void                 CtEm_SaReScale        ( void             );
               CbV *CtHn_SaHorReBase;
               CbV *CtHn_SaHorRshAll;

            void                 CtEm_SaFrqReGrid      ( void             );
               CbV *CtHn_SaFrqReGrid;

            void                 Emit_SaVrtNumerics     ( void             );
               CbV *MSU_SaVrtRshAll;
               CbV *MSU_SaVrtRshAxis;

               CbV *MSU_SaDrwTrace;

            void                 MRD_SaStatMsg         ( char    *i_s     );
               CbV *MSU_SaStatMsg;


            void                 Emit_XportHit         ( void             );


               CbV *MSU_RsmpOsAcq;
               CbV *CtHn_RsmpSa;

  private:
  public:

  private:
    static CtlMsgDspch          *ctMd;
};

#endif // __CTL_MSG_DSPCH_HPP_
