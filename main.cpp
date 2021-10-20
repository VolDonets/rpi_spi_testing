#include <iostream>
#include <unistd.h>

#include "holder_controller/holder_controller.h"

int main() {
    std::shared_ptr<HolderController> _holderController = std::make_shared<HolderController>();

    int i = 1000;
    while (i--) {
        _holderController->setMoveSpeed((uint8_t) i, (uint8_t) i);
        usleep(10000);
    }

    return 0;
}
