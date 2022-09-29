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
#include <string.h>
#include <iostream>
#include <getopt.h>

#include "constants.h"
#include "Measurement.hpp"

int main(int argc, char* argv[]) {

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


    struct option long_opt[] = 
    {
        {"help", no_argument, nullptr, 'h'},
        {"outcsv", required_argument, nullptr, 'o'},
        {"unit", required_argument, nullptr, 'u'},
        {"keyboard", no_argument, nullptr, 'k' },
        {nullptr, 0, nullptr, 0} // Last element must be empty
    };


    bool logToFile = false;
    std::string outputFileName;

    bool useKeyboard = false;

    std::string desiredMeasurementUnit;

    const char* short_opt = "ho:u:k";

    int ch; // character

    while ((ch = getopt_long(argc, argv, short_opt, long_opt, nullptr)) != -1) {

        switch (ch) {

            case -1:
            case 0:
                break;

            case 'h':
                std::cout << "Usage: " << argv[0] << std::endl;
                std::cout << "-h \t \t Shows this help text" << std::endl;
                std::cout << "-u [unit name] \t \t Measurements will be converted to the specified unit. (See manual for supported unit descriptions)" << std::endl;
                std::cout << "-o [filename].csv \t \t Logs measurements to the specified CSV file" << std::endl;
                std::cout << "-k \t \t Prints measurements from the keyboard directly" << std::endl;
                return 0;

            case 'u':
                // `optarg` is a global variable used in the getopt library
                std::cout << "[DEBUG] User specified unit: " << optarg << std::endl;
                desiredMeasurementUnit = std::string(optarg);
                break;

            case 'k':
                std::cout << "[DEBUG] User enabled keyboard functionality" << std::endl;
                useKeyboard = true;
                break;

            case 'o':
                std::cout << "[DEBUG] User requested output to " << optarg << ".csv " << std::endl;
                outputFileName = std::string(optarg);
                break;

            default:
                std::cerr << "ERROR: Unsupported command-line argument received : " << ch << std:: endl;
                return -1;
        }
    }


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

            auto measurementObj = Measurement(readBuffer);
            
            const std::string printableMeasurement = measurementObj.getMeasurement(desiredMeasurementUnit);

            if (logToFile) {

            }

            if (useKeyboard) {

            }
        }
    }


    return 0;
}