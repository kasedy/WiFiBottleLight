#pragma once

#include <stdint.h>

#include "animations/BaseAnimation.h"

/*
 * Fade on switch on-off.
 */
class SingleLedFade : public BaseAnimation {
  const uint8_t brightnessOverlap; // when next led starts
  uint8_t currentLed;
  bool raising;
  unsigned long lastUpdateTime;

  uint8_t getNextLedIndex() const;
  uint8_t getBrightness(int led) const;
  unsigned long getUpdateInterval();
public:
  constexpr static uint8_t pinsRequires = 3;

  SingleLedFade(LightController *lightController, uint8_t brightnessOverlap);
  virtual ~SingleLedFade();
  virtual void handle() override;
};
