#include "airbase_response.h"

const char *csvSeparator = ",";
const char *kvSeparator = "=";
const char *hexSeparator = "%";

AirbasePayload* AirbasePayload::parseResponseBody(String responseBody) {
  AirbasePayload* response = new AirbasePayload();
  char* body = responseBody.begin();
  char* pair;
  while (pair = strtok_r(body, csvSeparator, &body)) {
    char* key = strtok_r(pair, kvSeparator, &pair);
    String* value = decode(strtok_r(pair, kvSeparator, &pair));
    Log.traceln("%s=%s", key, value->c_str());
    response->insert({key, value->c_str()});
    delete value;
  }
  return response;
}

String* AirbasePayload::decode(char* value) {
  String* decodedValue = new String();
  char* body = value;
  char* token;
  char* end;
  while (token = strtok_r(body, hexSeparator, &body)) {
    if (token != value) {
      decodedValue->concat((char) (int)strtol(token, &end, 16));
    } else {
      decodedValue->concat(token);
    }
  }
  return decodedValue;
}

String AirbasePayload::getAttribute(String key) {
  if (this->find(key) != this->end()) {
    return this->at(key);
  }
  return EMPTY;  
}

void AirbasePayload::setAttribute(String key, String value) {
  this->insert({key, value});
}