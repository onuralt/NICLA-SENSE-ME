#include "Arduino_BHY2.h"

SensorXYZ accelerometer(SENSOR_ID_ACC);
Sensor pressure(SENSOR_ID_BARO);
int measurement = 1000;

void setup() {

  Serial.begin(38400);
  BHY2.begin();
  accelerometer.begin();
  pressure.begin();
}

void loop() {

  static auto lastCheck = millis();
  BHY2.update();
  // Check sensor values every 100 ms
  if (millis() - lastCheck >= 100) {
    lastCheck = millis();
    float accX = accelerometer.x() * 0.00239501953125;
    float accY = accelerometer.y() * 0.00239501953125;
    float accZ = accelerometer.z() * 0.00239501953125;
    if (measurement > 0) {
      Serial.print(measurement);
      Serial.print(",");
      Serial.print("acceleration X:");
      Serial.print(",");
      Serial.print((String)(String(accX, 3)));
      Serial.print(",");
      Serial.print("acceleration Y:");
      Serial.print(",");
      Serial.print((String)(String(accY, 3)));
      Serial.print(",");
      Serial.print("acceleration Z:");
      Serial.print(",");
      Serial.print((String)(String(accZ, 3)));
      Serial.print(",");
      Serial.print("pressure:");
      Serial.print(",");
      Serial.println((String)(String(pressure.value(), 3)));
      measurement--;
    }
  }
}