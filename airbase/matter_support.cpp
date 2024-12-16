#include "matter_support.h"

volatile ActionState MatterHandler::buttonAction = ActionState::ACTION_IDLE;

void IRAM_ATTR MatterHandler::pinStateChange(int pin) { 
  buttonAction = ActionState::ACTION_INITIATED;
}

void MatterHandler::init() {
  Matter.begin();
  attachInterrupt(BTN_BUILTIN, std::bind(&pinStateChange, BTN_BUILTIN), FALLING);
}

void MatterHandler::connect() {  
  if (!Matter.isDeviceCommissioned()) {
    Log.traceln("Matter device is not commissioned");
    Log.traceln("Commission it to your Matter hub with the manual pairing code or QR code");
    Log.traceln("Manual pairing code: %s\n", Matter.getManualPairingCode().c_str());
    Log.traceln("QR code URL: %s\n", Matter.getOnboardingQRCodeUrl().c_str());
  } else {
    Log.traceln("Matter device is commissioned");
  }
}

void MatterHandler::loop() {
  if (buttonAction == ActionState::ACTION_INITIATED) {
    Log.traceln("Matter decommission button pressed");
    buttonAction = ActionState::ACTION_IN_PROGRESS;
    startButtonPressedTime = millis();
  } else if (buttonAction == ActionState::ACTION_IN_PROGRESS) {
    if (digitalRead(BTN_BUILTIN) == HIGH) {
      Log.traceln("Matter decommission button released");
      buttonAction = ActionState::ACTION_IDLE;
      return;
    }    
    unsigned long time = millis();
    unsigned long elapsedTime = (millis() - startButtonPressedTime) / 1000;
    if (elapsedTime > DECOMMISSION_BUTTON_TIME_SEC) {
      Log.traceln("Decommissioning!");
      buttonAction = ActionState::ACTION_IDLE;
      if (!Matter.isDeviceCommissioned()) {
        Log.traceln("Already decommissioned!");
      } else {
        Log.traceln("Matter device is commissioned-> Starting Decommission process");
        Matter.decommission();          
        Log.traceln("Decommission done!");
        ESP.restart();
      }
    }
  }
}