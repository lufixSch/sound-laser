#ifndef SOUND_LASER_HAL_SPI_HPP
#define SOUND_LASER_HAL_SPI_HPP

class SPI {

  public:
  SPI();
  ~SPI();

  transfer(char* tx_data, char* rx_data, size_t size);
  write(char* data, size_t size);
}

#endif