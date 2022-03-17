// BlinkingLED.h

#ifndef BLINKING_LED_H
#define BLINKING_LED_H

#include <Arduino.h>

class analogBlinkingLED {
    private:
        uint8_t pin;
        bool state;
        int on;
        int off;
        unsigned long delay_on;
        unsigned long delay_off;
        unsigned long time;
    public:
        analogBlinkingLED(uint8_t gpio, unsigned long delay_on_, unsigned long delay_off_, int on_, int off_);
        void Clear();
        void Update();
        void Begin();
        void ON();
        void OFF();
};

class digitalBlinkingLED {
    private:
        uint8_t pin;
        bool state;
        bool on;
        bool off;
        unsigned long delay_on;
        unsigned long delay_off;
        unsigned long time;
    public:
        digitalBlinkingLED(uint8_t gpio, unsigned long delay_on_, unsigned long delay_off_, bool on_);
        void Clear();
        void Update();
        void Begin();
        void ON();
        void OFF();
};

#endif /* BLINKING_LED_H */