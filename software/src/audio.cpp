#include "audio.hpp"

#include <iostream>

AudioProcessor* AudioProcessor::instance_ { nullptr };

AudioProcessor* AudioProcessor::instance() {
  if (instance_ == nullptr) {
    instance_ = new AudioProcessor();
  }

  return instance_;
}

AudioProcessor::AudioProcessor() {
  // pcm_dev = std::make_shared<PCM>("bluealsa", 1, 44100);
}

void AudioProcessor::configure(size_t sampling_rate, size_t frame_size) {
  this->sampling_rate = sampling_rate;
  this->frame_size = frame_size;

  pcm_dev = std::make_shared<PCM>("bluealsa", 1, sampling_rate);
}

void AudioProcessor::record() {
  std::cout << "Run Record Loop\n";
  size_t len = frame_size;

  std::vector<sample_t> buffer(len);

  while (true) {
    pcm_dev->readFrames(buffer.data(), frame_size);
    samples.push(buffer);
  }

  // free(buffer);
}

std::thread* AudioProcessor::record_thread() {
  record_loop = new std::thread(&AudioProcessor::record, this);
  pthread_t id = (pthread_t)(record_loop->native_handle());

  sched_param sched_params = { 1 };
  pthread_setschedparam(id, SCHED_FIFO, &sched_params);
  return record_loop;
}

void AudioProcessor::run() {
  std::cout << "Run Audio Processor\n";

  const auto& speaker = Speaker::instance();

  Modulator mod(sampling_rate, frame_size, speaker->sampling_rate, 40000);

  while (true) {
    const auto& buffer = samples.pop();

    for (const auto t : mod.time) {
      const auto sig = mapValue(buffer.at(floor(t * sampling_rate)));
      const auto sample = mod.AM(sig, t, 0.5f, 0.5f);
      speaker->samples.push(speaker->mapSample(sample));
    }
  }
}

std::thread* AudioProcessor::run_thread() {
  loop = new std::thread(&AudioProcessor::run, this);
  pthread_t id = (pthread_t)(loop->native_handle());

  sched_param sched_params = { 1 };
  pthread_setschedparam(id, SCHED_FIFO, &sched_params);
  return loop;
}