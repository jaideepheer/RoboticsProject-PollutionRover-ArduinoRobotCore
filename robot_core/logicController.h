// Include protector.
#ifndef __btMessenger_h__
#define __btMessenger_h__

// Include project configs
#include"CONFIG_static.h"

#include <SoftwareSerial.h>

class logicController
{
  static SoftwareSerial btSerial;
  public:
    // constructor to init. vars like btSerial
    //logicController():btSerial(BT_PIN_IN, BT_PIN_OUT){}
    // loop update (called in loop())
    static void tick();
    // init. func.
    static void init();
};

#endif // __btMessenger_h__ include protector.
