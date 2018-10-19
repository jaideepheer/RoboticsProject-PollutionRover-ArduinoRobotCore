// Include project configs
#include"CONFIG_static.h"
/**
 * Include project modules. (header files for each module)
 */
 #include"logicController.h"

// instantiate modules
  typedef logicController logic;
void setup()
{
  #if __DEBUG_ENABLED__
    Serial.begin(9600);
  #endif
  // init. modules
    logic::init();
}

void loop()
{
  // allow modules to process data for this loop iteration.
    logic::tick();
}
