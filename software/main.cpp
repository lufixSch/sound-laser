#include <alsa/asoundlib.h>
#include <bcm2835.h>
#include <chrono>
#include <iostream>
#include <thread>

char data[3] = { 0x12, 0xAB, 0x34 };
char buf[3];

int main(int, char**) {
  std::cout << "Hello, world!\n";

  if (!bcm2835_init()) {
    std::cout << "bcm2835_init failed. Are you running as root??\n";
    return 1;
  }

  if (!bcm2835_spi_begin()) {
    std::cout << "bcm2835_spi_begin failed. Are you running as root??\n";
    return 1;
  }

  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_16); // BCM2835_SPI_CLOCK_DIVIDER_16);
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);

  auto start = std::chrono::high_resolution_clock::now();
  long long diff;

  while (true) {
    start = std::chrono::high_resolution_clock::now();
    bcm2835_spi_transfernb(data, buf, 3);
    auto diff_us
        = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start)
              .count()
        / 1000;
    bcm2835_delayMicroseconds(10 - (uint64_t)diff_us);
  }

  bcm2835_spi_end();
  bcm2835_close();

  return 0;
}
