#include "Wire.h"
#include "MainThread.h"

MainThread *mainThread = new MainThread();
void setup() {
  Serial.begin(115200);

  mainThread = new MainThread();
}

void loop() {
  mainThread->loop();
}