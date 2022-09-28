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

    std::string getMeasurement(Units requestedMeasurementUnit) const {
      
      // The simple case: The unit is requested in the same format its already stored in, so no conversion is needed
      if (requestedMeasurementUnit == mNativeUnit) {

        return mMeasurementStr;
      }

      // TODO: Handle conversion of unit

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

            if (((currChar >= static_cast<uint8_t>(CommonASCIIValues::UPPER_CASE_A)) && (currChar <= static_cast<uint8_t>(CommonASCIIValues::UPPER_CASE_Z))) || ((currChar >= static_cast<uint8_t>(CommonASCIIValues::LOWER_CASE_A)) && (currChar <= static_cast<uint8_t>(CommonASCIIValues::LOWER_CASE_Z)))) {

                measurementUnit.append(reinterpret_cast<const char*>(currChar));
            }

        }

        // By now, full measurement should be parsed

        mMeasurementStr = measurement;
        mNativeUnit = extractUnitName(measurementUnit);
        mMeasurement = std::stod(measurement);

    }

    /// @brief Converts a unit string into an enum
    /// @param measurementUnit 
    /// @return 
    Units extractUnitName(const std::string measurementUnit) {

        if (measurementUnit == "g") {
            return Units::GRAMS;
        }

        else if (measurementUnit == "kg") {
            return Units::KILOGRAMS;
        }

        else if (measurementUnit == "ct") {
            return Units::CARATS;
        }
      
        else if (measurementUnit == "T") {
            return Units::TOLA; 
        }
      
        else if (measurementUnit == "TAR") {
            return Units::TAR;
        }
      
        else if (measurementUnit == "dr") {
            return Units::DRAM;
        }
      
        else if (measurementUnit == "PKT") {
          return Units::PKT;
        }
      
        else if (measurementUnit == "GN") {
          return Units::GRAIN;
        }
      
        else if (measurementUnit == "TMR") {
          return Units::TMR;
        }
      
        else if (measurementUnit == "gsm") {
          return Units::GSM;
        }
      
        else if (measurementUnit == "tlJ") {
          return Units::TAEL_JAPAN;
        }
      
        else if (measurementUnit == "mo") {
          return Units::MOMME;
        }
      
        else if (measurementUnit == "dwt") {
          return Units::PENNYWEIGHT;
        }
      
        else if (measurementUnit == "oz") {
          return Units::OUNCES;
        }
      
        else if (measurementUnit == "lb") {
          return Units::POUNDS;
        }
      
        else if (measurementUnit == "tlT") {
          return Units::TAEL_TAIWAN;
        }
      
        else if (measurementUnit == "ozt") {
          return Units::TROY_OUNCE;
        }
      
        else if (measurementUnit == "tlH") {
          return Units::TAEL_HONGKONG;
        }
      
        else if (measurementUnit == "%") {
          return Units::PERCENT;
        }
      
        else {
          throw std::invalid_argument("Unsupported unit type!");
        }
    }


    // Members //

    bool mSign;

    double mMeasurement;
    std::string mMeasurementStr;

    std::array<uint8_t, gDataPacketLength> mRawMeasurement;

    Units mNativeUnit;
};
