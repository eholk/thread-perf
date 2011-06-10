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

#ifdef _WIN32
class mutex {
  HANDLE _mutex;

public:
  mutex() {
    _mutex = CreateMutex(NULL, FALSE, NULL);
  }

  ~mutex() {
    CloseHandle(_mutex);
  }

  void lock() {
    WaitForSingleObject(_mutex, INFINITE);
  }

  void unlock() {
    ReleaseMutex(_mutex);
  }
};
#else
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
#endif

class thread {

#ifdef _WIN32
  static DWORD WINAPI s_run(LPVOID p) {
#else
  static void *s_run(void *p) {
#endif
    ((thread *)p)->run();

    return 0;
  }

  void *run() {
    _mutex.lock();
    _mutex.unlock();
 
    return NULL;
  }

#ifdef _WIN32
  HANDLE _thread;
#else
  pthread_t _thread;
#endif
  mutex _mutex;

public:
  thread(int stack_size = 16384)
  {
    _mutex.lock();

#ifdef _WIN32
    _thread = CreateThread(NULL, stack_size, s_run, this, 0, NULL);
#else
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, stack_size);
    CHECKED(pthread_create(&_thread, &attr, s_run, this));
#endif
  }

  ~thread() {
#ifdef _WIN32
    WaitForSingleObject(_thread, INFINITE);
    CloseHandle(_thread);
#else
    CHECKED(pthread_join(_thread, NULL));
#endif
  }

  void terminate() {
    _mutex.unlock();
  }
};
