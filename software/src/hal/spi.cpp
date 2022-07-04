
#include "hal/spi.hpp"

#include <bcm2835.h>
#include <iostream>

SPI::SPI() {
  if (!bcm2835_spi_begin()) {
    std::cout << "bcm2835_spi_begin failed. Are you running as root??\n";
    return 1;
  }

  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_16); // BCM2835_SPI_CLOCK_DIVIDER_16);
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
}

SPI::~SPI() { bcm2835_spi_end(); }