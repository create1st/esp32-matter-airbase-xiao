#include <ArduinoLog.h>
#include <Matter.h>
#include <WiFi.h>
#include <FunctionalInterrupt.h> 
#include "arduino_ext.h"

#ifndef MATTER_SUPPORT_H_
#define MATTER_SUPPORT_H_
#define DECOMMISSION_BUTTON_TIME_SEC 10

typedef enum {
    ACTION_IDLE = 0,
    ACTION_INITIATED,
    ACTION_IN_PROGRESS,
} ActionState;

class MatterHandler {
  public:
    void init();
    void connect();
    void loop();
  private:
    unsigned long startButtonPressedTime;
    static volatile ActionState buttonAction;
    // #include <FunctionalInterrupt.h> is required to attach function to interrupt 
    static void IRAM_ATTR pinStateChange(int pin);
};

#endif