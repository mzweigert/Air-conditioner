#include "Wire.h"
#include "MainThread.h"

MainThread *mainThread = new MainThread();
void setup() {
  Serial.begin(9600);
}

void loop() {
  mainThread->loop();
}