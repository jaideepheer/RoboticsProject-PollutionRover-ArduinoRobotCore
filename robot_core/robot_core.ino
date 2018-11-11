//=========================== INCLUDES ==========================
  // Include project configs
    #include"CONFIG_static.h"
    #include"PROTOCOLS.h"
  // Include project modules. (header files for each module)
    #include"controllerSynchronizer.h"
    // servo.h
    #include<Servo.h>
//===============================================================

// define helper functions
  void getCarMotorPinNibble(byte &nibble);
  byte carMotorPinNibble = 0x00;
// instantiate modules
  struct SYSTEM_STATE systemState = {};
  typedef controllerSynchronizer btSync;
  
// instantiate hardware
  Servo armJ1, armJ2, armRotate;

//============================ SETUP ============================
  void setup()
  {
    // initialize modules
      // nothing here
      
    // initialize hardware
      pinMode(CAR_LEFT_MOTOR_OUT_1, OUTPUT);
      pinMode(CAR_LEFT_MOTOR_OUT_2, OUTPUT);
      pinMode(CAR_RIGHT_MOTOR_OUT_1, OUTPUT);
      pinMode(CAR_RIGHT_MOTOR_OUT_2, OUTPUT);
      armJ1.attach(ARM_J1_OUT);
      armJ2.attach(ARM_J2_OUT);
      armRotate.attach(ARM_ROTATE_OUT);

    // DEBUG init.
    #if __DEBUG_ENABLED__
      Serial.begin(9600);
    #endif
  }
//===============================================================

//============================ LOOP =============================
  void loop()
  {
    // allow modules to process data for this loop iteration.
      btSync::tick(systemState);
    // update hardware according to the systemState.
    {
        // Set arm position
          armJ1.write(systemState.armJ1Pos);
          armJ2.write(systemState.armJ2Pos);
          armRotate.write(systemState.armRotation);
        // Set car motion
          setCarMotorPinNibble(carMotorPinNibble);
          digitalWrite(CAR_LEFT_MOTOR_OUT_1, carMotorPinNibble &  B00000001);
          digitalWrite(CAR_LEFT_MOTOR_OUT_2, carMotorPinNibble &  B00000010);
          digitalWrite(CAR_RIGHT_MOTOR_OUT_1, carMotorPinNibble & B00000100);
          digitalWrite(CAR_RIGHT_MOTOR_OUT_2, carMotorPinNibble & B00001000);
    }
  }
//===============================================================

//========================= HELPERS =============================
  void setCarMotorPinNibble(byte &nibble)
  {
    // reset nibble
      nibble = 0x00;
    // Set nibble
      if(systemState.carMove > CAR_MOVE_BINARY_CUT_OFF)
      {
        // Forward
        if(systemState.carTurn > CAR_TURN_BINARY_CUT_OFF)
        {
          // Right
          nibble = B00000010;
        }
        else if(-systemState.carTurn > CAR_TURN_BINARY_CUT_OFF)
        {
          // Left
          nibble = B00001000;
        }
        else
        {
          // no turn
          nibble = B00001010;
        }
      }
      else if(-systemState.carMove > CAR_MOVE_BINARY_CUT_OFF)
      {
        // Backward
        if(systemState.carTurn > CAR_TURN_BINARY_CUT_OFF)
        {
          // Right
          nibble = B00000010;
        }
        else if(-systemState.carTurn > CAR_TURN_BINARY_CUT_OFF)
        {
          // Left
          nibble = B00001000;
        }
        else
        {
          // no turn
          nibble = B00000101;
        }
      }
      else
      {
        // no movement, check turn
        if(systemState.carTurn > CAR_TURN_BINARY_CUT_OFF)
        {
          // Right
          nibble = B00001001;
        }
        else if(-systemState.carTurn > CAR_TURN_BINARY_CUT_OFF)
        {
          // Left
          nibble = B00000110;
        }
      }
  }
//===============================================================
