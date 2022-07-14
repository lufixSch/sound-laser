#ifndef SOUND_LASER_TABLE_HPP
#define SOUND_LASER_TABLE_HPP

#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Table {
  static Table* instance_;
  std::vector<int32_t> value;
  std::vector<uint64_t> diff;
  std::vector<std::chrono::_V2::system_clock::duration> time;
  size_t sig_pos = 0;

  std::vector<size_t> speaker_queue;
  std::vector<size_t> audio_queue;

  protected:
  Table() {};

  public:
  Table(Table& other) = delete;
  void operator=(const Table&) = delete;

  static Table* instance() {
    if (instance_ == nullptr) {
      instance_ = new Table();
    }

    return instance_;
  };

  void configureSignalLen(size_t len) {
    time = std::vector<std::chrono::_V2::system_clock::duration>(len);
    value = std::vector<int32_t>(len);
    diff = std::vector<uint64_t>(len);
  }

  void addSignal(int32_t value, std::chrono::_V2::system_clock::duration time) {
    this->value.at(sig_pos) = value;
    this->time.at(sig_pos) = time;
  }
  void addDiff(uint64_t diff) { this->diff.at(sig_pos) = diff; };
  void nextSignal() { sig_pos++; };

  void printSignal() {
    std::cout << "val,diff,time"
              << "\n";

    for (uint32_t i = 0; i < value.size(); i++) {
      std::cout << value.at(i) << "," << diff.at(i) << "," << time.at(i).count() << "\n";
    }
  };

  void appendQueueSizes(size_t speaker, size_t audio) {
    speaker_queue.emplace_back(speaker);
    audio_queue.emplace_back(audio);
  };

  void printQueueSizes() {
    std::cout << "speaker,audio\n";

    for (size_t i = 0; i < speaker_queue.size(); i++) {
      std::cout << speaker_queue.at(i) << "," << audio_queue.at(i) << "\n";
    }
  }
};

#endif