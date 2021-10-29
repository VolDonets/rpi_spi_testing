#include <iostream>
#include <unistd.h>
#include <vector>

#include "holder_controller/holder_controller.h"

int main(int argc, char *argv[]) {
    std::shared_ptr<HolderController> _holderController = std::make_shared<HolderController>();

    int countMessageSends = 1000;
    __useconds_t messageSendingTimout = 10000;
    uint8_t xSpeed = 128;
    uint8_t ySpeed = 64;
    uint8_t direction = 0x00;

    bool isContainsHelpRequest = false;

    if (argc > 1) {
        std::string helpStr1 = "--help";
        std::string helpStr2 = "-h";

        std::string msgCountStr = "-m";
        std::string timeoutStr = "-t";
        std::string xSpeedStr = "-x";
        std::string ySpeedStr = "-y";
        std::string directionStr = "-d";

        std::vector<std::string> vecArgv;
        for (int i = 1; i < argc; i++) {
            vecArgv.push_back(argv[i]);
        }

        for (std::string str : vecArgv) {
            if (str == helpStr1 || str == helpStr2) {
                isContainsHelpRequest = true;
                break;
            }
        }

        if (!isContainsHelpRequest) {
            for (int i = 0; i < vecArgv.size(); i++) {
                try {
                    if (vecArgv[i] == msgCountStr) {
                        i++;
                        countMessageSends = std::stoi(vecArgv[i]);
                    } else if (vecArgv[i] == timeoutStr) {
                        i++;
                        messageSendingTimout = std::stoi(vecArgv[i]);
                    } else if (vecArgv[i] == xSpeedStr) {
                        i++;
                        xSpeed = std::stoi(vecArgv[i]);
                    } else if (vecArgv[i] == ySpeedStr) {
                        i++;
                        ySpeed = std::stoi(vecArgv[i]);
                    } else if (vecArgv[i] == directionStr) {
                        i++;
                        direction = std::stoi(vecArgv[i]);
                    }
                } catch (...) {

                }
            }
        }
    } else {
        std::cout << "### Used default configurations: \n";
    }

    if (isContainsHelpRequest) {
        std::cout << "Help message: \n";
        std::cout << "'-h', '--help'                      -- for help\n";
        std::cout << "'-m' + count messages               -- for getting current count of messages\n";
        std::cout << "'-t' + timeout in microseconds      -- for setting current timeout between messages\n";
        std::cout << "'-x' + speed value (0 - 255)        -- for setting speed for X axis \n";
        std::cout << "'-y' + speed value (0 - 255)        -- for setting speed for Y axis \n";
        std::cout << "'-d' + direction value (0, 1, 2, 3) -- for setting direction value \n";
        std::cout << "\n";
        return 0;
    }

    std::cout << "Total count of messages to SPI: " << countMessageSends << "\n";
    std::cout << "Timeout between messages: " << messageSendingTimout << "\n";
    std::cout << "X speed value: " << (int) xSpeed << "\n";
    std::cout << "Y speed value: " << (int) ySpeed << "\n";
    std::cout << "Direction value: " << (int) direction << "\n";
    std::cout << "\n";

    int i = 1000;
    while (i--) {
        _holderController->setMoveSpeed(xSpeed, ySpeed, direction);
        usleep(10000);
    }

    return 0;
}
