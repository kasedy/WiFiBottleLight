#pragma once

#include <HardwareSerial.h>
#include <pgmspace.h>

#ifndef LOGGING
  #define LOGGING false
#endif

#if LOGGING
  #define DBG(fmt, ...) Serial.printf_P(PSTR(fmt), ##__VA_ARGS__)
#else
  #define DBG(fmt, ...)
#endif
