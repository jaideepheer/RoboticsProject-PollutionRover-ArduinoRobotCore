#include"logicController.h"

static SoftwareSerial logicController::btSerial(BT_PIN_IN, BT_PIN_OUT);

void logicController::tick()
{
  // get BT messages and process them
  if(btSerial.isListening())
  {
    while(btSerial.available()) // read all pending messages
    {
      char msgChar = btSerial.read();
      // print debug feedback to serial
        _DEBUG_PRINT_("Got message char.: ");
        _DEBUG_PRINT_(msgChar);
        _DEBUG_PRINT_("\n");
    }
  }
}

void logicController::init()
{
  // init. BT serial
    btSerial.begin(BT_BAUDRATE);
    // set serial listner to btSerial
    btSerial.listen();
}
