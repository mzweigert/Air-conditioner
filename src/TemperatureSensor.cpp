#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor() {
  _dht->begin();
}

float TemperatureSensor::readTemperature() {
  float temperatures;
  for (int i = 0; i<5; i++) {
    temperatures += _dht->readTemperature();
  }
  return temperatures / 5;
}
