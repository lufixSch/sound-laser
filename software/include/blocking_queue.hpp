#ifndef SOUND_LASER_BLOCKING_QUQUE_HPP
#define SOUND_LASER_BLOCKING_QUQUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>
#include <stdlib.h>
#include <thread>
#include <unistd.h>

using namespace std;
template <class T> class BlockingQueue : public queue<T> {
  public:
  T pop() {
    unique_lock<std::mutex> lck(readerMutex);
    while (queue<T>::empty()) {
      isEmpty.wait(lck);
    }
    T value = queue<T>::front();
    queue<T>::pop();
    return value;
  }

  bool notEmpty() { return !queue<T>::empty(); }

  private:
  std::mutex readerMutex;
  condition_variable isEmpty;
};

#endif