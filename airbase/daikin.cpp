#include "esp32-hal.h"
#include "daikin.h"

bool Airbase::discover() {
  Log.traceln("Daikin Airbase network scan");
  NetworkUDP udp;
  IPAddress listenAddress(0, 0, 0, 0);
  int listenPort = 30000;
  udp.begin(listenAddress, listenPort);
  IPAddress apAddress(255, 255, 255, 255);
  int apPort = 30050;
  udp.beginPacket(apAddress, apPort);
  udp.print("DAIKIN_UDP/common/basic_info");
  udp.endPacket();
  delay(DISCOVER_RESPONSE_TIMEOUT);
  int packetSize = udp.parsePacket();
  if (packetSize) {
    Log.traceln("Daikin Airbase found: %p:%d", udp.remoteIP(), udp.remotePort());
    delete airbaseAddress;
    airbaseAddress = new IPAddress(udp.remoteIP());
    char responseBuffer[RESPONSE_BUFFER_SIZE];
    int len = udp.read(responseBuffer, RESPONSE_BUFFER_SIZE);
    Log.traceln("Daikin Airbase response: %s", responseBuffer);
    AirbasePayload* airbaseResponse = AirbasePayload::parseResponseBody(responseBuffer);
    Log.traceln("Daikin Airbase unit found: %s", airbaseResponse->getAttribute(AirbaseAttributes::DEVICE_NAME).c_str());
    delete airbaseResponse;
  }
  udp.stop();
  return packetSize != 0;
}

AirbasePayload* Airbase::getBasicInfo() {
  Log.traceln("getBasicInfo (%s)", airbaseAddress->toString().c_str());
  return sendCommand("/common/basic_info");
}

// Get date/time
// ret=OK,sta=2,cur=2024/9/12 23:58:31,reg=au,dst=0,zone=54
AirbasePayload* Airbase::getDateTime() {
  Log.traceln("getDateTime (%s)", airbaseAddress->toString().c_str());
  return sendCommand("/common/get_datetime");
}

// Reboot controller
// ret=OK
AirbasePayload* Airbase::reboot() {
  Log.traceln("reboot (%s)", airbaseAddress->toString().c_str());
  return sendCommand("/common/reboot");
}

// Get dealer info
// ret=OK,dealer_name=%2d,installer=%2d,contactNumber=%2d
AirbasePayload* Airbase::getDealerInfo() {
  Log.traceln("getDealerInfo (%s)", airbaseAddress->toString().c_str());
  return sendCommand("/aircon/get_dealer_info");
}

// Get zone settings
// ret=OK,zone_name=-%3b-%3b-%3b-%3b-%3b-%3b-%3b-,zone_onoff=0%3b0%3b0%3b0%3b0%3b0%3b0%3b0
AirbasePayload* Airbase::getZoneSetting() {
  Log.traceln("getZoneSetting (%s)", airbaseAddress->toString().c_str());
  return sendCommand("/aircon/get_zone_setting");
}

// Get quick timer
// ret=OK,t1_ena=0,t1_pow=1,t1_time=0,t2_ena=0,t2_pow=0,t2_time=735
AirbasePayload* Airbase::getQuickTimer() {
  Log.traceln("getQuickTimer (%s)", airbaseAddress->toString().c_str());
  return sendCommand("/aircon/get_quick_timer");
}

// Indoor/outdoor temperature sensor
// ret=OK,err=0,htemp=23,otemp=20
AirbasePayload* Airbase::getSensorInfo() {
  Log.traceln("getSensorInfo (%s)", airbaseAddress->toString().c_str());
  return sendCommand("/aircon/get_sensor_info");
}

// Model information
// ret=OK,err=0,model=NOTSUPPORT,type=N,humd=0,s_humd=7,en_zone=0,en_linear_zone=0,en_filter_sign=1,acled=1,land=0,elec=0,temp=1,m_dtct=0,ac_dst=au,dmnd=0,en_temp_setting=1,en_frate=1,en_fdir=0,en_rtemp_a=0,en_spmode=0,en_ipw_sep=0,en_scdltmr=0,en_mompow=0,en_patrol=0,en_airside=0,en_quick_timer=1,en_auto=0,en_dry=1,en_common_zone=0,cool_l=16,cool_h=32,heat_l=16,heat_h=32,frate_steps=3,en_frate_auto=1
AirbasePayload* Airbase::getModelInfo() {
  Log.traceln("getModelInfo (%s)", airbaseAddress->toString().c_str());
  return sendCommand("/aircon/get_model_info");
}

// Pooling information
// ret=OK,method=polling,notice_ip_int=3600,notice_sync_int=6
AirbasePayload* Airbase::getRemoteMethod() {
  Log.traceln("getRemoteMethod (%s)", airbaseAddress->toString().c_str());
  return sendCommand("/aircon/get_remote_method");
}

// Get all aircon parameters
// ret=OK,pow=0,mode=7,operate=2,bk_auto=2,stemp=25,dt1=25,dt2=25,f_rate=1,dfr1=1,dfr2=1,f_airside=0,airside1=0,airside2=0,f_auto=0,auto1=0,auto2=0,f_dir=0,dfd1=0,dfd2=0,filter_sign_info=0,cent=0,en_cent=0,remo=2
AirbasePayload* Airbase::getControlInfo() {
  Log.traceln("getControlInfo (%s)", airbaseAddress->toString().c_str());
  return sendCommand("/aircon/get_control_info");
}

// Set all aircon parameters
// ret=OK
AirbasePayload* Airbase::setControlInfo(AirbasePayload* airbaseRequest) {
  Log.traceln("setControlInfo (%s)", airbaseAddress->toString().c_str());
  return sendCommand("/aircon/set_control_info", airbaseRequest);
}

AirbasePayload* Airbase::sendCommand(char* commandUrl, AirbasePayload* airbaseRequest) {
  Log.traceln("sendCommand (%s),(%s)(%t)", airbaseAddress->toString().c_str(), commandUrl, airbaseRequest != NULL);
  AirbasePayload* responsePayload = NULL;
  String query;
  if (airbaseRequest != NULL) {
    bool firstParam = true;
    for (auto const& param : *airbaseRequest) {
        query += (firstParam ? "" : "&") + param.first + "=" + param.second;
        firstParam = false;
    }
  }
  String url = "http://" + airbaseAddress->toString() + "/skyfi" + commandUrl + (query.isEmpty() ? "" : "?" + query);
  Log.traceln("sendCommand (%s)", url.c_str());
  HTTPClient http;
  http.begin(url);
  int retries = 0;
  while (retries < MAX_RECONNECT_ATTEMPTS) {
    int httpCode = http.GET();
    Log.traceln("GET (%s), statusCode=%d, attempt=%d", url.c_str(), httpCode, retries);
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      responsePayload = AirbasePayload::parseResponseBody(payload);
      String returnCode = responsePayload->getAttribute(AirbaseAttributes::RETURN_CODE);
      if (!returnCode.equals(AirbaseAttributeValues::OK)) {
        Log.traceln("sendCommand (%s) returned_code=%s", url.c_str(), returnCode.c_str());
        responsePayload = NULL;
      }
      break;
    }
    delay(RECONNECT_PERIOD);
    retries++;
  }
  http.end();
  return responsePayload;
}