#ifndef SOUND_LASER_HAL_SPI_HPP
#define SOUND_LASER_HAL_SPI_HPP

#include <bcm2835.h>
#include <inttypes.h>

class SPI {
  char rx_buffer[4096];

  public:
  SPI();
  ~SPI();

  void (*transfer)(char* tx_data, char* rx_data, uint32_t size) = &bcm2835_spi_transfernb;
  void write(char* data, uint32_t size);
};

#endif