#include"metrics.h"
#include<Arduino.h>

static unsigned long MetricsManager::timeMark = 0;
static unsigned long MetricsManager::timeMarkMicro = 0;

static void MetricsManager::markTime()
{
  timeMark = millis();
  timeMarkMicro = micros();
}
static unsigned long MetricsManager::getDelaySinceMarked()
{
  return millis() - timeMark;
}
