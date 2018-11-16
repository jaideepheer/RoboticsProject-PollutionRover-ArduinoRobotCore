//=========================== INCLUDES ==========================
  // Include project configs
    #include"CONFIG_static.h"
    #include"PROTOCOLS.h"
  // Include project modules. (header files for each module)
    #include<Servo.h>
    #include"controllerSynchronizer.h"
    #include"tempSensor.h"
    #include"sensor.h"
//===============================================================

// define helper functions
  void getCarMotorPinNibble(byte &nibble);
  byte carMotorPinNibble = 0x00;
// instantiate modules
  struct SYSTEM_STATE systemState = {};
  //struct SENSOR airTempSensor = {};
  typedef controllerSynchronizer btSync;
  
// instantiate hardware
  Servo armJ1, armJ2, armRotate;
  
//============================ SETUP ============================
  void setup()
  {
    // initialize modules
      
    // initialize hardware
      pinMode(CAR_LEFT_MOTOR_OUT_1, OUTPUT);
      pinMode(CAR_LEFT_MOTOR_OUT_2, OUTPUT);
      pinMode(CAR_RIGHT_MOTOR_OUT_1, OUTPUT);
      pinMode(CAR_RIGHT_MOTOR_OUT_2, OUTPUT);
      // Reset arm init. position
        armJ1.write(ARM_J1_INIT);
        armJ2.write(ARM_J2_INIT);
        armRotate.write(ARM_ROTATE_INIT);
        systemState.armJ1Pos = ARM_J1_INIT;
        systemState.armJ2Pos = ARM_J2_INIT;
        systemState.armRotation = ARM_ROTATE_INIT;
      armJ1.attach(ARM_J1_OUT);
      armJ2.attach(ARM_J2_OUT);
      armRotate.attach(ARM_ROTATE_OUT);
      
    // Starting sensing the temperature
      tempSensor::init(12);
      
    //===Following Lines for the Air Sensor==================
      /*Serial.print("Calibrating...\n");                
      Sensor:: Ro = Sensor::MQCalibration(MQ_PIN);   //Calibrating the sensor. Please make sure the sensor is in clean air 
                                                    //when you perform the calibration                    
      Serial.print("Calibration is done...\n"); 
      Serial.print("Ro=");
      Serial.print(Sensor::Ro);
      Serial.print("kohm");
      Serial.print("\n");*/
    //====Air Sensor Calibration Complete=========
    
    // Start serial 
    Serial.begin(9600);
  }
//===============================================================

//============================ LOOP =============================
  void loop()
  {
    // Fetch temperature from the sensor
      tempSensor::tick(systemState);
    // Air sensor tick
      //Sensor::tick(Sensor::airTempSensor,(int8_t)sensors.getTempCByIndex(0));
    // BT tick
      btSync::tick(systemState);
    // update hardware according to the systemState.
    {
        // Set arm position
          armJ1.write(systemState.armJ1Pos);
          armJ2.write(systemState.armJ2Pos);
          armRotate.write(systemState.armRotation);
        // Set car motion
          setCarMotorPinNibble(carMotorPinNibble);
          digitalWrite(CAR_RIGHT_MOTOR_OUT_1, (carMotorPinNibble & B00000001) > 0?HIGH:LOW);
          digitalWrite(CAR_RIGHT_MOTOR_OUT_2, (carMotorPinNibble & B00000010) > 0?HIGH:LOW);
          digitalWrite(CAR_LEFT_MOTOR_OUT_1, (carMotorPinNibble & B00000100) > 0?HIGH:LOW);
          digitalWrite(CAR_LEFT_MOTOR_OUT_2, (carMotorPinNibble & B00001000) > 0?HIGH:LOW);
    }
  }
//===============================================================
//                            HELPERS
//===============================================================
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
          nibble = B00001000;
        }
        else if(-systemState.carTurn > CAR_TURN_BINARY_CUT_OFF)
        {
          // Left
          nibble = B00000010;
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
          nibble = B00000100;
        }
        else if(-systemState.carTurn > CAR_TURN_BINARY_CUT_OFF)
        {
          // Left
          nibble = B00000001;
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
