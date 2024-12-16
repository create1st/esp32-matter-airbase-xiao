#include "hub.h"
#include <FunctionalInterrupt.h>

// MatterOnOffLight matterButtons[MAX_ZONES];
// Preferences lastStatePref[MAX_ZONES];
// bool zoneStateChanged[MAX_ZONES];

char fmtStrBuffer[20];

void initHub() {
  //   sprintf(fmtStrBuffer, "Button%d", MATTER_ID);
  //   lastStatePref[i].begin(fmtStrBuffer, false);
  //   sprintf(fmtStrBuffer, "ZoneState%d", MATTER_ID);
  //   bool lastOnOffState = lastStatePref.getBool(fmtStrBuffer, true);
  //   matterButton.begin(lastOnOffState);
  //   matterButton.onChangeOnOff(std::bind(matterStateChanged, MATTER_ID, std::placeholders::_1));    
  //  attachInterrupt(PIN_ID, std::bind(&hardwareStateChanged, PIN_ID), CHANGE);
}

void discoverDevices() {
  Log.traceln("Waiting for Matter device discovery...");
  // Update matter state based on PIN
}

bool matterStateChanged(int matterId, bool state) {
  // Log.traceln("Matter state changed for zone %d = %s\r\n", zone, state ? "ON" : "OFF");
  // store last zone state
  // sprintf(fmtStrBuffer, "ZoneState%d", zone);
  // lastStatePref[zone].putBool(fmtStrBuffer, state);  
  // bool currentState = getLedState(zone);
  // if (currentState != state) {
  //   //setButtonState(zone, state);
  //   pushButton(zone);
  //   getLedState(zone);
  // }
  // This callback must return the success state to Matter core
  return true;
}

void IRAM_ATTR hardwareStateChanged(int pin) { 
  // PIN state update
}

void hubLoop() {
  // Update Matter on PID change
}
