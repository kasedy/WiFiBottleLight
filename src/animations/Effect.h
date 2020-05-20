#pragma once

#include <functional>

class BaseAnimation;
class LightController;
class __FlashStringHelper;

struct Effect {
  const __FlashStringHelper* name;
  std::function<BaseAnimation* (LightController* lightController)> animationBuilder;
  uint8_t pinsRequires;
};
