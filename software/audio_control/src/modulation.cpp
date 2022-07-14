#include "modulation.hpp"
#include "audio.hpp"

#include <cmath>

Modulator::Modulator(uint32_t input_fs, uint32_t input_samples, uint32_t output_fs, uint32_t carrier_f) {
  samples = (input_samples * output_fs) / input_fs;

  for (size_t i = 0; i < samples; i++) {
    time.push_back((float)i / output_fs);
  }

  this->input_fs = input_fs;
  this->input_samples = input_samples;
  this->carrier = M_PI * 2 * carrier_f;
}

float Modulator::AM(float signal, float t, float U0, float m) {
  float c = sin(carrier * t);

  return U0 * (1 + m * signal) * c;
}

float Modulator::FM(float signal, float t, float U0, float m) {
  float w0 = carrier;
  return U0 * sin(w0 * (1 + m * signal) * t);
}