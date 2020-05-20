#pragma once

#include "animations/BaseAnimation.h"

/*
 * No animation. Just jump from one colour to another.
 */ 
class NoAnimation : public BaseAnimation {
public:
  constexpr static uint8_t pinsRequires = 1;

  NoAnimation(LightController *lightController);
  virtual ~NoAnimation();
  virtual void handle() override;
};