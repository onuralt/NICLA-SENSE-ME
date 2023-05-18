#include "Arduino_BHY2.h"

SensorXYZ magnetometer(SENSOR_ID_MAG_PASS);
int measurement = 1000;
// Hard-iron calibration settings
const float hard_iron[3] = {
  9.01, 46.65, 38.78
};

// Soft-iron calibration settings
const float soft_iron[3][3] = {
  { 1.016, -0.006, -0.013 },
  { -0.006, 0.962, -0.004 },
  { -0.013, -0.004, 1.024 }
};

// Magnetic declination from magnetic-declination.com
// East is positive (+), west is negative (-)
// mag_decl = (+/-)(deg + min/60 + sec/3600)
// Set to 0 to get magnetic heading instead of geo heading
const float mag_decl = 3.0833;


void setup() {

  Serial.begin(38400);
  BHY2.begin();
  magnetometer.begin();
}

void loop() {
  static auto lastCheck = millis();
  static float hi_cal[3];
  static float heading = 0;

  BHY2.update();

  if (millis() - lastCheck >= 100) {
    lastCheck = millis();
    long int magX = magnetometer.x() / 16.0;
    long int magY = magnetometer.y() / 16.0;
    long int magZ = magnetometer.z() / 16.0;

    // Put raw magnetometer readings into an array
    float mag_data[] = { magX,
                         magY,
                         magZ };

    // Apply hard-iron offsets
    for (uint8_t i = 0; i < 3; i++) {
      hi_cal[i] = mag_data[i] - hard_iron[i];
    }

    // Apply soft-iron scaling
    for (uint8_t i = 0; i < 3; i++) {
      mag_data[i] = (soft_iron[i][0] * hi_cal[0]) + (soft_iron[i][1] * hi_cal[1]) + (soft_iron[i][2] * hi_cal[2]);
    }

    // Calculate angle for heading, assuming board is parallel to
    // the ground and +Y points toward heading.
    heading = -1 * (atan2(mag_data[0], mag_data[1]) * 180) / M_PI;

    // Apply magnetic declination to convert magnetic heading
    // to geographic heading
    heading += mag_decl;

    // Convert heading to 0..360 degrees
    if (heading < 0) {
      heading += 360;
    }

    if (measurement > 0) {
      // Print calibrated results
      Serial.print("measurement no:");
      Serial.print(",");
      Serial.print(measurement);
      Serial.print(",");
      Serial.print("Bx:");
      Serial.print(",");
      Serial.print(mag_data[0], 1);
      Serial.print(",");
      Serial.print("By:");
      Serial.print(",");
      Serial.print(mag_data[1], 1);
      Serial.print(",");
      Serial.print("Bz:");
      Serial.print(",");
      Serial.print(mag_data[2], 1);
      Serial.print(",");
      Serial.print("] Heading: ");
      Serial.print(",");
      Serial.println(heading, 2);
      measurement--;
    }
  }
}