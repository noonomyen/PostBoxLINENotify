// Post Box LINE Notify - 1.0.0 20220316
// Author : noonomyen
// BOARD : NodeMCU v3 ESP8266

// Arduino Code -> https://github.com/esp8266/Arduino
// LINE Notify -> https://notify-bot.line.me/en

////////////////////

#define LINE_NOTIFY_TOKEN_KEY ""
#define SENSOR_PIN D1
#define DETECT_SENSOR LOW
#define DETECT_SENSOR_DELAY 75

#define WIFI_SSID ""
#define WIFI_PASSWORD ""

////////////////////

#define ModemSleepMode true

#define TIME_UTC_OFFSET 7 * 3600

#define TIME_DST 0
#define NTP_SERVER_1 "pool.ntp.org"
#define NTP_SERVER_2 "time.google.com"

#define URL_Encoded "URLEncoded_TH.h"

#define SerialBaudRate 115200
#define DelaySetup 200
#define DelayStart 100
#define AUTO_RESTART 86400000 * 7
#define ModemSleepAfterActive 60000
#define ReConfigTimeAfter 86400000
#define LOOP_DELAY 10
#define PrintUptime 60000

#define RetrySendMessage 3
#define DelayInRetrySendMessage 1000
#define DelayAfterSent 100

#define GPIO_OnboardLED 2
#define OnboardLED_ON LOW

////////////////////

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <time.h>

#include URL_Encoded
#include "LINENotifyAPI.h"
#include "Datetime.h"
#include "WiFiConnect.h"
#include "BlinkingLED.h"
#include "DetectSensor.h"

digitalBlinkingLED LED(GPIO_OnboardLED, 75, 75, OnboardLED_ON);

String WiFi_SSID = WIFI_SSID;
String WiFi_PASSWORD = WIFI_PASSWORD;

int UTC_OFFSET = TIME_UTC_OFFSET;
int DST = TIME_DST;
String NTP_SERVER1 = NTP_SERVER_1;
String NTP_SERVER2 = NTP_SERVER_2;
time_t OFFSET_ConfigTimeVerify = 3;
uint8_t LENGTH_OF_TOKEN_KEY_PREVIEW = 12;

unsigned long Count_ModemSleep = millis() + ModemSleepAfterActive;
unsigned long Count_ReConfigTime = millis() + ReConfigTimeAfter;

bool OneTimesSend = 1;
unsigned long PrintUptime_ = millis() + PrintUptime;

String LINENotifyTokenKey = LINE_NOTIFY_TOKEN_KEY;

LINENotifyMessageAPI Notify(LINE_NOTIFY_TOKEN_KEY);

void setup() {
    Serial.begin(SerialBaudRate);
    delay(DelaySetup);
    Serial.println();
    Serial.println("Post Box LINE Notify - 1.0.0");
    Serial.println("[SETUP] Configure Pin Mode");
    Serial.println("[SETUP] Set PinMode -> GPIO " + String(GPIO_OnboardLED) + " : " + String("OUTPUT"));
    pinMode(GPIO_OnboardLED, OUTPUT);
    Serial.println("[SETUP] Set PinMode -> GPIO " + String(SENSOR_PIN) + " : " + String("INPUT"));
    pinMode(SENSOR_PIN, INPUT);
    Serial.println("[SETUP] Configure WiFi");
    WiFiSETUP();
    Serial.println("[SETUP] Configure Time");
    SetupTime();
    TIME_NOW();
    Serial.print("[SETUP] Time Current -> " + String(ctime((const time_t *)(&time_now))));
    Serial.println("[SETUP] LINE Notify Token Key Preview -> " + TokenKeyPreview(LINENotifyTokenKey, LENGTH_OF_TOKEN_KEY_PREVIEW));
    Serial.println("[SETUP] Configure Sensor Detection");
    SetDetectSensor(SENSOR_PIN, DETECT_SENSOR_DELAY, DETECT_SENSOR);
    delay(DelayStart);
    Serial.println("[SETUP] Start");
};

void loop() {
    if (AUTO_RESTART < millis()) {
        ESP.restart();
    };

    if (millis() > PrintUptime_) {
        Serial.println("[LOOP] Uptime -> " + String(millis() / 1000) + "s");
        PrintUptime_ = millis() + PrintUptime;
    };

    if (Notify.ERROR) {
        LED.ON();
    } else {
        LED.OFF();
    };

    if ((Count_ModemSleep < millis()) && ModemSleepMode) {
        WiFiSleep();
    };

    if (Count_ReConfigTime < millis()) {
        Count_ReConfigTime = millis() + ReConfigTimeAfter;
        ConfigTime();
    };

    if (DetectSensor()) {
        if (OneTimesSend) {
            LED.ON();
            Serial.println("[LOOP] Message Sending");
            OneTimesSend = 0;
            TIME_NOW();
            WiFiWake();
            WaitForWiFiConnection();
            String text_ = GET_Message_URLEncoded(DT);
            Notify.Message(&text_);
            for (int i = 0; i < RetrySendMessage; i++) {
                if (Notify.Send()) {
                    delay(DelayAfterSent);
                    Notify.ERROR = 0;
                    break;
                } else {
                    delay(DelayInRetrySendMessage);
                    if (i == (RetrySendMessage - 1)) {
                        Serial.println("[LOOP] Retry Sending Aborted");
                        Notify.ERROR = 1;
                    } else {
                        Serial.println("[LOOP] Retry Send -> " + String(i + 1));
                    };
                };
            };
            LED.OFF();
        };
        Count_ModemSleep = millis() + ModemSleepAfterActive;
    } else {
        OneTimesSend = 1;
    };
   delay(LOOP_DELAY);
};
