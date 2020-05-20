#include "animations/RandomSplashes.h"

#include "dbg.h"
#include "LightController.h"

RandomSplashes::RandomSplashes(LightController* lightController, int8_t speed) 
    : RandomSplashes(lightController, {}, speed) {
}

RandomSplashes::RandomSplashes(
    LightController* lightController, 
    std::vector<BrightnessSettings> bSettings,
    int8_t speed) 
    : BaseAnimation(lightController),
    speed(speed),
    brightnessSettings(bSettings) {
  DBG("RandomSplashes constructed!\n");
}

RandomSplashes::~RandomSplashes() {
  DBG("RandomSplashes destroyed!\n");
}

unsigned long RandomSplashes::getUpdateInterval() {
  int32_t multiplier = map(lightController->getAnimationSpeed(), 0, 255, -40, 40);
  multiplier += speed;
  unsigned long refreshInterval = random(1000000); // microseconds
  if (multiplier < 0) {
    refreshInterval += refreshInterval * (-multiplier) / 10;
  } else if (multiplier > 0) {
    refreshInterval = refreshInterval * 10 / (multiplier + 10);
  } 
  return refreshInterval;
}

void RandomSplashes::setLedBrightness(uint8_t index, BrightnessSettings brigtnessRange) {
  uint8_t minBrightness = map(brigtnessRange.minBrightness, 0, 255, 0, lightController->getLightBrightness());
  uint8_t maxBrightness = map(brigtnessRange.maxBrightness, 0, 255, 0, lightController->getLightBrightness());
  if (minBrightness == maxBrightness) {
    lightController->setPinValue(index, minBrightness);
  } else {
    while (true) {
      uint8_t newBrightness = random(minBrightness, maxBrightness + 1);
      if (newBrightness != lightController->getLedBrightness(index)) {
        lightController->setPinValue(index, newBrightness);
        break;
      }
    }
  }
}