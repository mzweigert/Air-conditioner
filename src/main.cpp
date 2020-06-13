#include "Wire.h"
#include "MainThread.h"

MainThread *mainThread;
void setup() {
  Serial.begin(115200);
  Wire.begin();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  mainThread = new MainThread();
}

void loop() {
  mainThread->loop();
}