#ifndef WebServer_h
#define WebServer_h

#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <FS.h>

#include "SPIFFSReadServer.h"
#include "FanController.h"
#include "TemperatureSensor.h"
#include "Definitions.h"
#include "ArduinoJson.h"

class WebServer {
 private:
  SPIFFSReadServer* _server;
  FanController* _fanController;
  TemperatureSensor* _temperatureSensor;

  void initEndpoints();

 public:
  WebServer(int port, FanController* _fanController, TemperatureSensor* _temperatureSensor);
  void loop();
};

#endif
