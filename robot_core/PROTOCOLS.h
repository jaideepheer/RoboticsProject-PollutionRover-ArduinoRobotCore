// Include protector.
#ifndef __PROTOCOLS_H__
#define __PROTOCOLS_H__

// define byte
typedef uint8_t byte;

//======================================= BT PROTOCOL ======================================
  enum BT_MESSAGE : byte
  {
    NONE,
    // CAR commands are followed by int8_t (8bit int) ranging from -128 to 127
    // [+ve is{ forward, anti-clockwise }]; [-ve is{ backward, clockwise }]
    MOVE_CAR, TURN_CAR,
    // ARM commands are followed by byte (8bit unsigned int) ranging from 0 to 255
    // the following no. indicates the required servo position.
    ARM_J1_MOVE, ARM_J2_MOVE, ARM_TURN
  };
//==========================================================================================

//====================================== SYSTEM STATE ======================================
  struct SYSTEM_STATE
  {
    // [+ve is{ forward, anit-clockwise }]; [-ve is{ backward, clockwise }]
    // -128 to 127
    int8_t carMove;
    int8_t carTurn;
    // 0 to 255
    byte armJ1Pos, armJ2Pos, armRotation;
  };
//==========================================================================================

#endif // __PROTOCOLS_H__
