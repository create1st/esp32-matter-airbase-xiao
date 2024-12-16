#include <ArduinoLog.h>
#include <WiFi.h>
#include <AsyncUDP.h>
#include <IPAddress.h>
#include <HTTPClient.h>
#include "airbase_response.h"

#ifndef AIRBASE_H_
#define AIRBASE_H_
#define RESPONSE_BUFFER_SIZE 1024
#define MAX_RECONNECT_ATTEMPTS 200
#define RECONNECT_PERIOD 200
#define DISCOVER_RESPONSE_TIMEOUT 1000

class Airbase {
  public:
    bool discover();
    AirbasePayload* getBasicInfo();
    AirbasePayload* getDateTime();
    AirbasePayload* getDealerInfo();
    AirbasePayload* getZoneSetting();
    AirbasePayload* getQuickTimer();
    AirbasePayload* getSensorInfo();
    AirbasePayload* getModelInfo();
    AirbasePayload* getRemoteMethod();
    AirbasePayload* getControlInfo();
    AirbasePayload* setControlInfo(AirbasePayload* airbaseRequest);
    AirbasePayload* reboot();
  private:
    IPAddress* airbaseAddress = new IPAddress();
    AirbasePayload* sendCommand(char* commandUrl, AirbasePayload* airbaseRequest = NULL);
};

#endif
