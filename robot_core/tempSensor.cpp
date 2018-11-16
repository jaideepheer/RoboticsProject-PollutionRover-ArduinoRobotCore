#include"tempSensor.h"

OneWire onewire(TEMP_SENSOR);
DallasTemperature sensors(&onewire);

static long tempSensor::lastTempConversionTimestamp = -1L;
static long tempSensor::conversionWaitTime = -1L;

static void tempSensor::init(byte resolution)
{
  sensors.begin();
  sensors.setWaitForConversion(false);
  conversionWaitTime = 750/ (1 << (12-resolution));
}

static void tempSensor::tick(struct SYSTEM_STATE &systemState)
{
  long curTime = millis();
  if(curTime-lastTempConversionTimestamp >= conversionWaitTime)
  {
    lastTempConversionTimestamp = curTime + 10;
    systemState.temperature = sensors.getTempCByIndex(0);
    sensors.requestTemperatures();
  }
}
      //
      //systemState.temperature = sensors.getTempCByIndex(0);
