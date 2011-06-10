/**
 * This test attempts to get the minimum overhead for creating and
 * joining a single thread.
 */

#include <iostream>

#include "timer.hpp"
#include "common.hpp"

const int num_iter = 10000;

using namespace std;

int main() 
{
#ifdef _WIN32
    GetCurrentProcessId();
#else
    getpid();
#endif

  timer t_base;
  t_base.start();
  for(int i = 0; i < num_iter; ++i) {
#ifdef _WIN32
    GetCurrentProcessId();
#else
    getpid();
#endif
  }
  t_base.stop();

  timer t_thread;
  
  t_thread.start();
  for(int i = 0; i < num_iter; ++i) {
#ifdef _WIN32
    GetCurrentProcessId();
#else
    getpid();
#endif
    thread t;
    t.terminate();
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
