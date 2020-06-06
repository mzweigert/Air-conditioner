#ifndef MainThread_h
#define MainThread_h

#include "WiFiConnector.h"
#include "Thread.h"
#include "FanController.h"
#include "TemperatureSensor.h"
#include "WebSocketsServerRunner.h"
#include "WebServer.h"
#include "ThreadController.h"
#include "Definitions.h"

class MainThread : public Thread {
 private:
    ThreadController _threads = ThreadController();
    WebSocketsServerRunner* _webSocketsServerRunner;
    WebServer* _webServer;
    FanController *_fanController;
    TemperatureSensor *_temperatureSensor;

    void refreshServers();
    void refreshFanPower();
    void initWiFiConnection();
 public:
  MainThread();
};

#endif
