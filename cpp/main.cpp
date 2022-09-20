/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <string>
#include <array>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h> // memset()
#include <iostream>

#include "constants.h"

int main(int /*argc */, char** /*argv[] */) {

    // -----
    // Setup and initialize serial port
    // -----

    const std::string serialPortFile = "/dev/ttyUSB0";
    const int serialPortFileDescriptor = open(serialPortFile.c_str(), O_RDONLY | O_NOCTTY | O_NONBLOCK);

    if (serialPortFileDescriptor == -1) {

        std::cerr << "Failed to open serial port file: " << serialPortFile << std::endl;
    }

    struct termios terminal_options;
    memset(&terminal_options, 0, sizeof(struct termios));

    if ((tcflush(serialPortFileDescriptor, TCIOFLUSH)) != 0) {

        std::cerr << "Failed to flush termios settings";
        close(serialPortFileDescriptor);
        return 1;
    }

    // Wait for the serial port to open -- this might not be needed
    usleep(100000);

    // -----
    // Start reading from serial port. Make sure you've read the documentation
    // -----

    std::array<std::byte, gDataPacketLength> readBuffer;

    while (true) {
        
        ssize_t bytesRead = read(serialPortFileDescriptor, readBuffer.begin(), gDataPacketLength);

        if (bytesRead < 0) {

            std::cerr << "Error reading from serial port" << std::endl;
            return 2;
        }

        if (bytesRead > 0) {

        }

    }



}

