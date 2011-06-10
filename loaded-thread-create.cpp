/**
 * This test measures the time to create a thread as the number of
 * threads increases. Unlike many-thread-create, this still creates
 * threads one at a time.
 */

#include <iostream>
#include <vector>

#include "timer.hpp"
#include "common.hpp"

const int max_threads = 2500;
const int thread_step = 100;
const int num_iter = 10000;

using namespace std;

void do_threads(int n) 
{
  thread *threads = new thread[n];

  timer t;

  t.start();
  for(int i = 0; i < num_iter; ++i) {
    thread t;
    t.terminate();
  }

  t.stop();

  cout << "time per thread at " << n << " threads: " 
       << t.elapsedNS() / num_iter << endl;

  for(int i = 0; i < n; ++i) {
    threads[i].terminate();
  }

  delete [] threads;
}

int main() 
{
  for(int i = 0; i < max_threads; i += thread_step) {
    do_threads(i);
  }

  return 0;
}
