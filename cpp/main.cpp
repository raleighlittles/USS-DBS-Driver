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
#include <fstream>
#include <getopt.h>
#include <chrono>
#include <ctime>

#include "constants.h"
#include "Measurement.hpp"

int main(int argc, char* argv[]) {

    /// -------------------------- ///
    /// Setup parsing of CLI args 
    

    struct option long_opt[] = 
    {
        {"help", no_argument, nullptr, 'h'},
        {"outcsv", required_argument, nullptr, 'o'},
        {"unit", required_argument, nullptr, 'u'},
        {"keyboard", no_argument, nullptr, 'k' },
        {nullptr, 0, nullptr, 0} // Last element must be empty
    };


    // For logging to CSV file
    bool logToFile = false;
    std::string outputFileName;
    std::ofstream csvFile;

    // For making measurement show up as keyboard input
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
                std::cout << "-h \t \t \t Shows this help text" << std::endl;
                std::cout << "-u [unit name] \t \t Measurements will be converted to the specified unit. (See manual for supported unit descriptions)" << std::endl;
                std::cout << "-o [filename] \t Logs measurements to the specified CSV file" << std::endl;
                std::cout << "-k \t \t \t Prints measurements from the keyboard directly" << std::endl;
                return 0;

            case 'u':
                // `optarg` is a global variable used in the getopt library
                desiredMeasurementUnit = std::string(optarg);
                std::cout << "[DEBUG] User specified unit: " << desiredMeasurementUnit << std::endl;
                break;

            case 'k':
                std::cout << "[DEBUG] User enabled keyboard functionality" << std::endl;
                useKeyboard = true;
                break;

            case 'o':
                outputFileName = std::string(optarg);
                std::cout << "[DEBUG] User requested output to " << outputFileName << std::endl;
                logToFile = true;
                break;

            default:
                std::cerr << "ERROR: Unsupported command-line argument received : " << ch << std:: endl;
                return -1;
        }
    }
    
    if (logToFile) {
     // Open CSV file, initialize columns
      
      csvFile.open(outputFileName, std::ios::out);
        
      if (!csvFile.is_open()) {
       std::cerr << "Error opening CSV file" << std::endl;
       return 2;
      }
        
       csvFile << "'Measurement Time' , 'Measurement Value'" << std::endl;
    }

    /// -------------------------- ///
    /// Setup serial port

    const std::string serialPortFile = "/dev/ttyUSB0";
    const int serialPortFileDescriptor = open(serialPortFile.c_str(), O_RDONLY | O_NOCTTY | O_NONBLOCK);

    if (serialPortFileDescriptor == -1) {

        std::cerr << "Failed to open serial port file: " << serialPortFile << std::endl;
    }

    struct termios terminal_options;
    memset(&terminal_options, 0, sizeof(struct termios));

    terminal_options.c_cflag = B9600 | CS8 | CREAD;

    if ((tcsetattr(serialPortFileDescriptor, TCSANOW, &terminal_options)) != 0)
    {

        std::cerr << "Failed to set termios settings";
        close(serialPortFileDescriptor);
        return 1;
    }

    if ((tcflush(serialPortFileDescriptor, TCIOFLUSH)) != 0) {

        std::cerr << "Failed to flush termios settings. Check that scale is connected";
        close(serialPortFileDescriptor);
        return 1;
    }

    // Wait for the serial port to open (Why is this needed?)
    usleep(10000);


    // Start reading from serial port. Make sure you've read the documentation to understand this section
    std::array<uint8_t, gDataPacketLength> readBuffer;

    while (true) {
        
        ssize_t bytesRead = read(serialPortFileDescriptor, readBuffer.begin(), gDataPacketLength);

        //std::cout << "[DEBUG] Read " << bytesRead << " bytes " << std::endl;

        if (bytesRead < 0) {

            std::cerr << "Error reading from serial port. Errno= " << errno << std::endl;
            return 2;
        }

        else if (bytesRead == 0) {
            usleep(100000);
        }

        else if (bytesRead > 1) {

            auto measurementObj = Measurement(readBuffer);
            
            const std::string printableMeasurement = measurementObj.getMeasurement(desiredMeasurementUnit);

            std::cout << "[DEBUG] Measurement received: " << printableMeasurement << std::endl;

            const std::string ineligibleMeasurement = "0.0";

            // Make sure the measurement isn't 0 (yes, this actually happens!)
            if (!printableMeasurement.compare(0, ineligibleMeasurement.size(), ineligibleMeasurement)) {
                std::cerr << "[WARNING] Measurement of zero was recorded, discarding" << std::endl;
                continue;
            }

            if (logToFile) {
                
                // Get current time
                    auto start = std::chrono::system_clock::now();
                    auto legacyStart = std::chrono::system_clock::to_time_t(start);
                    const std::string currentTimestamp = std::ctime(&legacyStart);

                std::cout << "[DEBUG] Current Time = " << currentTimestamp << std::endl;

                csvFile << printableMeasurement << " , " << currentTimestamp << std::endl;
            }

            if (useKeyboard) {
                continue;
            }
        }

        usleep(10000);
    }

    return 0;
}
