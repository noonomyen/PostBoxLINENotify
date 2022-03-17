// DetectSensor.cpp

#include "DetectSensor.h"

uint8_t SensorPin;
bool SensorState = 0;
uint8_t DetectSensor__;
unsigned long DetectDelay;
unsigned long Count;

void SetDetectSensor(uint8_t Sensor_Pin, unsigned long Detect_Delay, uint8_t DetectSensor_) {
    SensorPin = Sensor_Pin;
    DetectDelay = Detect_Delay;
    DetectSensor__ = DetectSensor_;
};

bool DetectSensor() {
  if (digitalRead(SensorPin) == DetectSensor__) {
    if (SensorState == 1 && Count <= millis()) {
          return true;
    } else if (SensorState == 0) {
      SensorState = 1;
      Count = millis() + DetectDelay;
    };
  } else {
    SensorState = 0;
  };
  return false;
};
