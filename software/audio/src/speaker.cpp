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
  long long diff;
  uint64_t delay = (uint64_t)(1000000000 / sampling_rate);
  uint64_t sleep_offset = 100;

  std::cout << "Run Speaker Loop with a max delay of " << delay << "\n";

  char data[WORD_SIZE] = { conf, 0x00, 0x00 };

  // Table* table = Table::instance();

  auto entry = std::chrono::high_resolution_clock::now();
  auto start = std::chrono::high_resolution_clock::now();

  while (true) {
    auto sample = samples.pop();
    data[1] = (char)(sample >> 4);
    data[2] = (char)((sample & 0x000F) << 4);

    spi.write(data, WORD_SIZE);

    // auto nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(start - entry);
    // table->addSignal(sample, nsec);

    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start)
                    .count();
    auto diff_abs = (uint64_t)diff - sleep_offset <= delay ? diff - sleep_offset : delay;
    auto sleep = (delay - diff_abs) / 1000;
    // table->addDiff(sleep);
    // table->nextSignal();
    bcm2835_delayMicroseconds(sleep);
    start = std::chrono::high_resolution_clock::now();
  }
}

std::thread* Speaker::run_thread() {
  loop = new std::thread(&Speaker::run, this);
  pthread_t id = (pthread_t)(loop->native_handle());

  sched_param sched_params = { 2 };
  pthread_setschedparam(id, SCHED_FIFO, &sched_params);

  return loop;
}