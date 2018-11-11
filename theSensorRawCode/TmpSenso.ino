
#include <OneWire.h>
#include <DallasTemperature.h>

int temp_sensor = 5;
float temperature = 0;
OneWire onewire(temp_sensor);
DallasTemperature sensors(&onewire);


void setup() {
Serial.begin(9600);
sensors.begin();
}

void loop() {
  Serial.print("Requesting Temperatures:");
  sensors.requestTemperatures();
  Serial.println("Done");
  temperature = sensors.getTempCByIndex(0);
  Serial.println("Temperature is:");
  Serial.print(temperature);
  delay(500);
}
