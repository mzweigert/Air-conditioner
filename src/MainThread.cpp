#include "MainThread.h"

MainThread::MainThread() : Thread(0, 0) {
  this->_fanController = new FanController();
  auto const run = std::bind(&MainThread::onLoop, this);
  Thread::onRun(run);
}

void MainThread::onLoop() {
  
}
