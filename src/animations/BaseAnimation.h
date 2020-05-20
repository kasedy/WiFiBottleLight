#pragma once

#include "Effect.h"

class LightController;

class BaseAnimation {
protected:
  LightController* const lightController;

public:
  BaseAnimation(LightController* lightController) : lightController(lightController) {}
  virtual ~BaseAnimation() {}
  virtual void handle() = 0;
};