#pragma once

#include <vector>
#include <functional>
#include <WString.h>

#include "animations/NoAnimation.h"
#include "animations/FadeCycle.h"
#include "animations/FadeSwitch.h"
#include "animations/RandomAsynchronousSplashes.h"
#include "animations/RandomSynchronousSplashes.h"
#include "animations/RandomSplashesCompensated.h"
#include "animations/SingleLedFade.h"

using namespace std::placeholders;

template<class T, typename... Args>
BaseAnimation* baseAnimationConstructor(LightController* lightController, Args... args) {
  return new T(lightController, args...);
}

template<class T, class... Args>
Effect makeEffect(const __FlashStringHelper* name, Args&&... args) {
  auto bound = std::bind(&baseAnimationConstructor<T, Args...>, _1, std::forward<Args>(args)...);
  return {name, bound, T::pinsRequires};
}

inline Effect noAnimation() {
  return makeEffect<NoAnimation>(F("No animation"));
}

inline Effect effectFadeOnSwitch() {
  return makeEffect<FadeSwitch>(F("Fade on switch"));
}

inline Effect effectFadeInCycle() {
  return makeEffect<FadeCycle>(F("Fade in cycle"));
}

inline Effect effectFadeSingleLed() {
  return makeEffect<SingleLedFade>(F("Fade single led"), 255);
}

inline Effect effectRandomSplashes() {
  return makeEffect<RandomAsynchronousSplashes>(F("Random splashes"));
}

inline Effect effectRandomCompensatedSplashes() {
  return makeEffect<RandomSplashesCompensated>(F("Random compensated splashes"));
}

inline Effect effectRandomBlinks() {
  return makeEffect<RandomAsynchronousSplashes>(
    F("Random blinks"), 
    std::vector<RandomSplashes::BrightnessSettings>({{0, 0}, {255, 255}}));
}

inline Effect effectAsycFire() {
  return makeEffect<RandomAsynchronousSplashes>(
    F("Async fire"), 
    std::vector<RandomSplashes::BrightnessSettings>({{51, 255}}));
}

inline Effect effectAsycFlame() {
  return makeEffect<RandomAsynchronousSplashes>(
    F("Async flame"), 
    std::vector<RandomSplashes::BrightnessSettings>({
        {25, 255}, 
        {51, 255}, 
        {76, 255}, 
        {102, 255}, 
        {127, 255}, 
        {51, 255}, 
        {153, 255}, 
        {178, 255}, 
        {204, 255}}), 
    10);
}

inline Effect effectSyncFire() {
  return makeEffect<RandomSynchronousSplashes>(
    F("Sync fire"), 
    std::vector<RandomSplashes::BrightnessSettings>({{51, 255}}));
}

inline Effect effectSyncFlame() {
  return makeEffect<RandomSynchronousSplashes>(
    F("Sync flame"), 
    std::vector<RandomSplashes::BrightnessSettings>({
        {25, 255}, 
        {51, 255}, 
        {76, 255}, 
        {102, 255},
        {127, 255}, 
        {51, 255}, 
        {153, 255}, 
        {178, 255}, 
        {204, 255}}),
    10);
}

inline std::vector<Effect> allEffects() {
  return std::vector<Effect>({
    noAnimation(),
    effectRandomCompensatedSplashes(),
    effectFadeOnSwitch(),
    effectFadeSingleLed(),
    effectFadeInCycle(),
    effectRandomSplashes(),
    effectRandomBlinks(),
    effectAsycFire(),
    effectAsycFlame(),
    effectSyncFire(),
    effectSyncFlame(),
  });
}

inline std::vector<Effect> defaultEffects() {
  return std::vector<Effect>({
    effectRandomCompensatedSplashes(),
    effectFadeOnSwitch(),
    effectFadeSingleLed(),
  });
}

#define EFFECT_LIST (allEffects())