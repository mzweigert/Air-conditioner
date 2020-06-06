#ifndef FanController_h
#define FanController_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

const int minFanAnalogVal = 10;
const int maxFanAnalogVal = 100;

struct TemperatureRange {
        signed char minTemperature;
        signed char maxTemperature;
    
        TemperatureRange(signed char minTemperature, signed char maxTemperature) : 
        minTemperature(minTemperature),
        maxTemperature(maxTemperature) {}

        String toJson() {
            return (String) "{ \"minTemperature\" : " + minTemperature + ", \"maxTemperature\" : " + maxTemperature + " }";
        }
};

class FanController {
    private:
        signed char _power;
        TemperatureRange _range = TemperatureRange(18, 30);

    public:
        FanController();
        void setPowerByTemperature(float temperature);
        void setTemperatureRange(TemperatureRange range);
        TemperatureRange getTemperatureRange();
};

#endif