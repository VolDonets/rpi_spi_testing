#include <iostream>

#include "spi_library/spi.h"

int main() {
    uint8_t buff[8] = {0xFF, 0x00, 0x01, 0xFF, 0x00, 0x01, 0xFF, 0x33};

    SPI spi;
    spi.Init("/dev/spidev0.0", SPI::SpiMode::MODE1, 8, 1100000, 0);

    int i = 1000;
    while (i--) {
        spi.transferArray(buff, 8);
    }

    return 0;
}
