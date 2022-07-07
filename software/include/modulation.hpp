#ifndef SOUND_LASER_MODULATIO_HPP
#define SOUND_LASER_MODULATIO_HPP

#include "audio.hpp"
#include <inttypes.h>
#include <list>
#include <vector>

class Modulator {
  uint32_t samples;
  uint32_t input_samples;
  uint32_t input_fs;
  float carrier;

  std::list<float> time;

  public:
  Modulator(uint32_t input_fs, uint32_t input_samples, uint32_t output_fs, uint32_t carrier_f);

  std::vector<float> AM(std::vector<sample_t> signal, float U0, float m);
  std::list<uint16_t> FM();
  std::list<uint16_t> PM();
};

#endif