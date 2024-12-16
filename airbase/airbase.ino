#include <ArduinoLog.h>
#include "arduino_ext.h"
#include "logging.h"
#include "wifi_support.h"
#include "matter_support.h"
#include "daikin.h"
#include "controller.h"
#include "hub.h"
#include "status.h"

// Set up the onboard button
unsigned long statusTimer = 0;
const int connectionWaitTime = 200; // msec
bool readyOn = false;
StatusIndicator statusIndicator;
WifiHandler wifiHandler;
MatterHandler matterHandler;
Airbase airbase;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BTN_BUILTIN, INPUT_PULLUP);
  statusIndicator.init();
  statusIndicator.on();
  LoggingHandler::connectSerial();
  statusIndicator.connecting();
  wifiHandler.connect();
  while (wifiHandler.isConnected()) {
    delay(connectionWaitTime);
  }
  while (!airbase.discover()) {
    delay(connectionWaitTime);
  }  
  // // // initHub();
  matterHandler.init();
  matterHandler.connect();
  while (!Matter.isDeviceCommissioned()) {
    statusIndicator.loop();
    delay(connectionWaitTime);    
    matterHandler.loop();
  }
  statusIndicator.ready();
  // discoverDevices();
  // printMemoryUsage();
  // testDaikin();
  // printMemoryUsage();
  // testDaikin();
  // printMemoryUsage();
  // testDaikin();
  // printMemoryUsage();
  Log.traceln("Starting:");
}

void loop() {  
  //Serial.println("light_sleep_enter");
  //esp_sleep_enable_timer_wakeup(1000000); //1 seconds
  //int ret = esp_light_sleep_start();
  //Serial.printf("light_sleep: %d\n", ret);
  statusIndicator.loop();
  //hubLoop();
  matterHandler.loop();
}

void testDaikin() {
  AirbasePayload* request = new AirbasePayload();
  AirbasePayload* response = airbase.getControlInfo();  
  if (response) {
    String airconMode = response->getAttribute(AirbaseAttributes::AIRCON_MODE);
    request->setAttribute(AirbaseAttributes::AIRCON_MODE, airconMode);
    request->setAttribute(AirbaseAttributes::POWER_STATUS, AirbaseAttributeValues::OFF);
    String temperature = response->getAttribute(DaikinController::getCurrentTemperatureAttribute(airconMode));
    request->setAttribute(AirbaseAttributes::TEMPERATURE_SET, temperature);
    String fanSpeed = response->getAttribute(DaikinController::getFanSpeedAttribute(airconMode));
    request->setAttribute(AirbaseAttributes::FAN_SPEED, fanSpeed);
    String fanDirection = response->getAttribute(DaikinController::getFanDirectionAttribute(airconMode));
    request->setAttribute(AirbaseAttributes::FAN_DIRECTION, fanDirection);
    delete response;
  }
  airbase.setControlInfo(request);
  delete request;
}

void printMemoryUsage() {
    Log.traceln("Memory usage:");
    Log.traceln("ESP heap size: %l", ESP.getHeapSize());
    Log.traceln("ESP free heap: %l", ESP.getFreeHeap());
    Log.traceln("ESP max alloc heap: %l", ESP.getMaxAllocHeap());
    Log.traceln("ESP min free heap: %l", ESP.getMinFreeHeap());
}
