#include "HomeAssistantMqttBroker.h"

#include <ArduinoJson.h>

#include "LightControllerService.h"

static const char* CONFIG_MQTT_PAYLOAD_ON PROGMEM = "ON"; 
static const char* CONFIG_MQTT_PAYLOAD_OFF PROGMEM = "OFF";

static const char* STATE PROGMEM = "state";
static const char* BRIGHTNESS PROGMEM = "brightness";
static const char* EFFECT PROGMEM = "effect";
static const char* WHITE_VALUE PROGMEM = "white_value";

static String getDeviceUniqueName() {
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.macAddress(mac);
  char macStr[WL_MAC_ADDR_LENGTH * 2 + 1] = { 0 };
  for (int i = 0; i < WL_MAC_ADDR_LENGTH; ++i) {
    snprintf_P(&macStr[i * 2], 3, PSTR("%02x"), mac[i]);
  }
  String result = String(F("bottle")) + macStr;
  return result;
}

static void homeAssistantMqttMessageSerialize(LightController& lightController, JsonObject& doc) {
  doc[FPSTR(STATE)] = lightController.isOn() ? FPSTR(CONFIG_MQTT_PAYLOAD_ON) : FPSTR(CONFIG_MQTT_PAYLOAD_OFF);
  doc[FPSTR(BRIGHTNESS)] = lightController.getLightBrightness();
  if (lightController.getCurrentAnimationIndex() != -1) {
    doc[FPSTR(EFFECT)] = lightController.getCurrentAnimationName();
  }
  doc[FPSTR(WHITE_VALUE)] = lightController.getAnimationSpeed();
}

static void homeAssistantMqttMessageDeserialize(JsonObject& doc, LightController& lightController) {
  const char* state = doc[FPSTR(STATE)] | "";
  if (strcmp_P(state, CONFIG_MQTT_PAYLOAD_ON) == 0) {
    lightController.setStateOn(true);
  } else if (strcmp_P(state, CONFIG_MQTT_PAYLOAD_OFF) == 0) {
    lightController.setStateOn(false);
  }

  lightController.setLightBrightness(doc[FPSTR(BRIGHTNESS)] | lightController.getLightBrightness());
  lightController.setAnimationSpeed(doc[FPSTR(WHITE_VALUE)] | lightController.getAnimationSpeed());
  if (doc[FPSTR(EFFECT)].is<const char*>()) {
    lightController.setAnimationByName(doc[FPSTR(EFFECT)]);
  }
}

static String getSubscribeTopic() {
  return String(F("homeassistant/light/")) + getDeviceUniqueName();
}

static String getPublishTopic() {
  return getSubscribeTopic() + F("/state");
}

static String getConfigTopic() {
  return getSubscribeTopic() + F("/config");
}

HomeAssistantMqttBroker::HomeAssistantMqttBroker(LightControllerService* lightControllerService, 
                                                 HomeAssistantMqttService* homeAssistantMqttService, 
                                                 AsyncMqttClient* mqttClient) :
    lightControllerService(lightControllerService),
    homeAssistantMqttService(homeAssistantMqttService),
    mqttPubSub(homeAssistantMqttMessageSerialize, 
               homeAssistantMqttMessageDeserialize, 
               lightControllerService, 
               mqttClient, 
               getPublishTopic(), 
               getSubscribeTopic()) {
  mqttClient->onConnect(std::bind(&HomeAssistantMqttBroker::sendAutoDiscovery, this));
  homeAssistantMqttService->addUpdateHandler([this](String originId) { sendAutoDiscovery(); }, false);
}

void HomeAssistantMqttBroker::sendAutoDiscovery() {
  AsyncMqttClient* mqttClient = mqttPubSub.getMqttClient();
  if (!mqttClient->connected()) {
    return;
  }

  const LightController* lightController = lightControllerService->get();
  const HomeAssistantMqttSettings& homeAssistantSettings = homeAssistantMqttService->get();
  bool supportsAnimation = lightController->supportsAnimation();

  DynamicJsonDocument doc(1024);
  doc[F("schema")] = F("json");
  doc[F("unique_id")] = getDeviceUniqueName();
  doc[F("name")] = homeAssistantSettings.deviceDisplayName;
  doc[F("state_topic")] = getPublishTopic();
  doc[F("command_topic")] = getSubscribeTopic();
  doc[F("optimistic")] = false;
  doc[F("qos")] = 2;
  doc[F("retain")] = true;
  doc[FPSTR(BRIGHTNESS)] = true;
  doc[FPSTR(EFFECT)] = supportsAnimation;
  doc[FPSTR(WHITE_VALUE)] = true;

  if (supportsAnimation) {
    JsonArray effectList = doc.createNestedArray(F("effect_list"));
    for (size_t i = 0; i < lightController->getAnimationCount(); ++i) {
      effectList.add(lightController->getAnimationName(i));
    }
  }
  
  String output;
  serializeJson(doc, output);
  doc.clear();

  DBG("Sending discovery config: %s\n", output.c_str());
  mqttClient->publish(getConfigTopic().c_str(), 2, true, output.c_str(), output.length());
}