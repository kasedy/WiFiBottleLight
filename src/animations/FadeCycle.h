#pragma once

#include <stdint.h>

#include "animations/BaseAnimation.h"

/*
 * Fade evenly from max brigtness to 0 and back;
 */
class FadeCycle : public BaseAnimation {
  uint8_t actualBrightness;
  int8_t step = -1;
  unsigned long lastUpdateTime = 0;

  void changeBrightness(uint8_t newBrightness);
  unsigned long getUpdateInterval();

public:
  constexpr static uint8_t pinsRequires = 1;

  FadeCycle(LightController* lightController);
  virtual ~FadeCycle();
  virtual void handle() override;
};