#ifndef PSM_h
#define PSM_h

#include "Arduino.h"

class PSM
{
public:
  PSM(unsigned char sensePin, unsigned char controlPin, unsigned int range, int mode = RISING, unsigned char divider = 1, unsigned char interruptMinTimeDiff = 0);

  void initTimer(uint16_t delay);

  void set(unsigned int value);

  long getCounter(void);
  void resetCounter(void);

  void stopAfter(long counter);

  unsigned int cps(void);
  unsigned long getLastMillis(void);

  unsigned char getDivider(void);
  void setDivider(unsigned char divider = 1);
  void shiftDividerCounter(char value = 1);

private:
  static inline void onZCInterrupt(void);
  static inline void calculateSkipFromZC(void);
  static inline void onPSMTimerInterrupt(void);
  void calculateSkip(void);
  void updateControl(bool forceDisable = true);

  unsigned char _sensePin;
  unsigned char _controlPin;
  unsigned int _range;
  unsigned char _divider = 1;
  unsigned char _dividerCounter = 1;
  unsigned char _interruptMinTimeDiff;
  volatile unsigned int _value = 0;
  volatile unsigned int _a = 0;
  volatile bool _skip = true;
  volatile long _counter = 0;
  volatile long _stopAfter = -1;
  volatile unsigned long _lastMillis = 0;

  bool _psmIntervalTimerInitialized = false;
  hw_timer_t* _psmIntervalTimer = nullptr;
};

extern PSM* _thePSM;

#endif
