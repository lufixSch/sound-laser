#include "hal/pcm.hpp"

PCM::PCM(std::string device_name, char channel_cnt, uint32_t fs) {
  int i;
  int err;
  snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;

  if ((err = snd_pcm_open(&capture_handle, device_name.c_str(), SND_PCM_STREAM_CAPTURE, 0)) < 0) {
    std::cerr << "cannot open audio device (" << snd_strerror(err) << ")\n";
    exit(1);
  }

  if ((err = snd_pcm_hw_params_malloc(&hw_params)) < 0) {
    std::cerr << "cannot allocate hardware parameter structure (" << snd_strerror(err) << ")\n";
    exit(1);
  }

  if ((err = snd_pcm_hw_params_any(capture_handle, hw_params)) < 0) {
    std::cerr << "cannot initialize hardware parameter structure (" << snd_strerror(err) << ")\n";
    exit(1);
  }

  if ((err = snd_pcm_hw_params_set_access(capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
    std::cerr << "cannot set access type (" << snd_strerror(err) << ")\n";
    exit(1);
  }

  if ((err = snd_pcm_hw_params_set_format(capture_handle, hw_params, format)) < 0) {
    std::cerr << "cannot set sample format (" << snd_strerror(err) << ")\n";
    exit(1);
  }

  if ((err = snd_pcm_hw_params_set_rate_near(capture_handle, hw_params, &fs, 0)) < 0) {
    std::cerr << "cannot set sample rate (" << snd_strerror(err) << ")\n";
    exit(1);
  }

  if ((err = snd_pcm_hw_params_set_channels(capture_handle, hw_params, 1)) < 0) {
    std::cerr << "cannot set channel count (" << snd_strerror(err) << ")\n";
    exit(1);
  }

  if ((err = snd_pcm_hw_params(capture_handle, hw_params)) < 0) {
    std::cerr << "cannot set parameters (" << snd_strerror(err) << ")\n";
    exit(1);
  }

  snd_pcm_hw_params_free(hw_params);

  if ((err = snd_pcm_prepare(capture_handle)) < 0) {
    std::cerr << "cannot prepare audio interface for use (" << snd_strerror(err) << ")\n";
    exit(1);
  }
}

void PCM::readFrames(char* buffer, size_t frames) {
  int err;

  if ((err = snd_pcm_readi(capture_handle, buffer, frames)) != frames) {
    std::cerr << "read from audio interface failed (" << snd_strerror(err) << ")\n";
    exit(1);
  }
}