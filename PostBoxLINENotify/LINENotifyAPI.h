// LINENotifyAPI.h

#ifndef LINE_NOTIFY_API_H
#define LINE_NOTIFY_API_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "BlinkingLED.h"

extern digitalBlinkingLED LED;

String TokenKeyPreview(String TOKEN_KEY, uint8_t length_preview);

class LINENotifyMessageAPI {
    private:
        String TOKEN;
        String REQUEST;
    public:
        bool ERROR = 0;
        LINENotifyMessageAPI(String TOKEN_KEY);
        void Message(String *msg);
        bool Send();
};

#endif /* LINE_NOTIFY_API_H */