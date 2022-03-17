// Datetime.cpp

#include "Datetime.h"

time_t time_now;
struct tm* DT;

bool ConfigTimeVerify() {
    if ((time(nullptr) - (millis() / 1000)) > OFFSET_ConfigTimeVerify) {
        return 0;
    } else {
        return 1;
    };
};

void ConfigTime() {
    Serial.println("[TIME] Configuring Time From NTP Server");
    configTime((int)(UTC_OFFSET), (int)(DST), (const char *)(NTP_SERVER1.c_str()), (const char *)(NTP_SERVER2.c_str()));
};

void WaitForTimeConfiguration() {
    LED.Begin();
    Serial.println("[TIME] Waiting For Time Configuration");
    while (ConfigTimeVerify()) {
        delay(5);
        LED.Update();
    };
    LED.Clear();
};

void SetupTime() {
    ConfigTime();
    WaitForTimeConfiguration();
};

void TIME_NOW() {
    time_now = time(nullptr);
    DT = localtime(&time_now);
};
