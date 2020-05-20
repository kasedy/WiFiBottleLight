#pragma once

#include <AsyncMqttClient.h>
#include <MqttPubSub.h>

#include "LightControllerService.h"
#include "HomeAssistantMqttService.h"

class HomeAssistantMqttBroker {
  LightControllerService* lightControllerService;
  HomeAssistantMqttService* homeAssistantMqttService;
  MqttPubSub<LightController> mqttPubSub;
public:
  HomeAssistantMqttBroker(LightControllerService* lightControllerService, 
                          HomeAssistantMqttService* homeAssistantMqttService, 
                          AsyncMqttClient* mqttClient);

private:
  void sendAutoDiscovery();
};