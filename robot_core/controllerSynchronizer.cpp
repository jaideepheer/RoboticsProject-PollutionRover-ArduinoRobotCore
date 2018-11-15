#include"controllerSynchronizer.h"

// init. vars
static int controllerSynchronizer::bytesRead = 0;
static bool controllerSynchronizer::insideMessage = false;
static byte controllerSynchronizer::messageBuffer[BT_PARSE_BUFFER_SIZE];
static byte controllerSynchronizer::messageType = BLANK_MESSAGE_TYPE;
static bool controllerSynchronizer::readyMessageScheduled = false;

static void controllerSynchronizer::sendReadyMessage()
{
  Serial.write(0xFA);
  Serial.write(0xA1);
  Serial.write(0xFF);

  // reset readyMessageRetryCounter
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
  // send ready message
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
      sendReadyMessage();
    }
  }
  else
  {
    // BT Serial is not the current listener
    _DEBUG_PRINT_(F("ERROR: Serial not ready."));
  }
}
