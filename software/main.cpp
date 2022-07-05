#include <chrono>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <vector>

//#include "speaker.hpp"
#define SIZE 1024

char data[3] = { 0x12, 0xAB, 0x34 };
char buf[3];

int main(int, char**) {
  std::cout << "Hello, world!\n";

  int arr[SIZE];
  arr[SIZE - 1] = 21;

  std::vector<int>* test;
  auto start = std::chrono::high_resolution_clock::now();

  for (size_t i = 0; i < 1000; i++) {
    /* code */
    test = new std::vector<int>(std::begin(arr), std::end(arr));
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cout << "Time taken by function: " << (float)duration.count() / 1000.0 << " microseconds" << std::endl;

  std::cout << arr[SIZE - 1] << " - " << test->at(SIZE - 1) << std::endl;

  arr[SIZE - 1] = 2;

  std::cout << arr[SIZE - 1] << " - " << test->at(SIZE - 1) << std::endl;

  // if (!bcm2835_init()) {
  //   std::cerr << "bcm2835_init failed. Are you running as root??\n";
  //   return 1;
  // }

  // Speaker* speaker = Speaker::instance();
  // speaker->run_thread();

  // bcm2835_close();

  return 0;
}
