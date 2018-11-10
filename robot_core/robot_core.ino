//=========================== INCLUDES ==========================
  // Include project configs
    #include"CONFIG_static.h"
    #include"PROTOCOLS.h"
  // Include project modules. (header files for each module)
    #include"controllerSynchronizer.h"
    // servo.h
    #include<Servo.h>
//===============================================================

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
    }
  }
//===============================================================
