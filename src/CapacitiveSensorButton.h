#pragma once

#include <CapacitiveSensor.h>

#include "Average.h"

class CapacitiveSensorButton {
public:
  enum EventType {
    Click,
    HoldStart,
    Holding,
  };
  typedef std::function<void(uint8_t numberClicks, EventType eventType)> Handler;
private:
  CapacitiveSensor cs;
  Handler handler;
  AverageValueCalculator<uint32_t, uint32_t> touchSensorData;
  AverageValueCalculator<uint32_t, uint64_t> debugTouchSensorData;
  uint32_t lastDebug;
  uint32_t lastAverageCalculation;
  uint32_t lastDownTime;
  uint32_t lastUpTime;
  uint8_t rapidClickCounter;
  bool isPressed:1;
  bool startHandlingLongPress:1;
public:
  // sendPin is a pin with high resistor in front
  CapacitiveSensorButton(uint8_t sendPin, uint8_t receivePin, Handler handler = nullptr);
  inline void setHandler(Handler newHandler) { handler = newHandler; }
  void loop();
};
