#ifndef SOUND_LASER_AUDIO_HPP
#define SOUND_LASER_AUDIO_HPP

#include "hal/pcm.hpp"

#include <array>
#include <thread>

class AudioProcessor {
  static AudioProcessor* instance_;

  PCM* pcm_dev;
  std::thread* record_loop;
  std::thread* loop;

  void mapValues(char* in, sample_t* out, size_t in_size);

  protected:
  AudioProcessor();

  public:
  static AudioProcessor* instance();

  void record(size_t frame_size);
  void record_thread(size_t frame_size);

  void run(size_t frame_size);
  void run_thread(size_t frame_size);
};

#endif