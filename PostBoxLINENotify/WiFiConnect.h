// WiFiConnect.h

#ifndef WIFI_CONNECT_H
#define WIFI_CONNECT_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "BlinkingLED.h"

extern digitalBlinkingLED LED;

extern String WiFi_SSID;
extern String WiFi_PASSWORD;

void WiFiSETUP();
void WiFiCheck();

void WiFiSleep();
void WiFiWake();

void WiFiConnect();
void WaitForWiFiConnection();

bool WiFiIsSleeping();

#endif /* WIFI_CONNECT_H */