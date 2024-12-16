#include "controller.h"

const char* DaikinController::getCurrentTemperatureAttribute(String airconMode) {
  return airconMode.equals(AirbaseAttributeValues::HEAT)
    ? AirbaseAttributes::TEMPERATURE_HEAT_RO
    : AirbaseAttributes::TEMPERATURE_COOL_RO;
}

const char* DaikinController::getFanSpeedAttribute(String airconMode) {
  return airconMode.equals(AirbaseAttributeValues::HEAT)
    ? AirbaseAttributes::FAN_SPEED_HEAT_RO
    : AirbaseAttributes::FAN_SPEED_COOL_RO;
}

const char* DaikinController::getFanDirectionAttribute(String airconMode) {
  return airconMode.equals(AirbaseAttributeValues::HEAT)
    ? AirbaseAttributes::FAN_DIRECTION_HEAT_RO
    : AirbaseAttributes::FAN_DIRECTION_COOL_RO;
}
