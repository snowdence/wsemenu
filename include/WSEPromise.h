#ifndef WSEPromise_h
#define WSEPromise_h

#if defined(WIRING) && WIRING >= 100
#include <Wiring.h>
#elif defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class WSEPromise
{
public:
  WSEPromise()
  {
    this->_timer.time = 1000;
  }
  WSEPromise(unsigned long _t)
  {
    this->_timer.time = _t;
  }

  unsigned long getEllapsed()
  {
    return millis() - this->_timer.last;
  }
  void start()
  {
    this->reset();
    this->_timer.started = true;
    this->_waiting = true;
  }

  unsigned long stop()
  {
    this->_timer.started = false;
    this->_waiting = false;
    return this->getEllapsed();
  }
  void restart()
  {
    if (!this->done())
    {
      this->_timer.started = true;
      this->_waiting = true;
    }
  }

  bool done()
  {
    if (!this->_timer.started)
      return false;
    if ((millis() - this->_timer.last) >= this->_timer.time)
    {
      this->_timer.done = true;
      this->_waiting = false;
      executeCallback();
      return true;
    }
    return false;
  }

  bool waiting()
  {
    return (this->_timer.started && !this->done()) ? true : false;
  }
  void setTime(unsigned long t) { this->_timer.time = t; }
  unsigned long getTime() { return this->_timer.time; }
  void reset()
  {
    this->stop();
    this->_timer.last = millis();
    this->_timer.done = false;
  }

  boolean started()
  {
    return this->_timer.started;
  }
  ~WSEPromise() {}

  //Hook function
  void executeDefaultFunc() {}
  void executeHook()
  {
    (this->hookExecuteFunc != nullptr) ? hookExecuteFunc() : executeDefaultFunc();
  }
  void executeCallback()
  {
    (this->hookCallbackFunc != nullptr) ? hookCallbackFunc() : executeDefaultFunc();
  }
  WSEPromise *setHookExecuteFunc(void (*function)())
  {
    this->hookExecuteFunc = function;
    return this;
  }

  WSEPromise *setHookCallbackFunction(void (*function)())
  {
    this->hookCallbackFunc = function;
    return this;
  }

private:
  struct WSEPromiseTimer
  {
    unsigned long int time;
    unsigned long int last;
    boolean done;
    boolean started;
  };
  struct WSEPromiseTimer _timer;
  boolean _waiting;
  void (*hookExecuteFunc)();
  void (*hookCallbackFunc)();
};

#endif