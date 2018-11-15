// Include protector.
#ifndef __PROTOCOLS_H__
#define __PROTOCOLS_H__

// include standard int types
#include<stdint.h>
// define byte
typedef uint8_t byte;

//======================================= BT PROTOCOL ======================================
#define BT_MAX_JUNK_READ 7
#define BT_SET_SYSTEM_STATE_MESSAGE_SIZE 8
#define BT_PARSE_BUFFER_SIZE 16
  enum BT_MESSAGE_BYTES : byte
  {
    // These are the message elements found in BT messages.
    HEADER = 0xFA, FOOTER = 0xFF,
    READY_MESSAGE = 0xA1, SET_SYSTEM_STATE = 0xF1,
    BLANK_MESSAGE_TYPE = 0xFF
  };
//==========================================================================================

//====================================== SYSTEM STATE ======================================
#define CAR_MOVE_BINARY_CUT_OFF 30
#define CAR_TURN_BINARY_CUT_OFF 30
  struct SYSTEM_STATE
  {
    // [+ve is{ forward, anit-clockwise }]; [-ve is{ backward, clockwise }]
    // -128 to 127 (valid only from -100 to 100)
    int8_t carMove;
    int8_t carTurn;
    // 0 to 255 (valid only from 0 to 180)
    byte armJ1Pos, armJ2Pos, armRotation;
  };
//==========================================================================================
#endif // __PROTOCOLS_H__
