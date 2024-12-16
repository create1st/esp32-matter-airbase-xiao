#include <ArduinoLog.h>
#include <Matter.h>
#include <Preferences.h>
#include "matter_support.h"
#include "status.h"

#ifndef HUB_H_
#define HUB_H_

void initHub();
void discoverDevices();
void hubLoop();
bool matterStateChanged(int matterId, bool state);
void IRAM_ATTR hardwareStateChanged(int pin);

#endif