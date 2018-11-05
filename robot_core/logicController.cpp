#include"logicController.h"

void logicController::tick(struct SYSTEM_STATE &systemState)
{
  // get BT messages and process them
  if(Serial)
  {
    while(Serial.available()) // read all pending messages
    {
      char msgChar = Serial.read();
      {
        // print debug feedback to serial
          _DEBUG_PRINT_(F("Got message char.: "));
          _DEBUG_PRINT_(msgChar);
          _DEBUG_PRINT_(F("\n"));
      }
      // decide what to do
        parse_BT_message(msgChar, systemState);
    }
  }
  else
  {
    // BT Serial is not the current listener
    _DEBUG_PRINT_(F("ERROR: Serial not ready."));
  }
}

void logicController::parse_BT_message(char &msgChar, struct SYSTEM_STATE &systemState)
{
  switch(msgChar)
  {
    case BT_MESSAGE::MOVE_CAR:
      // move car command, fetch next int8_t for move value
      ;
      systemState.carMove = 127;
      break;
    default:
      {
        _DEBUG_PRINT_(F("Can't parse msg: "));
        _DEBUG_PRINT_(msgChar);
        _DEBUG_PRINT_(F("\n"));
      }
      break;
  }
}
