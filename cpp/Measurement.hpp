/**
 * @file measurement.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <array>
#include <cstdint>
#include <string>
#include <stdexcept>

#include "constants.h"

class Measurement
{

  public:
    explicit Measurement(const std::array<uint8_t, gDataPacketLength> rawMeasurementBytes);

    bool checkSign(void) const {

    }

    std::string getMeasurement(Units measurementUnit) const {

    }

  private:

    /// @brief Decodes the list of raw bytes into a measurement
    ///     Side-effect: stores the measurement and native unit in the class
    ///     Read the whole documentation to understand how the data is stored.
    /// @return 
    double decodeRawMeasurement() {

        uint8_t sign = mRawMeasurement.at(0);

        if (sign == 0x2B) { // ASCII '+'
            mSign = true;
        }
        else if (sign == 0x2D) { // ASCII '-'
            mSign = false;
        }
        else {
            // Unsupported
            throw std::invalid_argument("Unable to determine sign (+/-) of measurement, data does not match expected format");
        }
    }


    // Members //

    bool mSign;

    double mMeasurement;

    std::array<uint8_t, gDataPacketLength> mRawMeasurement;

    Units mNativeUnit;
};