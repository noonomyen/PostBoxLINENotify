// WiFiConnect.cpp

#include "WiFiConnect.h"

bool WiFiSleeping = 0;

void PrintStatus(uint8_t code_) {
    if (code_ == WL_CONNECTED) {
        Serial.println("[WiFi] Status : Connected");
    } else if (code_ == WL_NO_SHIELD) {
        Serial.println("[WiFi] Status : No Shield");
    } else if (code_ == WL_IDLE_STATUS) {
        Serial.println("[WiFi] Status : Idle Status");
    } else if (code_ == WL_NO_SSID_AVAIL) {
        Serial.println("[WiFi] Status : No SSID Avail");
    } else if (code_ == WL_SCAN_COMPLETED) {
        Serial.println("[WiFi] Status : Scan Completed");
    } else if (code_ == WL_CONNECT_FAILED) {
        Serial.println("[WiFi] Status : Connect Failed");
    } else if (code_ == WL_CONNECTION_LOST) {
        Serial.println("[WiFi] Status : Connection Lost");
    } else if (code_ == WL_DISCONNECTED) {
        Serial.println("[WiFi] Status : Disconnected");
    };
};

void WiFiConnectFailed() {
    Serial.println("[WiFi] Retry Connecting Again");
    WiFi.disconnect();
    WiFi.begin(WiFi_SSID, WiFi_PASSWORD);
    Serial.println("[WiFi] Waiting For WiFi Connection");
};

void WaitForWiFiConnection() {
    Serial.println("[WiFi] Waiting For WiFi Connection");
    LED.Begin();
    uint8_t WiFiStatus = WiFi.status();
    while (WiFiStatus != WL_CONNECTED) {
        LED.Update();
        delay(5);
        WiFiStatus = WiFi.status();
        if (WiFiStatus == WL_CONNECT_FAILED) {
            PrintStatus(WiFiStatus);
            WiFiConnectFailed();
        };
    };
    Serial.println("[WiFi] Connected");
    LED.Clear();
};

void WiFiConnect() {
    Serial.println("[WiFi] Connecting to SSID -> " + WiFi_SSID);
    WiFi.begin(WiFi_SSID, WiFi_PASSWORD);
};

void WiFiSleep() {
    if (!WiFiSleeping) {
        WiFiSleeping = 1;
        Serial.println("[WiFi] Disconnect");
        WiFi.disconnect();
        Serial.println("[WiFi] Modem -> Sleep");
        WiFi.forceSleepBegin();
    };
};

void WiFiWake() {
    if (WiFiSleeping) {
        WiFiSleeping = 0;
        Serial.println("[WiFi] Modem -> Wake");
        WiFi.forceSleepWake();
        Serial.println("[WiFi] Set mode -> STA");
        WiFi.mode(WIFI_STA);
        WiFiConnect();
    };
};

void WiFiSETUP() {
    Serial.println("[WiFi] Set Mode -> STA");
    WiFi.mode(WIFI_STA);
    WiFiConnect();
    WaitForWiFiConnection();
};

void WiFiCheck() {
    if (WiFiSleeping) {
        WiFiWake();
    } else {
        uint8_t WiFiStatus = WiFi.status();
        if (WiFiStatus != WL_CONNECTED) {
            PrintStatus(WiFiStatus);
            Serial.println("[WiFi] Retry Connecting Again");
            WiFi.disconnect();
            WiFiSETUP();
        };
    };
};

bool WiFiIsSleeping() {
    return WiFiSleeping;
};