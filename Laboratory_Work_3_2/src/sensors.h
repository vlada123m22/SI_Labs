#ifndef SENSORS_H
#define SENSORS_H

#include <OneWire.h>
#include <DallasTemperature.h>
#include "filters.h"
#include "globals.h"

extern OneWire oneWire;
extern DallasTemperature tempSensor;
extern SaltPepperFilter ultrasonicSaltPepperFilter;
extern WeightedAverageFilter ultrasonicWeightedFilter;
extern SaltPepperFilter temperatureSaltPepperFilter;
extern WeightedAverageFilter temperatureWeightedFilter;

#endif
