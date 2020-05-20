#include "LightController.h"

#include "helpers.h"
#include "animations/Effect.h"
#include "animations/NoAnimation.h"

LightController::LightController(const std::vector<PinStatus> &pinsGpio, const std::vector<Effect> &effects) :
    lightBrightness(255),
    animationSpeed(255 / 2),
    pins(pinsGpio), 
    effects(filter_vector(effects, [&](Effect e){ return pinsGpio.size() >= e.pinsRequires; })),
    currentEffect(nullptr),
    currentAnimationIndex(-1),
    stateOn(false),
    lightBrightnessChanged(false),
    stateOnChanged(false),
    effectChanged(false),
    dirtyFlag(false) {
  for (int i = 0; i < getLedCount(); ++i) {
    for (int gpio : pins[i].gpio) {
      DBG("Set pin %d to output\n", gpio);
      pinMode(gpio, OUTPUT);
      setPinValue(i, 0);
    }
  }
  if (effects.empty()) {
    currentEffect = new NoAnimation(this);
  } else {
    setAnimationByIndex(0);
  }
}

void LightController::setPinValue(uint8_t pinIndex, uint8_t brightness) {
  int pwmDuty = map(brightness, 0, 255, 0, 1023);
  for (int gpio : pins[pinIndex].gpio) {
    analogWrite(gpio, pwmDuty);
  }
  pins[pinIndex].brightness = brightness;
}

void LightController::setAllPinValue(uint8_t brightness) {
  for (uint8_t i = 0; i < getLedCount(); ++i) {
    setPinValue(i, brightness);
  }    
}

void LightController::setLightBrightness(uint8_t newMaxBrightness) {
  if (lightBrightness == newMaxBrightness) {
    return;
  }
  lightBrightness = newMaxBrightness;
  dirtyFlag = lightBrightnessChanged = true;
}

void LightController::setAnimationSpeed(uint8_t newAnimationSpeed) {
  if (animationSpeed == newAnimationSpeed) {
    return;
  }
  animationSpeed = newAnimationSpeed;
  dirtyFlag = animationSpeedChanged = true;
}

void LightController::setAnimationByName(String effectName) {
  for (size_t animationIndex = 0; animationIndex < effects.size(); ++animationIndex) {
    if (effectName == effects[animationIndex].name) {
      setAnimationByIndex(animationIndex);
      return;
    }
  }
}

void LightController::nextAnimation() {
  uint8_t animationIndex = getCurrentAnimationIndex();
  if (++animationIndex >= effects.size()) {
    animationIndex = 0;
  }
  setAnimationByIndex(animationIndex);
}

void LightController::setAnimationByIndex(uint8_t animationIndex) {
  if (currentAnimationIndex == animationIndex 
      || animationIndex == -1
      || animationIndex >= effects.size()) {
    return;
  }
  if (currentEffect) {
    delete currentEffect;
  }
  const Effect &effectInfo = effects[animationIndex];
  currentEffect = effectInfo.animationBuilder(this);
  dirtyFlag = effectChanged = true;
  currentAnimationIndex = animationIndex;
}

void LightController::loop() {
  currentEffect->handle();
  lightBrightnessChanged = false;
  stateOnChanged = false;
  effectChanged = false;
  animationSpeedChanged = false;
}