// BlinkingLED.cpp

#include "BlinkingLED.h"

analogBlinkingLED::analogBlinkingLED(uint8_t gpio, unsigned long delay_on_, unsigned long delay_off_, int on_, int off_) {
    this->pin = gpio;
    this->delay_on = delay_on_;
    this->delay_off = delay_off_;
    this->on = on_;
    this->off = off_;
    this->state = off_;
};

void analogBlinkingLED::Clear() {
    analogWrite(this->pin, this->off);
    this->state = 0;
    this->time = 0;
};

void analogBlinkingLED::Update() {
    if (this->state && this->time <= millis()) {
        this->OFF();
    } else if (!this->state && this->time <= millis()) {
        this->ON();
    };
};

void analogBlinkingLED::Begin() {
    analogWrite(this->pin, this->on);
    this->state = 1;
    this->time = millis() + this->delay_on;
};

void analogBlinkingLED::ON() {
    analogWrite(this->pin, this->on);
    this->state = 1;
    this->time = millis() + this->delay_on;
};

void analogBlinkingLED::OFF() {
    analogWrite(this->pin, this->off);
    this->state = 0;
    this->time = millis() + this->delay_off;
};

digitalBlinkingLED::digitalBlinkingLED(uint8_t gpio, unsigned long delay_on_, unsigned long delay_off_, bool on_) {
    this->pin = gpio;
    this->delay_on = delay_on_;
    this->delay_off = delay_off_;
    this->on = on_;
    this->off = !on_;
    this->state = this->off;
};

void digitalBlinkingLED::Clear() {
    digitalWrite(this->pin, this->off);
    this->state = 0;
    this->time = 0;
};

void digitalBlinkingLED::Update() {
    if (this->state && this->time <= millis()) {
        this->OFF();
    } else if (!this->state && this->time <= millis()) {
        this->ON();
    };
};

void digitalBlinkingLED::Begin() {
    digitalWrite(this->pin, this->on);
    this->state = 1;
    this->time = millis() + this->delay_on;
};

void digitalBlinkingLED::ON() {
    digitalWrite(this->pin, this->on);
    this->state = 1;
    this->time = millis() + this->delay_on;
};

void digitalBlinkingLED::OFF() {
    digitalWrite(this->pin, this->off);
    this->state = 0;
    this->time = millis() + this->delay_off;
};
