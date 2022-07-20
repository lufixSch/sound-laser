
#include "hal/spi.hpp"

#include <iostream>

SPI::SPI() {
  if (!bcm2835_spi_begin()) {
    throw std::runtime_error("bcm2835_spi_begin failed. Are you running as root??");
  }

  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64); // BCM2835_SPI_CLOCK_DIVIDER_16);
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
}

SPI::~SPI() { bcm2835_spi_end(); }

void SPI::write(char* data, uint32_t size) { this->transfer(data, this->rx_buffer, size); }
