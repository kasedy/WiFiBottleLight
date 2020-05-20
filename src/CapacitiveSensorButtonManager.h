#pragma once

#include "LightControllerService.h"
#include "CapacitiveSensorButton.h"


class CapacitiveSensorButtonManager {
  CapacitiveSensorButton capacitiveSensorButton;
  LightController* lightController;
  ESP8266React* esp8266react;
  uint8_t lastChangeBrightness;
  bool lightScrollDirectionUp;
public:
  CapacitiveSensorButtonManager(uint8_t sendPin, uint8_t receivePin, LightControllerService* lightControllerService, ESP8266React* esp8266react);
  inline void loop() { capacitiveSensorButton.loop(); }

private:
  void handler(uint8_t numberClicks, CapacitiveSensorButton::EventType eventType);
  
  void onClickHandler();
  void onDoubleClickHandler();
  void onMultipleClicksHandler();
  void onLongPressHandler(bool isFirst);
};