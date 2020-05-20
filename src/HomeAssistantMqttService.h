#pragma once

#include <FSPersistence.h>
#include <HttpEndpoint.h>
#include <StatefulService.h>

#include "LightController.h"
#include "LightControllerService.h"

struct HomeAssistantMqttSettings {
  String deviceDisplayName;
};

class HomeAssistantMqttService : public StatefulService<HomeAssistantMqttSettings> {
  HttpEndpoint<HomeAssistantMqttSettings> _httpEndpoint;
  FSPersistence<HomeAssistantMqttSettings> _fsPersistence;
public:
  HomeAssistantMqttService(
      LightControllerService* lightControllerService, 
      AsyncWebServer* server, 
      FS* fs, 
      SecurityManager* securityManager);

  inline void begin() { _fsPersistence.readFromFS(); }
  inline const HomeAssistantMqttSettings& get() const { return _state; }
};