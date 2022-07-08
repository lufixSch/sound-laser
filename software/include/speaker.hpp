#ifndef SOUND_LASER_SPEAKER_OUT_HPP
#define SOUND_LASER_SPEAKER_OUT_HPP

#include "audio.hpp"
#include "blocking_queue.hpp"
#include "hal/spi.hpp"
#include "modulation.hpp"

#include <bcm2835.h>
#include <chrono>
#include <thread>

typedef uint16_t dac_t;

class Speaker {
  static Speaker* instance_;

  SPI spi;
  std::thread* loop;

  const char conf = 0x00;

  protected:
  Speaker() {};

  public:
  size_t sampling_rate = 125e3;
  size_t dac_max = 4096;
  size_t dac_min = 0;
  BlockingQueue<dac_t> samples;
  //  ~Speaker();

  Speaker(Speaker& other) = delete;
  void operator=(const Speaker&) = delete;

  static Speaker* instance();
  void configure(size_t sampling_rate, size_t dac_max_value, size_t dac_min_value);

  void run();
  std::thread* run_thread();

  dac_t mapSamples(sample_t sample, size_t max_value);
};

#endif