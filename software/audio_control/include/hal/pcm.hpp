#ifndef SOUND_LASER_HAL_PCM_HPP
#define SOUND_LASER_HAL_PCM_HPP

#include <alsa/asoundlib.h>
#include <cmath>
#include <iostream>
#include <string>

typedef int16_t sample_t;

class PCM {

  public:
  size_t format_width;
  size_t format_max;
  size_t format_zero;
  snd_pcm_t* capture_handle;
  snd_pcm_hw_params_t* hw_params;

  PCM(std::string device_name, char channel_cnt, uint32_t fs);
  ~PCM() { snd_pcm_close(capture_handle); };

  void readFrames(sample_t* buffer, size_t frames);
};

#endif