#ifndef SOUND_LASER_SPEAKER_OUT_HPP
#define SOUND_LASER_SPEAKER_OUT_HPP

#include "hal/spi.hpp"

#include <bcm2835.h>
#include <chrono>
#include <thread>

class Speaker {
  SPI spi;
  static Speaker* instance_;
  std::thread* loop;

  const char conf = 0x00;

  protected:
  Speaker() {};

  public:
  //  ~Speaker();

  Speaker(Speaker& other) = delete;
  void operator=(const Speaker&) = delete;

  static Speaker* instance();

  void run();
  std::thread* run_thread();
};

#endif