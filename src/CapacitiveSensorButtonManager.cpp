#include "CapacitiveSensorButtonManager.h"

using namespace std::placeholders;

CapacitiveSensorButtonManager::CapacitiveSensorButtonManager(uint8_t sendPin, 
                                                             uint8_t receivePin, 
                                                             LightControllerService* lightControllerService) :
    capacitiveSensorButton(sendPin, receivePin, std::bind(&CapacitiveSensorButtonManager::handler, this, _1, _2)),
    lightController(lightControllerService->get()) {
}

void CapacitiveSensorButtonManager::handler(uint8_t numberClicks, CapacitiveSensorButton::EventType eventType) {
  if (eventType == CapacitiveSensorButton::Click) {
    if (numberClicks == 1) {
      onClickHandler();
    } else if (numberClicks == 2) {
      onDoubleClickHandler();
    } else if (numberClicks >= 20) {
      onMultipleClicksHandler();
    }
  } else if (eventType == CapacitiveSensorButton::HoldStart) {
    onLongPressHandler(true);
  } else if (eventType == CapacitiveSensorButton::Holding) {
    onLongPressHandler(false);
  }
}

void CapacitiveSensorButtonManager::onClickHandler() {
  lightController->toggleState();
}

void CapacitiveSensorButtonManager::onDoubleClickHandler() {
  lightController->setStateOn(true);
  lightController->nextAnimation();
}

void CapacitiveSensorButtonManager::onMultipleClicksHandler() {
  // TODO: ESP8266React should provide factory reset
  WiFi.disconnect(true);
  delay(200);
  ESP.reset();
}

void CapacitiveSensorButtonManager::onLongPressHandler(bool isFirst) {
  uint8_t now = (uint8_t) millis();
  if (isFirst) {
    if (!lightController->isOn()) {
      lightController->setLightBrightness(0);
      lightController->setStateOn(true);
      lightScrollDirectionUp = true;
    } else {
      lightScrollDirectionUp = !lightScrollDirectionUp;
    }
  } else if ((uint8_t) (now - lastChangeBrightness) < 15) {
    return;
  }
  lastChangeBrightness = now;
  uint8_t brightness = lightController->getLightBrightness();
  uint8_t step = 2; 
  if (brightness < 30) {
    step = 1;
  } else if (brightness > 140 && brightness < 190) {
    step = 3;
  } else if (brightness >= 190) {
    step = 4;
  }
  if (brightness > 255 - step) {
    lightScrollDirectionUp = false;
  } else if (brightness < step) {
    lightScrollDirectionUp = true;
  }
  lightController->setLightBrightness(brightness + (lightScrollDirectionUp ? step : -step));
}
