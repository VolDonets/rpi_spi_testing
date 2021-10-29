//
// Created by biba_bo on 2021-10-20.
//

#include "holder_controller.h"

HolderController::HolderController() {
    _spiDriver = std::make_shared<SPI>();
    _spiDriver->Init("/dev/spidev0.0", SPI::SpiMode::MODE1, 8, 1100000, 0);
}

HolderController::HolderController(std::shared_ptr<SPI> spiDriver) : _spiDriver(spiDriver) {

}

void HolderController::recalculateMessageSum() {
    uint16_t messageSum = 0;
    for (int i = 1; i < _BUFFER_OUT_SIZE - 1; i++)
        messageSum += (uint16_t) _messageOutBuffer[i];

    messageSum %= 256;
    _messageOutBuffer[_BUFFER_OUT_SIZE - 1] = (uint8_t) messageSum;
}

void HolderController::setMoveSpeed(uint8_t xSpeed, uint8_t ySpeed, uint8_t direction) {
    _messageOutBuffer[1] = xSpeed; // set speed for X axis
    _messageOutBuffer[2] = ySpeed; // set speed for Y axis
    _messageOutBuffer[3] = direction; // set movement direction
    for (int i = 3; i < _BUFFER_OUT_SIZE - 1; i++)
        _messageOutBuffer[i] = 0x00;

    recalculateMessageSum();
    _spiDriver->transferArray(_messageOutBuffer, _BUFFER_OUT_SIZE);
}

void HolderController::stopMoving() {
    setMoveSpeed(0x00, 0x00, 0x00);
}