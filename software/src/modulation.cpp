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

std::vector<float> Modulator::AM(std::vector<sample_t> signal, float U0, float m) {
  std::vector<float> out;

  for (auto t : time) {
    auto c = sin(carrier * t);
    auto s = (float)signal.at(round(t * input_fs));

    out.emplace_back(U0 * (1 + m * s) * c);
  }

  return out;
}