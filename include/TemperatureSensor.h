#ifndef TemperatureSensor_h
#define TemperatureSensor_h

#include<SPI.h>
#include "DHT.h"

#define DHT11_PIN D2
#define DHTTYPE DHT11

class TemperatureSensor {
    private:
        DHT *_dht = new DHT(DHT11_PIN, DHTTYPE);
    public:
        float readTemperature();
        TemperatureSensor();
};

#endif