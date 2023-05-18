#include "Arduino_BHY2.h"

SensorXYZ magnetometer(SENSOR_ID_MAG_PASS);

void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);  // will pause Zero, Leonardo, etc until serial console opens

  Serial.println(F("Sensor Lab - IMU Calibration!"));
  BHY2.begin();
  magnetometer.begin();
}

void loop() {
  BHY2.update();

  long int magX = magnetometer.x();
  long int magY = magnetometer.y();
  long int magZ = magnetometer.z();

  // 'Raw' values to match expectation of MOtionCal
  Serial.print("Raw:");
  Serial.print(int(0));
  Serial.print(",");
  Serial.print(int(0));
  Serial.print(",");
  Serial.print(int(0));
  Serial.print(",");
  Serial.print(int(0));
  Serial.print(",");
  Serial.print(int(0));
  Serial.print(",");
  Serial.print(int(0));
  Serial.print(",");
  Serial.print(int(magX / 16.0 * 10));
  Serial.print(",");
  Serial.print(int(magY / 16.0 * 10));
  Serial.print(",");
  Serial.print(int(magZ / 16.0 * 10));
  Serial.println("");

  // unified data
  Serial.print("Uni:");
  Serial.print(0);
  Serial.print(",");
  Serial.print(0);
  Serial.print(",");
  Serial.print(0);
  Serial.print(",");
  Serial.print(0);
  Serial.print(",");
  Serial.print(0);
  Serial.print(",");
  Serial.print(0);
  Serial.print(",");
  Serial.print(magX / 16.0);
  Serial.print(",");
  Serial.print(magY / 16.0);
  Serial.print(",");
  Serial.print(magZ / 16.0);
  Serial.println("");
}
