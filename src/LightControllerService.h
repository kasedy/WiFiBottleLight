#pragma once

#include <vector>
#include <StatefulService.h>
#include <SecurityManager.h>
#include <WebSocketTxRx.h>

#include "LightController.h"

class LightControllerService : public StatefulService<LightController> {
  WebSocketTxRx<LightController> webSocketService;
  uint32_t lastUpdatePushTime;
public:
  LightControllerService(
    const std::vector<LightController::PinStatus> &pinsGpio, 
    const std::vector<Effect> &effects,
    AsyncWebServer* webServer);

  void loop();
  inline LightController* get() { return &_state; }

private:
  void resetLastUpdatePushTime();
};