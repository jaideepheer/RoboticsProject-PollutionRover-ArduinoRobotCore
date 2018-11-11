//=========================== INCLUDES ==========================
  // Include project configs
    #include"CONFIG_static.h"
    #include"PROTOCOLS.h"
    //#include"sensor.h"
  // Include project modules. (header files for each module)
    #include"controllerSynchronizer.h"
    // servo.h
    #include<Servo.h>
     // The essential header file for Temp Sensor
#include <OneWire.h>
// Temperature Calculator Library
#include <DallasTemperature.h>
//===============================================================

OneWire onewire(TEMP_SENSOR);
DallasTemperature sensors(&onewire);

// instantiate modules
  struct SYSTEM_STATE systemState = {};
 
  typedef controllerSynchronizer btSync;
  
// instantiate hardware
  Servo armJ1, armJ2, armRotate;
// instantiate the requirements for temp sensor

//============================ SETUP ============================
  void setup()
  {
    // initialize modules
      // nothing here
      
    // initialize hardware
      armJ1.attach(ARM_J1_OUT);
      armJ2.attach(ARM_J2_OUT);
      armRotate.attach(ARM_ROTATE_OUT);
      
    // Starting sensing the temperature
      sensors.begin();
 //===Following Lines for the Air Sensor==================
      Serial.print("Calibrating...\n");                
      Ro = Sensor::MQCalibration(MQ_PIN);   //Calibrating the sensor. Please make sure the sensor is in clean air 
                                                    //when you perform the calibration                    
      Serial.print("Calibration is done...\n"); 
      Serial.print("Ro=");
      Serial.print(Ro);
      Serial.print("kohm");
      Serial.print("\n");
//====Air Sensor Calibration Complete=========
    // DEBUG init.
    #if __DEBUG_ENABLED__
      Serial.begin(9600);
    #endif
  }
//===============================================================

//============================ LOOP =============================
  void loop()
  {
    //Temperature sensor comanded to return the temperature
    sensors.requestTemperatures();
    // Sensor Tick 
    Sensor::tick(airTempSensor,(int8_t)sensors.getTempCByIndex(0));
    // allow modules to process data for this loop iteration.
   
      // === Sensor Tick Complete ===========
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
