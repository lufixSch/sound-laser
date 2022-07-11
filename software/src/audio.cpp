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
  size_t len = pcm_dev->format_width * frame_size;
  //  char* buffer = (char*)malloc(len);

  //  std::vector<char> test();

  while (true) {
    std::vector<char> buffer(len);

    pcm_dev->readFrames(buffer.data(), frame_size);
    // samples.push(buffer);

    for (const auto el : buffer) {
      std::cout << int(el) << "\n";
    }
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

  auto speaker = Speaker::instance();
  Modulator mod(sampling_rate, frame_size, speaker->sampling_rate, 40000);

  while (true) {
    auto buffer = samples.pop();
    auto data = mapValues(buffer);

    for (auto sample : buffer) {
      std::cout << int(sample) << "\n";
    }

    auto sig = mod.AM(data, 0.5, 0.2);

    for (auto sample : sig) {
      speaker->samples.push(speaker->mapSamples(sample, 65536));
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

std::vector<sample_t> AudioProcessor::mapValues(std::vector<char> in) {
  std::vector<sample_t> out;

  for (size_t i = 0; i < in.size(); i += 2) {
    out.emplace_back(((sample_t)in.at(i) << 8) + in.at(i + 1));
  }

  return out;
}