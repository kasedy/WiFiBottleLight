#include "LightControllerService.h"

static const char* STATE_PARAM PROGMEM = "state";
static const char* BRIGHTNESS_PARAM PROGMEM = "brightness";
static const char* SPEED_PARAM PROGMEM = "speed";
static const char* EFFECT_PARAM PROGMEM = "effect";
static const char* EFFECT_LIST_PARAM PROGMEM = "effect_list";

#define LIGHT_SETTINGS_SOCKET_PATH "/ws/light"
#define UPDATE_THROTTLE_MS 100

static void webSocketSerializer(LightController& lightController, JsonObject& json) {
  json[FPSTR(STATE_PARAM)] = lightController.isOn();
  json[FPSTR(BRIGHTNESS_PARAM)] = lightController.getLightBrightness();
  if (lightController.supportsAnimation()) {
    json[FPSTR(SPEED_PARAM)] = lightController.getAnimationSpeed();
    json[FPSTR(EFFECT_PARAM)] = lightController.getCurrentAnimationIndex();
    JsonArray effectOptions = json.createNestedArray(FPSTR(EFFECT_LIST_PARAM));
    for (size_t index = 0; index < lightController.getAnimationCount(); ++index) {
      effectOptions.add(lightController.getAnimationName(index));
    }
  }
}

static void webSocketDeserializer(JsonObject& json, LightController& lightController) {
  lightController.setStateOn(json[FPSTR(STATE_PARAM)] | lightController.isOn());
  lightController.setLightBrightness(json[FPSTR(BRIGHTNESS_PARAM)] | lightController.getLightBrightness());
  if (lightController.supportsAnimation()) {
    lightController.setAnimationSpeed(json[FPSTR(SPEED_PARAM)] | lightController.getAnimationSpeed());
    lightController.setAnimationByIndex(json[FPSTR(EFFECT_PARAM)] | lightController.getCurrentAnimationIndex());
  }
}

LightControllerService::LightControllerService(
    const std::vector<LightController::PinStatus> &pinsGpio, 
    const std::vector<Effect> &effects,
    AsyncWebServer* webServer) : 
    StatefulService<LightController>(pinsGpio, effects),
    webSocketService(webSocketSerializer, 
                    webSocketDeserializer, 
                    this,
                    webServer,
                    LIGHT_SETTINGS_SOCKET_PATH),
    lastUpdatePushTime(0) {
  addUpdateHandler(std::bind(&LightControllerService::resetLastUpdatePushTime, this));
}

void LightControllerService::resetLastUpdatePushTime() {
  lastUpdatePushTime = millis();
  _state.resetDirtyFlag();
}

void LightControllerService::loop() {
  if (_state.isDirty() && millis() - lastUpdatePushTime > UPDATE_THROTTLE_MS) {
    callUpdateHandlers(F("Internal change"));
  }
  _state.loop(); 
}