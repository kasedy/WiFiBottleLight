#include "HomeAssistantMqttService.h"

#include <ArduinoJson.h>

#include "dbg.h"

static const char* HOME_ASSISTANT_SETTINGS_ENDPOINT = "/rest/ha";
static const char* HOME_ASSISTANT_SETTINGS_FILE = "/config/ha";

static void homeAssistantMqttSettingsSerialize(HomeAssistantMqttSettings& settings, JsonObject& root) {
  root["name"] = settings.deviceDisplayName;
  DBG("Serialize called with %s\n", settings.deviceDisplayName.c_str());
}

static void homeAssistantMqttSettingsDeserialize(JsonObject& root, HomeAssistantMqttSettings& settings) {
  settings.deviceDisplayName = root["name"] | "";
  if (settings.deviceDisplayName.isEmpty()) {
    settings.deviceDisplayName = F("Cointreau Bottle");
  }
  DBG("Deserialize called with %s\n", settings.deviceDisplayName.c_str());
}


HomeAssistantMqttService::HomeAssistantMqttService(LightControllerService* lightControllerService, 
                                                   AsyncWebServer* server, 
                                                   FS* fs, 
                                                   SecurityManager* securityManager) : 
    _httpEndpoint(homeAssistantMqttSettingsSerialize,
                  homeAssistantMqttSettingsDeserialize,
                  this,
                  server,
                  HOME_ASSISTANT_SETTINGS_ENDPOINT,
                  securityManager,
                  AuthenticationPredicates::IS_AUTHENTICATED),
    _fsPersistence(homeAssistantMqttSettingsSerialize, 
                   homeAssistantMqttSettingsDeserialize, 
                   this, 
                   fs, 
                   HOME_ASSISTANT_SETTINGS_FILE) {}