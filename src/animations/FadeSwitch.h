#pragma once

#include <stdint.h>

#include "animations/BaseAnimation.h"

/*
 * Fade on switch on-off.
 */
class FadeSwitch : public BaseAnimation {
  uint8_t currentBrightness = 0;
  unsigned long lastUpdateTime = 0;
  
  unsigned long getUpdateInterval();
  void updateBrightness(uint8_t newValue);
  uint8_t getEndBrightness() const;
  uint8_t getStartBrightness() const;
public:
  constexpr static uint8_t pinsRequires = 1;

  FadeSwitch(LightController* lightController);
  virtual ~FadeSwitch();
  virtual void handle() override;
};
