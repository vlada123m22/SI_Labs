#pragma once
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "globals.h"

#ifndef FILTERS_H
#define FILTERS_H

class SaltPepperFilter {
  float window[FILTER_WINDOW_SIZE];
  int index = 0;
  bool filled = false;

public:
  float filterValue(float newVal);
};

class WeightedAverageFilter {
  float window[FILTER_WINDOW_SIZE];
  int index = 0;
  bool filled = false;

public:
  float filterValue(float newVal);
};

#endif
