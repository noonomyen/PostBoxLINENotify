// LINENotifyAPI.cpp

#include "LINENotifyAPI.h"

String TokenKeyPreview(String TOKEN_KEY, uint8_t length_preview) {
    uint8_t tkl = TOKEN_KEY.length();
    String tmp = "";
    for (uint8_t i = 0; i != (tkl - length_preview); i++) {
        tmp += "*";
    };
    for (uint8_t i = (tkl - length_preview); i != tkl; i++) {
        tmp += TOKEN_KEY[i];
    };
    return tmp;
};

LINENotifyMessageAPI::LINENotifyMessageAPI(String TOKEN_KEY) {
    this->TOKEN = TOKEN_KEY;
};

void LINENotifyMessageAPI::Message(String *msg) {
    Serial.println("[LINENotifyMessageAPI] HTTP Message Configuring");
    this->REQUEST = "";
    this->REQUEST += "POST /api/notify HTTP/1.1\r\n";
    this->REQUEST += "Content-Type: application/x-www-form-urlencoded\r\n";
    this->REQUEST += "Host: notify-api.line.me\r\n";
    this->REQUEST += "Authorization: Bearer " + this->TOKEN + "\r\n";
    this->REQUEST += "User-Agent: ESP8266\r\n";
    this->REQUEST += "Content-Length: " + String(msg->length() + 8) + "\r\n";
    this->REQUEST += "Connection: close\r\n";
    this->REQUEST += "\r\n";
    this->REQUEST += "message=" + *msg;
};

bool LINENotifyMessageAPI::Send() {
    Serial.println("[LINENotifyMessageAPI] Sending Request API To Server");
    BearSSL::WiFiClientSecure CLIENT;
    CLIENT.setInsecure();

    if (!CLIENT.connect("notify-api.line.me", 443)) {
        Serial.println("[LINENotifyMessageAPI] Connection To Host Failed");
        return false;
    } else {
        Serial.println("[LINENotifyMessageAPI] Connected To Host Successfully");
    };

    Serial.println("[LINENotifyMessageAPI] REQUESTING TO : notify-api.line.me:443");
    CLIENT.print(this->REQUEST);

    int ReCheck = 0;
    while(!CLIENT.available()) {
        ReCheck += 1;
        delay(50);
        if (ReCheck == 200) {
            return false;
        };
    };

    if(CLIENT.available()) {
        String RESPONSE = String(CLIENT.readStringUntil('\r\n')).substring(13,9);
        CLIENT.stop();
        Serial.println("[LINENotifyMessageAPI] RESPONSE : " + RESPONSE);
    };

    return true;
};
