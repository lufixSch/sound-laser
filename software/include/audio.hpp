#ifndef SOUND_LASER_AUDIO_HPP
#define SOUND_LASER_AUDIO_HPP

#include "blocking_queue.hpp"
#include "hal/pcm.hpp"
#include "modulation.hpp"
#include "speaker.hpp"

#include <array>
#include <thread>
#include <vector>

class AudioProcessor {
  static AudioProcessor* instance_;

  std::shared_ptr<PCM> pcm_dev;
  std::thread* record_loop;
  std::thread* loop;

  BlockingQueue<std::vector<char>> samples;

  std::vector<sample_t> mapValues(std::vector<char> in);

  protected:
  AudioProcessor();

  public:
  size_t sampling_rate;
  size_t frame_size;

  static AudioProcessor* instance();
  void configure(size_t sampling_rate, size_t frame_size);

  void record();
  void record_thread();

  void run();
  void run_thread();
};

#endif