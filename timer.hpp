#pragma once

#include <mach/mach_time.h>

/**
 *  A simple timer class that accesses the system's high resolution
 *  timers. There will be a specialized version for each platform. For
 *  now it only works on OS X.
 */
class timer {
  uint64_t _start;
  uint64_t _stop;

public:
  void start() {
    _stop = 0;
    _start = mach_absolute_time();
  }

  void stop() {
    _stop = mach_absolute_time();
  }

  int64_t elapsed() const {
    return (_stop - _start);
  }

  int64_t elapsedNS() const {
    mach_timebase_info_data_t tbi;
    
    mach_timebase_info(&tbi);

    return elapsed() * tbi.numer / tbi.denom;
  }

  timer operator-(timer rhs) {
    timer r;
    r._start = rhs.elapsed();
    r._stop = elapsed();
    return r;
  }
};
