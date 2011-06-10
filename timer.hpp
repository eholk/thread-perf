#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
typedef UINT64 uint64_t;
typedef INT64  int64_t;
#else
#include <inttypes.h>
#endif

#ifdef __MACH__
#include <mach/mach_time.h>
#endif

#ifdef __linux__
#include <time.h>
#endif

/**
 *  A simple timer class that accesses the system's high resolution
 *  timers. There will be a specialized version for each platform.
 */
class timer {
  uint64_t _start;
  uint64_t _stop;

#ifdef __MACH__
  uint64_t _time() const {
    return mach_absolute_time();
  }
#endif

#ifdef __linux__
  uint64_t _time() const {
    timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return (uint64_t)t.tv_sec * 1000000000 + t.tv_nsec;
  }
#endif  

#ifdef _WIN32
  uint64_t _time() const {
    LARGE_INTEGER qpc;
    QueryPerformanceCounter(&qpc);
    return qpc.QuadPart;
  }
#endif

public:
  void start() {
    _stop = 0;
    _start = _time();
  }

  void stop() {
    _stop = _time();
  }

  int64_t elapsed() const {
    return (_stop - _start);
  }

  int64_t elapsedNS() const {
#ifdef __MACH__
    mach_timebase_info_data_t tbi;
    
    mach_timebase_info(&tbi);

    return elapsed() * tbi.numer / tbi.denom;
#endif
#ifdef __linux__
    return elapsed();
#endif
#ifdef _WIN32
    LARGE_INTEGER qpf;
    QueryPerformanceFrequency(&qpf);
    return elapsed() * 1000000000 / qpf.QuadPart;
#endif
  }

  timer operator-(timer rhs) {
    timer r;
    r._start = rhs.elapsed();
    r._stop = elapsed();
    return r;
  }
};
