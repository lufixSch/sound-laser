#include "speaker.hpp"

#define WORD_SIZE 3

Speaker* Speaker::instance_ { nullptr };

Speaker* Speaker::instance() {
  if (instance_ == nullptr) {
    instance_ = new Speaker();
  }

  return instance_;
}

void Speaker::run() {
  auto start = std::chrono::high_resolution_clock::now();
  long long diff;

  char data[WORD_SIZE] = { conf, 0x00, 0x00 };

  while (true) {
    start = std::chrono::high_resolution_clock::now();

    // get data from queue
    data[1] = 0x12;
    data[2] = 0xAB;

    spi.write(data, WORD_SIZE);

    auto diff_us
        = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start)
              .count()
        / 1000;
    bcm2835_delayMicroseconds(10 - (uint64_t)diff_us);
  }
}

std::thread* Speaker::run_thread() {
  loop = new std::thread(&Speaker::run, this);
  return loop;
}