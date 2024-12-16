#include <Arduino.h>

#ifndef STATUS_H_
#define STATUS_H_
#define LED_STATUS_TIMER_FREQUENCY 1000000 // frequency to 1Mhz

class StatusIndicator {
  public:
    void init();
    void connecting();
    void ready();
    void loop();    
    void on();
    void off();
    void buildInButtonPressed();
    void buildInButtonReleased();
  private:
    hw_timer_t *ledTimer = NULL;
    volatile uint8_t ledr = 0;
    volatile uint8_t ledg = 0;
    volatile uint8_t ledb = 0;
    volatile uint8_t prevLedr = 0;
    volatile uint8_t prevLedg = 0;
    volatile uint8_t prevLedb = 0;
    volatile bool lastLedOnState = false;
    static volatile bool ledOn;
    static void ARDUINO_ISR_ATTR onTimer();
    void updateLedColor(uint8_t r, uint8_t g, uint8_t b);
};

#endif