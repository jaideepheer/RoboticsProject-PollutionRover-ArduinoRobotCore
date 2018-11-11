#ifndef __sensor_h__
#define __sensor_h__

//===================================SENSORS VALUES=====================================
struct SENSOR
{
  // all the values returned by the sensor
  uint16_t gas_co,gas_lpg,gas_smoke;
  int8_t temperature;  
};
 struct SENSOR airTempSensor={};
class Sensor
{
  public:
  static float LPGCurve[3];   //two points are taken from the curve. 
                                                    //with these two points, a line is formed which is "approximately equivalent"
                                                    //to the original curve. 
                                                    //data format:{ x, y, slope}; point1: (lg200, 0.21), point2: (lg10000, -0.59) 
  static float COCurve[3];    //two points are taken from the curve. 
                                                    //with these two points, a line is formed which is "approximately equivalent" 
                                                    //to the original curve.
                                                    //data format:{ x, y, slope}; point1: (lg200, 0.72), point2: (lg10000,  0.15) 
 static float SmokeCurve[3];    //two points are taken from the curve. 
                                                    //with these two points, a line is formed which is "approximately equivalent" 
                                                    //to the original curve.
                                                    //data format:{ x, y, slope}; point1: (lg200, 0.53), point2: (lg10000,  -0.22)                                                     
   static float Ro;                 //Ro is initialized to 10 kilo ohms
  static void tick(struct SENSOR &airTempSensor,int8_t temp_val);
  static float MQResistanceCalculation(int raw_adc);
  static float MQCalibration(int mq_pin);
  static float MQRead(int mq_pin);
  static int MQGetGasPercentage(float rs_ro_ratio, int gas_id);
  static int  MQGetPercentage(float rs_ro_ratio, float *pcurve);
};

#endif
