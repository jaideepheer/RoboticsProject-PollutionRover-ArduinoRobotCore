#ifndef __sensor_h__
#define __sensor_h__

//===================================SENSORS VALUES=====================================
struct SENSOR
{
  // all the values returned by the sensor
  uint16_t gas_co,gas_lpg,gas_smoke;
  int8_t temperature;  
};
struct SENSOR airTempSensor = {};

float LPGCurve[3]  =  {2.3,0.21,-0.47};   //two points are taken from the curve. 
                                                    //with these two points, a line is formed which is "approximately equivalent"
                                                    //to the original curve. 
                                                    //data format:{ x, y, slope}; point1: (lg200, 0.21), point2: (lg10000, -0.59) 
  float COCurve[3]  =  {2.3,0.72,-0.34};    //two points are taken from the curve. 
                                                    //with these two points, a line is formed which is "approximately equivalent" 
                                                    //to the original curve.
                                                    //data format:{ x, y, slope}; point1: (lg200, 0.72), point2: (lg10000,  0.15) 
  float SmokeCurve[3] ={2.3,0.53,-0.44};    //two points are taken from the curve. 
                                                    //with these two points, a line is formed which is "approximately equivalent" 
                                                    //to the original curve.
                                                    //data format:{ x, y, slope}; point1: (lg200, 0.53), point2: (lg10000,  -0.22)                                                     
   float Ro =  10;                 //Ro is initialized to 10 kilo ohms
class Sensor
{
  public:
  
  static void tick(struct SENSOR &airTempSensor,int8_t temp_val);
  static float MQResistanceCalculation(int raw_adc);
  static float MQCalibration(int mq_pin);
  static float MQRead(int mq_pin);
  static int MQGetGasPercentage(float rs_ro_ratio, int gas_id);
  static int  MQGetPercentage(float rs_ro_ratio, float *pcurve);
};

#endif
