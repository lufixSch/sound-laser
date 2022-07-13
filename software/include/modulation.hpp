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

  public:
  float carrier;
  std::list<float> time;

  Modulator(uint32_t input_fs, uint32_t input_samples, uint32_t output_fs, uint32_t carrier_f);

  float AM(float signal, float t, float U0, float m);
  float FM(float signal, float t, float U0, float m);
  float PM();
};

#endif