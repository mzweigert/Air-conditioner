#include "FanController.h"

FanController::FanController() {
    pinMode(D1, OUTPUT); // sets the pins as outputs:
    analogWriteRange(100); // to have a range 1 - 100 for the fan
    analogWriteFreq(10000);
}

void FanController::setPower(signed char power) {
    if(power < minFanAnalogVal || maxFanAnalogVal > 100) {
        return;
    } else {
        analogWrite(D1, power);
    }
}