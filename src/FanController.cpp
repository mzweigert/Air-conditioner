#include "FanController.h"

FanController::FanController() {
    pinMode(D1, OUTPUT); // sets the pins as outputs:
    analogWriteRange(100); // to have a range 1 - 100 for the fan
    analogWriteFreq(10000);
}

void FanController::setPowerByTemperature(float temperature) {
  signed char power = map(temperature, _range.minTemperature, _range.maxTemperature, minFanAnalogVal, maxFanAnalogVal);
  Serial.println((String) "Temp: " + temperature);
  Serial.println((String) "Power: " + power);
  if(power != this->_power) {
    this->_power = power;
        analogWrite(D1, power);
  }
}

void FanController::setTemperatureRange(TemperatureRange range) {
    this->_range = range;
}
TemperatureRange FanController::getTemperatureRange() {
    return this->_range;
}