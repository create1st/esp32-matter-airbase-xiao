#include "wifi_support.h"

void WifiHandler::connect() {
  Log.traceln("Connecting to WiFi: %s", ssid);
  WiFi.onEvent(onEvent);
  WiFi.begin(ssid, pass);
}

bool WifiHandler::isConnected() {
  return WiFi.status() != WL_CONNECTED;
}

void WifiHandler::onEvent(WiFiEvent_t event) {
  switch (event) {
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      showNetworkConnectionDetails();
      break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Log.traceln("WiFi connection lost");
      break;
    default: break;
  }
}

void WifiHandler::showNetworkConnectionDetails() {
  Log.traceln("WiFi connection details");
  IPAddress ip = WiFi.localIP();
  Log.traceln("IP Address: %p", ip);
  Log.traceln("Network Information:");
  Log.traceln("SSID: %s", WiFi.SSID());
  Log.traceln("signal strength (RSSI): %d dBm", WiFi.RSSI());
  Log.traceln("MAC: %s", WiFi.macAddress().c_str());
  Log.traceln("Auto reconnect: %s", WiFi.getAutoReconnect() ? "ON": "OFF");
}
