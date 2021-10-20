//
// Created by biba_bo on 2021-10-20.
//

#ifndef RPI_SPI_TESTING_HOLDER_CONTROLLER_H
#define RPI_SPI_TESTING_HOLDER_CONTROLLER_H

#include <memory>

#include "../spi_library/spi.h"

class HolderController {
    /**
     * this buffer is a message format for messaging to holder controller via SPI interface
     * 0 byte is the message start flag
     * 1 byte is speed value by X axis
     * 2 byte is speed value by Y axis
     * 3 byte -//-
     * 4 byte -//-
     * 5 byte -//-
     * 6 byte -//-
     * 7 byte is control sum for message checking
     */
    const uint32_t _BUFFER_OUT_SIZE = 8;
    uint8_t _messageOutBuffer[8] = {0xFF, 0x00, 0x00, 0x00,
                                    0x00, 0x00, 0x00, 0x00};
    std::shared_ptr<SPI> _spiDriver;


    void recalculateMessageSum();

public:
    HolderController();
    HolderController(std::shared_ptr<SPI> spiDriver);

    void setMoveSpeed(uint8_t xSpeed, uint8_t ySpeed);
    void stopMoving();
};


#endif //RPI_SPI_TESTING_HOLDER_CONTROLLER_H
