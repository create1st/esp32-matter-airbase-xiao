#include "status.h"

// hw_timer_t* StatusIndicator::ledTimer = NULL;
volatile bool StatusIndicator::ledOn = false;
// volatile bool StatusIndicator::lastLedOnState = false;
// volatile uint8_t StatusIndicator::ledr = 0;
// volatile uint8_t StatusIndicator::ledg = 0;
// volatile uint8_t StatusIndicator::ledb = 0;
// volatile uint8_t StatusIndicator::prevLedr = 0;
// volatile uint8_t StatusIndicator::prevLedg = 0;
// volatile uint8_t StatusIndicator::prevLedb = 0;

void ARDUINO_ISR_ATTR StatusIndicator::onTimer() {
  ledOn = !ledOn;
}

void StatusIndicator::init() {
  ledTimer = timerBegin(LED_STATUS_TIMER_FREQUENCY);
  // Attach onTimer function to our timer.
  timerAttachInterrupt(ledTimer, &onTimer);
  // Set alarm to call onTimer function every second (value in microseconds).
  // Repeat the alarm (third parameter) with unlimited count = 0 (fourth parameter).
  timerAlarm(ledTimer, LED_STATUS_TIMER_FREQUENCY, true, 0);
}

void StatusIndicator::loop() {
  if (lastLedOnState != ledOn) {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    if (ledOn) {
      r = ledr;
      g = ledg;
      b = ledb;
    }
    digitalWrite(LED_BUILTIN, r > 0 || b > 0 || g > 0 ? HIGH : LOW);
    // rgbLedWriteOrdered(RGB_BUILTIN, LED_COLOR_ORDER_RGB, r, g, b);
    lastLedOnState = ledOn;
  }
}

void StatusIndicator::updateLedColor(uint8_t r, uint8_t g, uint8_t b) {
  //rgbLedWriteOrdered(RGB_BUILTIN, LED_COLOR_ORDER_RGB, r, g, b);
  digitalWrite(LED_BUILTIN, r > 0 || b > 0 || g > 0 ? HIGH : LOW);
  ledr = r;
  ledg = g;
  ledb = b;
}

void StatusIndicator::on() {
  updateLedColor(255, 255, 255);
}

void StatusIndicator::off() {
  updateLedColor(0, 0, 0);
}

void StatusIndicator::connecting() {
  updateLedColor(254, 138, 24);
}

void StatusIndicator::ready() {
  updateLedColor(0, 100, 0);
}

void StatusIndicator::buildInButtonPressed() {
  prevLedr = ledr;
  prevLedg = ledg;
  prevLedb = ledb;
  updateLedColor(255, 128, 0);
}

void StatusIndicator::buildInButtonReleased() {
  updateLedColor(prevLedr, prevLedg, prevLedb);
}
