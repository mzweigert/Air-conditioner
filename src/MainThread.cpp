#include "MainThread.h"

MainThread::MainThread() : Thread(0, 1000) {
  this->_fanController = new FanController();
  this->_temperatureSensor = new TemperatureSensor();
  initWiFiConnection();

  Thread *refreshFanPower = new Thread(2, 1000, std::bind(&MainThread::refreshFanPower, this));
  _threads.add(refreshFanPower);

  Thread *refreshServers = new Thread(3, 0, std::bind(&MainThread::refreshServers, this));
  _threads.add(refreshServers);

  auto const run = std::bind(&ThreadController::loop, &_threads);
  Thread::onRun(run);

}

void MainThread::initWiFiConnection() {
  boolean connected = WiFiConnector::connectToWiFi();
  if (connected) {
    _webSocketsServerRunner = new WebSocketsServerRunner(WEB_SOCKET_SERVER_PORT, _temperatureSensor, WEB_SOCKET_SERVER_ORIGIN);
    _webServer = new WebServer(WEB_SERVER_PORT, _fanController, _temperatureSensor);
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void MainThread::refreshFanPower() {
  float temperature = _temperatureSensor->readTemperature();
  _fanController->setPowerByTemperature(temperature);
}

void MainThread::refreshServers() {
  WiFiConnector::loop();
  if (WiFiConnector::isConnected()) {
    if (_webSocketsServerRunner == NULL) {
      _webSocketsServerRunner = new WebSocketsServerRunner(WEB_SOCKET_SERVER_PORT, _temperatureSensor, WEB_SOCKET_SERVER_ORIGIN);
    }
    if (_webServer == NULL) {
      _webServer = new WebServer(WEB_SERVER_PORT, _fanController, _temperatureSensor);
      digitalWrite(LED_BUILTIN, LOW);
    }
    _webSocketsServerRunner->loop();
    _webServer->loop();
  }
}
