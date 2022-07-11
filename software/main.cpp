#include <chrono>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <vector>

#include "audio.hpp"
#include "speaker.hpp"

int main(int, char**) {
  std::cout << "Hello, world!\n";

  if (!bcm2835_init()) {
    std::cerr << "bcm2835_init failed. Are you running as root??\n";
    return 1;
  }

  Speaker* speaker = Speaker::instance();
  AudioProcessor* audio = AudioProcessor::instance();

  speaker->configure(100000, 4096, 0);
  audio->configure(8000, 512);

  auto spe = speaker->run_thread();
  auto aud = audio->run_thread();
  auto rec = audio->record_thread();

  spe->join();
  aud->join();
  rec->join();

  bcm2835_close();

  return 0;
}
