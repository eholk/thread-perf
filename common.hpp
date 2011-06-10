/**
 *  Common concurrency things each of the tests will use.
 */

#pragma once

#define CHECKED(call)						\
  {								\
    int res = (call);						\
    if(0 != res) {						\
      fprintf(stderr,						\
	      #call " failed in %s at line %d, result = %d "	\
	      "(%s) \n",					\
	      __FILE__, __LINE__, res, strerror(res));		\
      abort();							\
    }								\
  }

class mutex {
  pthread_mutex_t _mutex;

public:
  mutex() {
    CHECKED(pthread_mutex_init(&_mutex, NULL));
  }

  ~mutex() {
    CHECKED(pthread_mutex_destroy(&_mutex));
  }

  void lock() {
    CHECKED(pthread_mutex_lock(&_mutex));
  }

  void unlock() {
    CHECKED(pthread_mutex_unlock(&_mutex));
  }
};

class thread {
  static void *s_run(void *p) {
    return ((thread *)p)->run();
  }

  void *run() {
    _mutex.lock();
    _mutex.unlock();
 
    return NULL;
  }

  pthread_t _thread;
  mutex _mutex;

public:
  thread() 
  {
    _mutex.lock();
    CHECKED(pthread_create(&_thread, NULL, s_run, this));
  }

  ~thread() {
    CHECKED(pthread_join(_thread, NULL));
  }

  void terminate() {
    _mutex.unlock();
  }
};
