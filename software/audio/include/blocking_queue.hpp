#ifndef SOUND_LASER_BLOCKING_QUQUE_HPP
#define SOUND_LASER_BLOCKING_QUQUE_HPP

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <stdlib.h>
#include <thread>
#include <unistd.h>

using namespace std;
template <class T> class BlockingQueue : public queue<T> {
  public:
  void push(T item) {
    {
      unique_lock<std::mutex> lck(lock);
      queue<T>::push(item);
    }
    not_empty.notify_one();
  }

  T pop() {
    unique_lock<std::mutex> lck(lock);
    not_empty.wait(lck, [this]() { return queue<T>::size() > 0; });

    T value = queue<T>::front();
    queue<T>::pop();
    return value;
  }

  bool notEmpty() { return !queue<T>::empty(); }

  private:
  std::mutex lock;
  condition_variable not_empty;
};

#endif