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
#include "converter.h"

#pragma once

class Measurement
{

  public:
    explicit Measurement(const std::array<uint8_t, gDataPacketLength> rawMeasurementBytes)
            : mRawMeasurement(rawMeasurementBytes) { }

    bool checkSign(void) const {
      // TODO: Not used?
      return true;
    }

    std::string getMeasurement(const std::string desiredUnitName) {

      decodeRawMeasurement();

      const Units requestedMeasurementUnit = extractUnitName(desiredUnitName);
      
      // The simple case: The unit is requested in the same format its already stored in, so no conversion is needed
      if (requestedMeasurementUnit == mNativeUnit) {
        return mMeasurementStr;
      }

      else {
        
        return std::to_string(Converter::convertMeasurement(mMeasurement, mNativeUnit, requestedMeasurementUnit));
      }
    }

  private:

    /// @brief Main function of this class: decodes the series of raw bytes into a measurement
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

        // if ((mRawMeasurement.at(mRawMeasurement.size() - 2) != static_cast<uint8_t>(CommonASCIIValues::CARRIAGE_RET)) || 
        //     (mRawMeasurement.back() != static_cast<uint8_t>(CommonASCIIValues::NEWLINE))) {
        //   if ( mRawMeasurement.at(mRawMeasurement.size() - 2) != static_cast<uint8_t>(CommonASCIIValues::NEWLINE) ) {

        //     throw std::invalid_argument("Message was supposed to end with newline but didn't, check that message is correctly formatted!");
        // }

        // Now that the measurement must be valid, begin parsing.

        std::string measurement = "";

        // The units are included in the measurement itself, so `measurement` will be "8 lbs" while measurementUnits will be "lbs"
        std::string measurementUnit = "";

        // Read the entire character portion -- remember the last two bytes are the CRLF
        for (std::size_t i = 1; i < mRawMeasurement.size() - 2; i++) {

            uint8_t currChar = mRawMeasurement[i];

            if (currChar != static_cast<uint8_t>(CommonASCIIValues::SPACE) && (currChar != 0)) { // Skip spaces, don't want them included in the measurement

              // Don't use the `currChar` value, it'll segfault. Remember you need the pointer to the char, not the char itself!
              measurement.append(std::string(reinterpret_cast<const char*>(mRawMeasurement.data() + i), 1));
            }


            // Check if current character is in range of:
            // uppercase letters in ASCII or lowercase letters,
            // if it is, it's part of the 'unit' description

            if (((currChar >= static_cast<uint8_t>(CommonASCIIValues::UPPER_CASE_A)) && (currChar <= static_cast<uint8_t>(CommonASCIIValues::UPPER_CASE_Z))) || ((currChar >= static_cast<uint8_t>(CommonASCIIValues::LOWER_CASE_A)) && (currChar <= static_cast<uint8_t>(CommonASCIIValues::LOWER_CASE_Z)))) {

              measurementUnit.append(std::string(reinterpret_cast<const char*>(mRawMeasurement.data() + i), 1));
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
    Units extractUnitName(const std::string measurementUnit) const {

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
          throw std::invalid_argument("Unsupported unit type: " + measurementUnit);
        }
    }


    // Members //

    bool mSign;

    double mMeasurement;
    std::string mMeasurementStr;

    std::array<uint8_t, gDataPacketLength> mRawMeasurement;

    Units mNativeUnit;
};
