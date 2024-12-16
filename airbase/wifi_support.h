#include <ArduinoLog.h>
#include <WiFi.h>
#include "credentials.h"

#ifndef WIFI_SUPPORT_H_
#define WIFI_SUPPORT_H_

class WifiHandler {
  public:
    void connect();
    bool isConnected();
  private:
    static void onEvent(WiFiEvent_t event);
    static void showNetworkConnectionDetails();
};

#endif