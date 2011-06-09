/**
 *  Common concurrency things each of the tests will use.
 */

#pragma once

class mutex {
  pthread_mutex_t _mutex;

public:
  mutex() {
    pthread_mutex_init(&_mutex, NULL);
  }

  ~mutex() {
    pthread_mutex_destroy(&_mutex);
  }

  void lock() {
    pthread_mutex_lock(&_mutex);
  }

  void unlock() {
    pthread_mutex_unlock(&_mutex);
  }
};

class thread {
  volatile bool running;

  static void *s_run(void *p) {
    return ((thread *)p)->run();
  }

  void *run() {
    _mutex.lock();
    _mutex.unlock();
 
    running = false;
    return NULL;
  }

  pthread_t _thread;
  mutex _mutex;

public:
  thread() 
    : running(false)
  {
    _mutex.lock();
    running = true;
    pthread_create(&_thread, NULL, s_run, this);
  }

  ~thread() {
    if(running) {
      terminate();
    }
    pthread_join(_thread, NULL);
  }

  void terminate() {
    _mutex.unlock();
  }
};
