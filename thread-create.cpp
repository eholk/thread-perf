/**
 * This test attempts to get the minimum overhead for creating and
 * joining a single thread.
 */

#include <iostream>

#include "timer.hpp"

const int num_iter = 10000;

using namespace std;

void *thread_func(void *arg) 
{
  return NULL;
}

int main() 
{
  getpid();

  timer t_base;
  t_base.start();
  for(int i = 0; i < num_iter; ++i) {
    getpid();
  }
  t_base.stop();

  timer t_thread;
  pthread_t thread;
  
  t_thread.start();
  for(int i = 0; i < num_iter; ++i) {
    getpid();
    pthread_create(&thread, NULL, thread_func, NULL);
    pthread_join(thread, NULL);
  } 
  t_thread.stop();

  cout << "Time per null loop iteration: "
       << t_base.elapsedNS() / num_iter << endl;
  cout << "Time per thread loop iteration: "
       << t_thread.elapsedNS() / num_iter << endl;
  cout << "Time for thread create/join: "
       << (t_thread - t_base).elapsedNS() / num_iter << endl;  

  return 0;
}
