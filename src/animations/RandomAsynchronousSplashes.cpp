#include "animations/RandomAsynchronousSplashes.h"

#include "dbg.h"
#include "LightController.h"

RandomAsynchronousSplashes::RandomAsynchronousSplashes(LightController* lightController, int8_t speed) 
    : RandomAsynchronousSplashes(lightController, {}, speed) {
}

RandomAsynchronousSplashes::RandomAsynchronousSplashes(
    LightController* lightController, 
    std::vector<BrightnessSettings> bSettings,
    int8_t speed) 
    : RandomSplashes(lightController, bSettings, speed),
    ledInfo(new LedInfo[lightController->getLedCount()]) {
  DBG("RandomAsynchronousSplashes constructed!\n");
}

RandomAsynchronousSplashes::~RandomAsynchronousSplashes() {
  delete[] ledInfo;
  DBG("RandomAsynchronousSplashes destroyed!\n");
}

void RandomAsynchronousSplashes::handle() {
  if (lightController->isEffectChanged() 
      || lightController->isAnimationSpeedChanged()) {
    resetTimers(micros());
  }

  if (lightController->isMaxBrightensChanged()) {
    if (lightController->isOn()) {
      lightController->setAllPinValue(lightController->getLightBrightness());
      resetTimers(micros() + 500000);
    }
  }

  if (lightController->isStateOnChanged()) {
    if (!lightController->isOn()) {
      lightController->setAllPinValue(0);
    } else {
      resetTimers(micros());
    }
  }

  if (!lightController->isOn()) {
    return;
  }

  for (uint8_t index = 0; index < lightController->getLedCount(); ++index) {
    // time may overflow unsigned long
    unsigned long timeDiff = micros() - ledInfo[index].timeToChangeBrightness;
    if (((unsigned long) timeDiff <= (unsigned long) -timeDiff)) {
      setLedBrightness(index, nextBrightness(index));
      ledInfo[index].timeToChangeBrightness = micros() + getUpdateInterval();
    }
  }
}

RandomSplashes::BrightnessSettings RandomAsynchronousSplashes::nextBrightness(uint8_t index) {
  if (brightnessSettings.size() > 0) {
    uint8_t &brightnessSettingsIndex = ledInfo[index].brightnessSettingsIndex;
    if (brightnessSettingsIndex >= brightnessSettings.size()) {
      brightnessSettingsIndex = 0;
    }
    return brightnessSettings[brightnessSettingsIndex++];
  }
  return {0, 255};
}

void RandomAsynchronousSplashes::resetTimers(unsigned long newTime) {
  for (uint8_t index = 0; index < lightController->getLedCount(); ++index) {
    ledInfo[index].brightnessSettingsIndex = random(brightnessSettings.size());
    ledInfo[index].timeToChangeBrightness = newTime;
  }
}