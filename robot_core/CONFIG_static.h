// Include protector.
#ifndef __CONFIG_STATIC_H__
#define __CONFIG_STATIC_H__

//======================================= CONFIGS =======================================
/**
 * Configs using #define pre-prosessor directives.
 * These are used to save memory since these values are replaced before compilation.
 * These settings cannot be configured during runtime.
 * These are meant to be fixed.
 * Put any config that should'nt change here.
 */
 
  // BT input/output pins
    #define BT_PIN_OUT 7
    #define BT_PIN_IN 8
    #define BT_BAUDRATE 9600
  
  // DEBUG config, See _DEBUG_PRINT_, it is usefull.
  #ifndef __DEBUG_CONFIG__
    // enable/disable debugging. Saves a LOT of memory when disabled.
    #define __DEBUG_ENABLED__ true
    #define __DEBUG_SERIAL__ Serial // the serial to print debug data to.
    // _DEBUG_PRINT_("Hello") will print 'Hello' to the debug console if debugging is enabled.
    #if __DEBUG_ENABLED__
      #define _DEBUG_PRINT_(X) __DEBUG_SERIAL__.print(X)
    #else
      #define _DEBUG_PRINT_(X)  
    #endif
    // To use Serial as debug serial.
    #if __DEBUG_ENABLED__
      #include<Arduino.h>
    #endif
  #endif

//=======================================================================================

// Config checks
#if __DEBUG_ENABLED__
  #warning "DEBUG enabled...! Debug mode will use more memory."
#endif
#if BT_PIN_OUT==BT_PIN_IN
  #error "Config: BT_PIN_OUT and BT_PIN_IN have same values."
#endif

#endif // __CONFIG_STATIC_H__
