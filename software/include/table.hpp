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

  size_t pos = 0;

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

  void configureLen(size_t len) {
    time = std::vector<std::chrono::_V2::system_clock::duration>(len);
    value = std::vector<int32_t>(len);
    diff = std::vector<uint64_t>(len);
  }

  void append(int32_t value, std::chrono::_V2::system_clock::duration time) {
    this->value.emplace_back(value);
    this->time.emplace_back(time);
  };

  void add(int32_t value, std::chrono::_V2::system_clock::duration time) {
    this->value.at(pos) = value;
    this->time.at(pos) = time;
    pos++;
  }

  void addDiff(uint64_t diff) { this->diff.at(pos - 1) = diff; };

  void print() {
    std::cout << "val,diff,time"
              << "\n";

    for (uint32_t i = 0; i < value.size(); i++) {
      std::cout << value.at(i) << "," << diff.at(i) << "," << time.at(i).count() << "\n";
    }
  };

  void saveToFile(std::string file_name);
};

#endif