// Include protector.
#ifndef __btMessenger_h__
#define __btMessenger_h__

// Include project configs
#include"CONFIG_static.h"
#include"PROTOCOLS.h"

class logicController
{
  public:
    // loop update (called in loop())
    static void tick(struct SYSTEM_STATE &systemState);
  private:
    static void parse_BT_message(char &msgChar, struct SYSTEM_STATE &systemState);
};

#endif // __btMessenger_h__ include protector.
