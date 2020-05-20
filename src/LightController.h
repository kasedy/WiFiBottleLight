#pragma once

#include "dbg.h"
#include "animations/BaseAnimation.h"

#include <Esp.h>

//TODO: rename into LightState or DeviceState
class LightController {
public:
  struct PinStatus {
    PinStatus(uint8_t gpio) : gpio(1, gpio), brightness(0) {}
    PinStatus(std::initializer_list<uint8_t> gpio) : gpio(gpio), brightness(0) {}
    const std::vector<uint8_t> gpio;
    uint8_t brightness;
  };

private:
  uint8_t lightBrightness;
  uint8_t animationSpeed;
  std::vector<PinStatus> pins;
  const std::vector<Effect> effects;
  BaseAnimation* currentEffect;
  uint8_t currentAnimationIndex;
  bool stateOn:1;

  // Reset every loop() call
  bool lightBrightnessChanged:1;
  bool stateOnChanged:1;
  bool effectChanged:1;
  bool animationSpeedChanged:1; 

  // Reset manualy
  bool dirtyFlag:1;

public:
  LightController(const std::vector<PinStatus> &pinsGpio, const std::vector<Effect> &effects);

  void loop();

  // GPIO control
  inline uint8_t getLedCount() const { return pins.size(); }
  inline uint8_t getLedBrightness(uint8_t pinIndex) const { return pins[pinIndex].brightness; }
  void setPinValue(uint8_t pinIndex, uint8_t brightness);
  void setAllPinValue(uint8_t brightness);
  
  // Animation
  inline bool supportsAnimation() const { return !effects.empty(); }
  inline size_t getAnimationCount() const { return effects.size(); }
  inline uint8_t getCurrentAnimationIndex() const { return currentAnimationIndex; }
  inline String getAnimationName(size_t index) const { return effects[index].name; }
  inline String getCurrentAnimationName() const { return effects[currentAnimationIndex].name; }
  void nextAnimation();
  void setAnimationByIndex(uint8_t animationIndex);
  void setAnimationByName(String effectName);

  // Brightness
  void setLightBrightness(uint8_t newMaxBrightness);
  inline uint8_t getLightBrightness() const { return lightBrightness; }

  // Speed
  void setAnimationSpeed(uint8_t newAnimationSpeed);
  inline uint8_t getAnimationSpeed() const { return animationSpeed; }

  // ON-OFF
  inline bool isOn() const { return stateOn; }
  inline void toggleState() { setStateOn(!isOn()); }
  inline void setStateOn(bool newStateOn) { 
    if (stateOn == newStateOn) {
      return;
    }
    stateOn = newStateOn;
    stateOnChanged = true;
  }

  // Dirty flags that reset every loop() call
  inline bool isEffectChanged() const { return effectChanged; }
  inline bool isMaxBrightensChanged() const { return lightBrightnessChanged; }
  inline bool isAnimationSpeedChanged() const { return animationSpeedChanged; }
  inline bool isStateOnChanged() const { return stateOnChanged; }
  inline bool isChanged() const {
    return isMaxBrightensChanged() 
        || isStateOnChanged() 
        || isEffectChanged() 
        || isAnimationSpeedChanged();
  }

  // Manual diry flag to track change
  inline void resetDirtyFlag() { dirtyFlag = false; }
  inline bool isDirty() const { return dirtyFlag; }
  inline bool getAndResetDirtyFlag() { 
    bool val = dirtyFlag; 
    dirtyFlag = false; 
    return val; 
  }
};