// Include protector.
#ifndef __tempSensor_h__
#define __tempSensor_h__

#include"CONFIG_static.h"
#include"PROTOCOLS.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class tempSensor
{
  private:
    static long lastTempConversionTimestamp;
    static long conversionWaitTime;
  public:
    static void init(byte resolution);
    static void tick(struct SYSTEM_STATE &systemState);
};

#endif // __tempSensor_h__
