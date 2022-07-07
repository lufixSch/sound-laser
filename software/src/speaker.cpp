#include "speaker.hpp"

#define WORD_SIZE 3

Speaker* Speaker::instance_ { nullptr };

Speaker* Speaker::instance() {
  if (instance_ == nullptr) {
    instance_ = new Speaker();
  }

  return instance_;
}

void Speaker::configure(size_t sampling_rate, size_t dac_max_value, size_t dac_min_value) {
  this->sampling_rate = sampling_rate;
  dac_max = dac_max_value;
  dac_min = dac_min_value;
}

void Speaker::run() {
  auto start = std::chrono::high_resolution_clock::now();

  long long diff;
  char delay = (char)(1000000 / sampling_rate);

  char data[WORD_SIZE] = { conf, 0x00, 0x00 };

  while (true) {
    start = std::chrono::high_resolution_clock::now();

    auto sample = samples.pop();
    data[1] = (char)(sample >> 4);
    data[2] = (char)((sample & 0x000F) << 4);

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

dac_t Speaker::mapSamples(sample_t sample, size_t max_value) {
  return (dac_t)((sample * (dac_max - dac_min)) / max_value + dac_min);
}