// Datetime.h

#ifndef DATETIME_H
#define DATETIME_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <time.h>

#include "BlinkingLED.h"

extern time_t time_now;
extern struct tm* DT;

extern digitalBlinkingLED LED;
extern int UTC_OFFSET;
extern int DST;
extern String NTP_SERVER1;
extern String NTP_SERVER2;

extern time_t OFFSET_ConfigTimeVerify;

void ConfigTime();
void WaitForTimeConfiguration();
void SetupTime();

void TIME_NOW();

#endif /* DATETIME_H */