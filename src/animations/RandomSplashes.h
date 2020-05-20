#pragma once

#include <stdint.h>
#include <vector>

#include "animations/BaseAnimation.h"

class RandomSplashes : public BaseAnimation {
public:
  struct BrightnessSettings {
    uint8_t minBrightness;
    uint8_t maxBrightness;
  };

  RandomSplashes(LightController* lightController, int8_t speed = 0);
  RandomSplashes(
    LightController* lightController, 
    std::vector<BrightnessSettings> brightnessSettings, 
    int8_t speed = 0);
  virtual ~RandomSplashes();

private:
  int8_t speed; // each unit increases (or decreases if negative) speed by 10%

protected:
  std::vector<BrightnessSettings> brightnessSettings;
  unsigned long getUpdateInterval();
  void setLedBrightness(uint8_t index, BrightnessSettings brigtnessRange);
};
