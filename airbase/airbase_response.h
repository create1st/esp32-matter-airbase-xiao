#include "WString.h"
#include <ArduinoLog.h>
#include <Arduino.h>
#include <map>

#ifndef AIRBASE_RESPONSE_H_
#define AIRBASE_RESPONSE_H_
#define RESPONSE_BUFFER_SIZE 1024

// Airbase response attributes
namespace AirbaseAttributes {
  const char RETURN_CODE[] = "ret"; // OK, PARAM NG
  const char MESSAGE[] = "msg"; // 404 Not Found
  const char MAC[] = "mac";
  const char SSID[] = "ssid";
  const char DEVICE_NAME[] = "name";
  const char DEVICE_TYPE[] = "type"; // aircon
  const char REGION[] = "reg"; // au
  const char DST[] = "dst"; // 0 ??
  const char FIRMWARE_VERSION[] = "ver"; // 1_2_1
  const char FIRMWARE_REVISION[] = "rev"; // 23
  const char ERROR[] = "err"; // 0
  const char LOCATION[] = "location"; // 0 ??
  const char ICON[] = "icon"; // 0 ??
  const char DISCOVERY_PORT[] = "port"; // 30050
  const char USER_ID[] = "id";
  const char PASSWORD[] = "pw";
  const char LPW_FLAG[] = "lpw_flag"; // 0 ??
  const char ADP_KIND[] = "adp_kind"; // 3 ??
  const char ADP_MODE[] = "adp_mode"; // run
  const char LED[] = "led"; // 1 ??
  const char EN_SET_ZONE[] = "en_setzone"; // 1 ??
  const char EN_CHANNEL[] = "en_ch"; // 1 ??
  const char HOLIDAY[] = "holiday"; // 0 ??
  const char EN_HOL[] = "en_hol"; // 0 ??
  const char SYNC_TIME[] = "sync_time"; // 0 ??
  const char ERROR_TYPE[] = "err_type"; // 0
  const char ERROR_CODE[] = "err_code"; // 0

  const char OPERATE[] = "operate"; // 2=DRY, 2=COLD, 1=HOT, 0=FAN, ???=AUTO
  const char BK_AUTO[] = "bk_auto"; // 2=DRY, 2=COLD, 1=HOT, 1=FAN, ???=AUTO

  // MODE
  const char POWER_STATUS[] = "pow"; // 0=OFF, 1=ON
  const char AIRCON_MODE[] = "mode"; // 7=DRY, 2=COLD, 1=HOT, 0=FAN, ???=AUTO

  // REMOTE CONTROL
  const char REMOTE_METHOD[] = "method"; // polling
  const char NOTICE_IP[] = "notice_ip_int"; // 3600 sec
  const char NOTICE_SYNC[] = "notice_sync_int"; // 6 sec

  // TEMPERATURE
  const char TEMPERATURE_SET[] = "stemp"; // AUTO=18-31, HOT=10-31, COLD=18-33
  const char TEMPERATURE_HEAT_RO[] = "dt1";
  const char TEMPERATURE_COOL_RO[] = "dt2";
  const char TEMPERATURE_HOME_RO[] = "htemp"; // inside temperature
  const char TEMPERATURE_OUTDOOR_RO[] = "otemp"; // outside temperature

  // FAN
  const char FAN_SPEED[] = "f_rate"; // 1=lvl1, 2=lvl3, 5=lvl3, 0=lvl_auto
  const char FAN_SPEED_HEAT_RO[] = "dfr1";
  const char FAN_SPEED_COOL_RO[] = "dfr2";
  const char FAN_DIRECTION[] = "f_dir"; // 0 for ducted system without control
  const char FAN_DIRECTION_HEAT_RO[] = "dfd1";
  const char FAN_DIRECTION_COOL_RO[] = "dfd2";
}

// Attribute values
namespace AirbaseAttributeValues {
  // return code
  const char OK[] = "OK";
  // switch
  const char OFF[] = "0";
  const char ON[] = "1";
  // mode
  const char DRY[] = "7";
  const char COOL[] = "2";
  const char HEAT[] = "1";
  const char FAN_ONLY[] = "0";
  // fan speed
  const char FAN_SPEED_1[] = "1";
  const char FAN_SPEED_2[] = "3";
  const char FAN_SPEED_3[] = "5";
  const char FAN_SPEED_AUTO[] = "0";
}

typedef std::map<String, String> AirbasePayloadBase;

class AirbasePayload : public AirbasePayloadBase {      
  public: 
    String getAttribute(String key);
    void setAttribute(String key, String value);
    static AirbasePayload* parseResponseBody(String responseBody);
  private:
    const String EMPTY;
    static String* decode(char* value);
};

#endif