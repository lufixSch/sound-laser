#include "audio.hpp"

AudioProcessor* AudioProcessor::instance_ { nullptr };

AudioProcessor* AudioProcessor::instance() {
  if (instance_ == nullptr) {
    instance_ = new AudioProcessor();
  }

  return instance_;
}

AudioProcessor::AudioProcessor() { pcm_dev = new PCM("bluealsa", 1, 44100); }

void AudioProcessor::record(size_t frame_size) {
  size_t len = pcm_dev->format_width * frame_size * 8;
  char* buffer = (char*)malloc(len);

  while (true) {
    pcm_dev->readFrames(buffer, frame_size);
    // push in queue
  }

  free(buffer);
}

void AudioProcessor::run(size_t frame_size) {
  size_t len = pcm_dev->format_width * frame_size * 8;
  char* buffer = (char*)malloc(len);
  sample_t* data_buff = (sample_t*)malloc(len / 2);

  while (true) {
    // pull from queue

    mapValues(buffer, data_buff, len);

    // modulate Signal
    // push to queue
  }

  free(buffer);
  free(data_buff)
}

void AudioProcessor::mapValues(char* in, sample_t* out, size_t in_size) {
  for (size_t i = 0; i < in_size; i += 2) {
    out[i / 2] = ((sample_t)in[i] << 8) + in[i + 1];
  }
}