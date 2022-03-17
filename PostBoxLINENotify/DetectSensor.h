// DetectSensor.h

#ifndef DETECT_SENSOR_H
#define DETECT_SENSOR_H

#include <Arduino.h>

void SetDetectSensor(uint8_t Sensor_Pin, unsigned long Detect_Delay, uint8_t DetectSensor_);
bool DetectSensor();

#endif /* DETECT_SENSOR_H */