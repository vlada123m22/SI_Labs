#include "filters.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

float SaltPepperFilter::filterValue(float newVal) {
  window[index++] = newVal;
  if (index >= FILTER_WINDOW_SIZE) {
    index = 0;
    filled = true;
  }
  int size = filled ? FILTER_WINDOW_SIZE : index;
  float min = window[0], max = window[0], sum = 0;
  for (int i = 0; i < size; i++) {
    if (window[i] < min) min = window[i];
    if (window[i] > max) max = window[i];
    sum += window[i];
  }
  float average = sum / size;
  if (abs(newVal - average) > SALT_PEPPER_THRESHOLD) return average;
  return newVal;
}

float WeightedAverageFilter::filterValue(float newVal) {
  window[index++] = newVal;
  if (index >= FILTER_WINDOW_SIZE) {
    index = 0;
    filled = true;
  }
  int size = filled ? FILTER_WINDOW_SIZE : index;
  float weightedSum = 0;
  float weightTotal = 0;
  for (int i = 0; i < size; i++) {
    float weight = i + 1;
    weightedSum += window[(index + i) % size] * weight;
    weightTotal += weight;
  }
  return weightedSum / weightTotal;
}
