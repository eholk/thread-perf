/**
 * This test measures the time to create a thread as the number of
 * threads increases.
 */

#include <iostream>

#include "timer.hpp"
#include "common.hpp"

const int num_iter = 10000;

using namespace std;

void do_threads(int n) 
{
  timer t;

  t.start();

  thread *threads = new thread[n];

  for(int i = 0; i < n; ++i) {
    threads[i].terminate();
  }

  delete [] threads;

  t.stop();

  cout << "time per thread at " << n << " threads: " 
       << t.elapsedNS() / n << endl;
}

int main() 
{
  for(int i = 1; i <= num_iter; ++i) {
    do_threads(i);
  }

  return 0;
}
