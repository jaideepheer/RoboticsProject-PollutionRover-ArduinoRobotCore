// Include protector.
#ifndef __controllerSynchronizer_h__
#define __controllerSynchronizer_h__

// Include project configs
#include"CONFIG_static.h"
#include"PROTOCOLS.h"

class controllerSynchronizer
{
  public:
    // loop update (called in loop())
    static void tick(struct SYSTEM_STATE &systemState);
  private:
  // vars
    static int bytesRead;
    static bool insideMessage;
    static byte messageType;
    static byte messageBuffer[BT_PARSE_BUFFER_SIZE];
    static bool readyMessageScheduled;
  // functions
    static bool parseAndCheckMessage(bool &insideMessage, const int messageLength);
    static void handleSetSystemStateMessage(struct SYSTEM_STATE &systemState);
    static void sendReadyMessage();
  // helpers
    static bool findByteInSerial(byte b);
};

#endif // __controllerSynchronizer_h__ include protector.
