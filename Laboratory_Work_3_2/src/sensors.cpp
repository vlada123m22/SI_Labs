#include "sensors.h"

OneWire oneWire(TEMP_SENSOR_PIN);
DallasTemperature tempSensor(&oneWire);

SaltPepperFilter ultrasonicSaltPepperFilter;
WeightedAverageFilter ultrasonicWeightedFilter;
SaltPepperFilter temperatureSaltPepperFilter;
WeightedAverageFilter temperatureWeightedFilter;
