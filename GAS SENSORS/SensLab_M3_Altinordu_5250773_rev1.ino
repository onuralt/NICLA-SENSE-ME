#include "Arduino_BHY2.h"

//#define RESISTANCE
#ifdef RESISTANCE
Sensor gas(SENSOR_ID_GAS);
int seconds = 0;

void setup() {
  Serial.begin(115200);
  BHY2.begin();
  gas.begin();
}

void loop() {
  static auto lastCheck = millis();
  BHY2.update();

  // Check sensor values every second
  if (millis() - lastCheck >= 10000) {
    lastCheck = millis();
    Serial.println(String(seconds) + String(",") + String(int(gas.value())));
    seconds = seconds + 10;
  }
}
#endif

#ifndef RESISTANCE
SensorBSEC bsec(SENSOR_ID_BSEC);
int seconds = 0;

void setup() {
  Serial.begin(115200);

  BHY2.begin();
  bsec.begin();
}

void loop() {
  static auto lastCheck = millis();
  BHY2.update();

  if (millis() - lastCheck >= 10000) {
    lastCheck = millis();
    Serial.println(String(seconds) + String(",") + String(int(bsec.b_voc_eq())) + String(",") + String(int(bsec.co2_eq())) + String(",") + String(int(bsec.accuracy())) + String(",") + String(int(bsec.iaq())) + String(",") + String(int(bsec.comp_t())) + String(",") + String(int(bsec.comp_h())));
    seconds = seconds + 10;
  }
}
#endif