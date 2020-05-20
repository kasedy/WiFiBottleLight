#include "animations/RandomSynchronousSplashes.h"

#include "dbg.h"
#include "LightController.h"

RandomSynchronousSplashes::RandomSynchronousSplashes(LightController* lightController, int8_t speed) 
    : RandomSynchronousSplashes(lightController, {}, speed) {
}

RandomSynchronousSplashes::RandomSynchronousSplashes(
    LightController* lightController, 
    std::vector<BrightnessSettings> bSettings,
    int8_t speed) 
    : RandomSplashes(lightController, bSettings, speed) {
  DBG("RandomSynchronousSplashes constructed!\n");
}

RandomSynchronousSplashes::~RandomSynchronousSplashes() {
  DBG("RandomSynchronousSplashes destroyed!\n");
}

void RandomSynchronousSplashes::handle() {
  if (lightController->isEffectChanged() 
      || lightController->isAnimationSpeedChanged()) {
    resetTimer(micros());
  }

  if (lightController->isMaxBrightensChanged()) {
    if (lightController->isOn()) {
      lightController->setAllPinValue(lightController->getLightBrightness());
      resetTimer(micros() + 500000);
    }
  }

  if (lightController->isStateOnChanged()) {
    if (!lightController->isOn()) {
      lightController->setAllPinValue(0);
    } else {
      resetTimer(micros());
    }
  }

  if (!lightController->isOn()) {
    return;
  }

  // time may overflow unsigned long
  unsigned long timeDiff = micros() - timeToChangeBrightness;
  if (((unsigned long) timeDiff <= (unsigned long) -timeDiff)) {
    BrightnessSettings brigtnessRange = nextBrightness();
    for (uint8_t index = 0; index < lightController->getLedCount(); ++index) {
      setLedBrightness(index, brigtnessRange);
    }
    timeToChangeBrightness = micros() + getUpdateInterval();
  }
}

RandomSplashes::BrightnessSettings RandomSynchronousSplashes::nextBrightness() {
  if (brightnessSettings.size() > 0) {
    if (brightnessSettingsIndex >= brightnessSettings.size()) {
      brightnessSettingsIndex = 0;
    }
    return brightnessSettings[brightnessSettingsIndex++];
  } 
  return {0, 255};
}

void RandomSynchronousSplashes::resetTimer(unsigned long newTime) {
  brightnessSettingsIndex = random(brightnessSettings.size());
  timeToChangeBrightness = newTime;
}