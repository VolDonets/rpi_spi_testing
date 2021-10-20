cmake_minimum_required(VERSION 3.12)
project(rpi_spi_testing)

set(CMAKE_CXX_STANDARD 20)

add_executable(rpi_spi_testing
        log/LOG.h
        spi_library/spi.h spi_library/spi.cpp
        holder_controller/holder_controller.h holder_controller/holder_controller.cpp
        main.cpp)
