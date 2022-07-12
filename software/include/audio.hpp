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

  BlockingQueue<std::vector<sample_t>> samples;

  protected:
  AudioProcessor();

  public:
  size_t sampling_rate;
  size_t frame_size;

  AudioProcessor(AudioProcessor& other) = delete;
  void operator=(const AudioProcessor&) = delete;

  static AudioProcessor* instance();
  void configure(size_t sampling_rate, size_t frame_size);

  void record();
  std::thread* record_thread();

  void run();
  std::thread* run_thread();

  float mapValue(sample_t in) { return ((float)in - pcm_dev->format_zero) / pcm_dev->format_max; };
};

#endif