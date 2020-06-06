#include "WebServer.h"

void WebServer::initEndpoints() {
  _server->on("/", [&]() {
    if (!_server->handleFileRead("/index.html"))
      _server->send(404, "text/plain", "404: Not Found");
  });

  _server->on("/getWebSocketServerAddress", [&]() {
    String response = "{ \"ip\" : \"" + WiFi.localIP().toString() + "\", \"port\" : " + WEB_SOCKET_SERVER_PORT + " }";
    _server->send(200, "application/json", response);
  });

  _server->on("/getCurrentTemperatureRange", [&]() {
    String json = this->_fanController->getTemperatureRange().toJson();
    _server->send(200, "application/json", json);
  });

  _server->on("/updateCurrentTemperatureRange", HTTP_PUT, [&]() {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, _server->arg("plain"));
    signed char minTemp = doc["minimumTemperature"];
    signed char maxTemp = doc["maximumTemperature"];
    if (minTemp < 20 || maxTemp > 35) {
      _server->send(200, "application/text", (String) "Temperature range must be between 20 and 35");
      return;
    }
    this->_fanController->setTemperatureRange(TemperatureRange(minTemp, maxTemp));
    _server->send(200, "application/text", (String) "Temperature range has been changed.");
  });
}

WebServer::WebServer(int port, FanController* fanController, TemperatureSensor* temperatureSensor) {
  this->_server = new SPIFFSReadServer(port);
  this->_fanController = fanController;
  this->_temperatureSensor = temperatureSensor;
  initEndpoints();
  SPIFFS.begin();
  _server->begin();
}

void WebServer::loop() {
  _server->handleClient();
}
