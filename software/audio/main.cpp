#include <chrono>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <vector>

#include "audio.hpp"
#include "speaker.hpp"
#include "table.hpp"

Table* Table::instance_ = { nullptr };

void exit_handler(int s) {
  Table::instance()->printQueueSizes();
  exit(0);
}

int main(int, char**) {
  std::cout << "Welcome to Sound Laser!\n";

  struct sigaction sig_int_handler = {
    .sa_flags = 0,
  };
  sig_int_handler.sa_handler = &exit_handler;
  sigemptyset(&sig_int_handler.sa_mask);
  sigaction(SIGINT, &sig_int_handler, NULL);

  // Table::instance()->configureSignalLen(100000);

  if (!bcm2835_init()) {
    std::cerr << "bcm2835_init failed. Are you running as root??\n";
    return 1;
  }

  Speaker* speaker = Speaker::instance();
  AudioProcessor* audio = AudioProcessor::instance();

  speaker->configure(100000, 4096, 0);
  audio->configure(16000, 512);

  const auto spe = speaker->run_thread();
  const auto aud = audio->run_thread();
  const auto rec = audio->record_thread();

  spe->join();
  aud->join();
  rec->join();

  bcm2835_close();

  return 0;
}
