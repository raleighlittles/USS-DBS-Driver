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
    void decodeRawMeasurement() {

        // To start, conduct basic sanity checks -- verifying the message starts correctly (with a plus or minus sign),
        // and ends correctly (with a carriage return and a newline)

        uint8_t sign = mRawMeasurement.at(0);

        if (sign == static_cast<uint8_t>(CommonASCIIValues::PLUS_SIGN)) {
            mSign = true;
        }

        else if (sign == static_cast<uint8_t>(CommonASCIIValues::MINUS_SIGN)) {
            mSign = false;
        }

        else {
            // Unsupported
            throw std::invalid_argument("Unable to determine sign (+/-) of measurement, data does not match expected format");
        }

        if ((mRawMeasurement.at(mRawMeasurement.size() - 2) != static_cast<uint8_t>(CommonASCIIValues::CARRIAGE_RET)) || 
            (mRawMeasurement.back() != static_cast<uint8_t>(CommonASCIIValues::NEWLINE))) {

            throw std::invalid_argument("Message was supposed to end with '\r\n' but didn't, check that message is correctly formatted!");
        }

        // Now that the measurement must be valid, begin parsing.

        std::string measurement = "";

        // The units are included in the measurement itself, so `measurement` will be "8 lbs" while measurementUnits will be "lbs"
        std::string measurementUnit = "";

        // Read the entire character portion -- remember the last two bytes are the CRLF
        for (std::size_t i = 1; i < mRawMeasurement.size() - 2; i++) {

            auto currChar = mRawMeasurement.at(i);

            if (currChar != static_cast<uint8_t>(CommonASCIIValues::SPACE)) { // Skip spaces
                measurement.append(reinterpret_cast<const char*>(currChar));
            }

            // Check if current character is in the range of:
            // uppercase letters (0x41 65d to 0x5A 90d in ASCII table)
            // lowercase letters (0x61 97d to 0x7A 122d)
            // if it is, it's part of the 'unit' description

            if (((currChar >= 0x41) && (currChar <= 0x5A)) || ((currChar >= 0x61) && (currChar <= 0x7A))) {
                measurementUnit.append(reinterpret_cast<const char*>(currChar));
            }

        }

        // By now, full measurement should be parsed, just need to determine what the units are
        mMeasurementStr = measurement;

    }

    /// @brief Converts a unit string into an enum
    /// @param measurementUnit 
    /// @return 
    Units extractUnitName(const std::string measurementUnit) {

    }


    // Members //

    bool mSign;

    double mMeasurement;
    std::string mMeasurementStr;

    std::array<uint8_t, gDataPacketLength> mRawMeasurement;

    Units mNativeUnit;
};