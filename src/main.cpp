#include <FS.h>

#include "EmergencyProtocol.h"
#include "Device.h"

Device* device;

void setup() {
#if LOGGING
  Serial.begin(74880, SERIAL_8N1, SERIAL_TX_ONLY);
  Serial.setDebugOutput(true);
#endif 
  EmergencyProtocol::checkOnActivation();
  SPIFFS.begin();
  device = new Device(&SPIFFS);
}

void loop() {
  device->loop();
}
