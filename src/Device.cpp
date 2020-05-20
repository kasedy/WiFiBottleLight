#include "Device.h"

#include "animations/AllEffects.h"

Device::Device(FS* fs) :
    webServer(80),
    esp8266React(&webServer, fs),
    lightControllerService(LED_PINS, EFFECT_LIST, &webServer),
    homeAssistantMqttService(&lightControllerService, &webServer, fs, esp8266React.getSecurityManager()),
    homeAssistantMqttBroker(&lightControllerService, &homeAssistantMqttService, esp8266React.getMqttClient()),
    capacitiveSensorButtonManager(CAPACITIVE_SENSOR_SEND_PIN, CAPACITIVE_SENSOR_RECEIVE_PIN, &lightControllerService) {
  esp8266React.begin();
  homeAssistantMqttService.begin();
  webServer.begin();
}

void Device::loop() {
  esp8266React.loop();
  capacitiveSensorButtonManager.loop();
  lightControllerService.loop();
}