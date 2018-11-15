// Include protector.
#ifndef __metrics_h__
#define __metrics_h__

class MetricsManager
{
  private:
    static unsigned long timeMark;
    static unsigned long timeMarkMicro;
  public:
    // func. pointers
    static void markTime();
    static unsigned long getDelaySinceMarked();
};

#endif // __metrics_h__ include protector.
