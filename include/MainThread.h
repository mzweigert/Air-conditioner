#ifndef MainThread_h
#define MainThread_h

#include "WiFiConnector.h"
#include "Thread.h"
#include "FanController.h"
#include "TemperatureSensor.h"

class MainThread : public Thread {
 private:
    FanController *_fanController;
    TemperatureSensor *_temperatureSensor;
   
    void onLoop();
 public:
  MainThread();
};

#endif
