#include <Arduino.h>
#include "airbase_response.h"

#ifndef DAIKIN_CONTROLLER_H_
#define DAIKIN_CONTROLLER_H_

class DaikinController {
  public:
    static const char* getCurrentTemperatureAttribute(String airconMode);
    static const char* getFanSpeedAttribute(String airconMode);
    static const char* getFanDirectionAttribute(String airconMode);
};

#endif