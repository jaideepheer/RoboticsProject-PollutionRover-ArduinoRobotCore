//===============================================================
//                            HELPERS
//===============================================================
  template<class T>
    void clip(const T minVal, T &value, const T maxVal)
    {
      if(value < minVal) value = minVal;
      else if(value > maxVal) value = maxVal;
    }
//===============================================================

#include"controllerSynchronizer.h"

// init. vars
static int controllerSynchronizer::bytesRead = 0;
static bool controllerSynchronizer::insideMessage = false;
static byte controllerSynchronizer::messageBuffer[BT_PARSE_BUFFER_SIZE];
static byte controllerSynchronizer::messageType = BLANK_MESSAGE_TYPE;
struct SENSOR Sensor :: airTempSensor = {0,0,0,0};
static bool controllerSynchronizer::readyMessageScheduled = false;
static unsigned long controllerSynchronizer::lastStateMessageTimestamp = -1L;

static void controllerSynchronizer::handleDisconnect(struct SYSTEM_STATE &systemState)
{
  // reset ARM position
    systemState.carMove = 0;
    systemState.carTurn = 0;
    systemState.armJ1Pos = ARM_J1_INIT;
    systemState.armJ2Pos = ARM_J2_INIT;
    systemState.armRotation = ARM_ROTATE_INIT;
}

static void controllerSynchronizer::sendReadyMessage(struct SYSTEM_STATE &systemState)
{
  Serial.write(0xFA);
  Serial.write(0xA1);
  Serial.write(systemState.temperature);
  /*Serial.write(Sensor::airTempSensor.gas_lpg);
  Serial.write(Sensor::airTempSensor.gas_co);
  Serial.write(Sensor::airTempSensor.gas_smoke);*/
  Serial.write(0xFF);

  // reset readyMessageScheduled
  readyMessageScheduled = false;
}

static void controllerSynchronizer::handleSetSystemStateMessage(struct SYSTEM_STATE &systemState)
{
  // messageBuffer has message without the first two bytes (header and type).
    systemState.carMove = messageBuffer[0];
    systemState.carTurn = messageBuffer[1];
    systemState.armJ1Pos = messageBuffer[2];
    systemState.armJ2Pos = messageBuffer[3];
    systemState.armRotation = messageBuffer[4];
  // Ensure HW limits
    clip(ARM_J1_LIMIT_MIN, systemState.armJ1Pos, ARM_J1_LIMIT_MAX);
    clip(ARM_J2_LIMIT_MIN, systemState.armJ2Pos, ARM_J2_LIMIT_MAX);
    clip(ARM_ROTATE_LIMIT_MIN, systemState.armRotation, ARM_ROTATE_LIMIT_MAX);
  // send ready message
  lastStateMessageTimestamp = millis();
  readyMessageScheduled = true;
}

/*
 * Return: True if message is valid, False is message if invalid
 */
static bool controllerSynchronizer::parseAndCheckMessage(bool &insideMessage, const int messageLength)
{
  // read message into buffer
  size_t bytesRead = Serial.readBytesUntil(BT_MESSAGE_BYTES::HEADER, messageBuffer, messageLength);
  // check message validity
  if(bytesRead<messageLength || messageBuffer[messageLength-1] == BT_MESSAGE_BYTES::HEADER)
  {
    // HEADER found inside message
    // invalid message
    return false;
  }
  // Header not inside message, can safely get outside message
    insideMessage = false;
  if(messageBuffer[messageLength-1] != BT_MESSAGE_BYTES::FOOTER)
  {
    // message not ending with FOOTER, invalid message
    return false;
  }
  // All OK, valid message
  return true;
}

static bool controllerSynchronizer::findByteInSerial(byte b)
{
  int rd = 0;
  while(Serial.available()>0 && rd<BT_MAX_JUNK_READ)
  {
    if(Serial.read() == b) return true;
  }
  return false;
}

void controllerSynchronizer::tick(struct SYSTEM_STATE &systemState)
{
  // get BT messages and process them
  if(Serial)
  {
    // Serial ready
    if(Serial.available()>0)
    {
      if(!insideMessage)
      {
        // read till header
        insideMessage = findByteInSerial(BT_MESSAGE_BYTES::HEADER);
        messageType = BT_MESSAGE_BYTES::BLANK_MESSAGE_TYPE;
      }
      else
      {
        if(messageType == BT_MESSAGE_BYTES::BLANK_MESSAGE_TYPE)
        {
          // get message type
            messageType = Serial.read();
        }
        // inside message
        switch(messageType)
        {
          case BT_MESSAGE_BYTES::SET_SYSTEM_STATE:
            // set_system_state message
            // if complete message recieved
            if(Serial.available()>=BT_SET_SYSTEM_STATE_MESSAGE_SIZE-2)
            {
              if(parseAndCheckMessage(insideMessage, BT_SET_SYSTEM_STATE_MESSAGE_SIZE-2))
              {
                // message valid
                handleSetSystemStateMessage(systemState);
              }
            }
            break;
          case BT_MESSAGE_BYTES::HEADER:
            // new header found
            messageType = Serial.read();
            break;
          default:
            // invalid messageType
            insideMessage = false;
            break;
        }
      }
    }
    // Send ready message
    if(readyMessageScheduled)
    {
      sendReadyMessage(systemState);
    }
    // Handle disconnect
    if(millis()-lastStateMessageTimestamp >= BT_DISCONNECT_TIMEOUT_MILLIS)
    {
      handleDisconnect(systemState);
    }
  }
  else
  {
    // BT Serial is not the current listener
    _DEBUG_PRINT_(F("ERROR: Serial not ready."));
  }
}
