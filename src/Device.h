#pragma once

#include <ESP8266React.h>

#include "CapacitiveSensorButtonManager.h"
#include "HomeAssistantMqttBroker.h"
#include "HomeAssistantMqttService.h"
#include "LightControllerService.h"

class Device {
  AsyncWebServer webServer;
  ESP8266React esp8266React;
  LightControllerService lightControllerService;
  HomeAssistantMqttService homeAssistantMqttService;
  HomeAssistantMqttBroker homeAssistantMqttBroker;
  CapacitiveSensorButtonManager capacitiveSensorButtonManager;
public:
  Device(FS* fs);

  void setup();
  void loop();
};