#ifndef __sensor_h__
#define __sensor_h__

//===================================AIR QUALITY VALUES=====================================
struct AIR_QUALITY
{
  //the values of Air Quality will be stored here. 
  // presently assuming that the ppm will not go beyond 255
  uint8_t gas_lpg,gas_co,gas_smoke;
};
//==========================================================================================

//====================================TEMP SENSOR VALUE ====================================
struct TempInCel
{
  // stores the temperature value in Celcius
  int8_t temperature;
};
struct TempInCel tempinc = {};
struct AIR_QUALITY airQuality = {};
#endif
