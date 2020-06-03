#ifndef FanController_h
#define FanController_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

const int minFanAnalogVal = 10;
const int maxFanAnalogVal = 100;

class FanController {
    public:
        FanController();
        void setPower(signed char power);
};

#endif