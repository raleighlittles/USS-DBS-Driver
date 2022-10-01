/**
 * @file Measurement.hpp
 * @author Raleigh Littles (raleighlittles@gmail.com)
 * @brief Class that represents a 'Measurement' object from the scale,
 *        responsible for parsing message and converting to printable format
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
      : mRawMeasurement(rawMeasurementBytes) {}

  std::string getMeasurement(const std::string desiredUnitName)
  {

    decodeRawMeasurement();

    const Units requestedMeasurementUnit = extractUnitName(desiredUnitName);

    // The simple case: The unit is requested in the same format its already stored in, so no conversion is needed
    if (requestedMeasurementUnit == mNativeUnit)
    {
      return mMeasurementStr;
    }

    else
    {
      return std::to_string(Converter::convertMeasurement(mMeasurement, mNativeUnit, requestedMeasurementUnit));
    }
  }

  // Returns the raw measurement as received by the scale
  double getNativeMeasurement()
  {
    return mMeasurement;
  }

private:
  /// @brief Main function of this class: decodes the series of raw bytes into a measurement
  ///     Side-effect: stores the measurement and native unit in the class
  ///     Read the whole documentation to understand how the data is stored.
  /// @return
  void decodeRawMeasurement()
  {

    // To start, conduct basic sanity checks -- verifying the message starts correctly (with a plus or minus sign),
    // and ends correctly (with a carriage return and a newline)

    uint8_t sign = mRawMeasurement.at(0);

    if (sign == static_cast<uint8_t>(CommonASCIIValues::MINUS_SIGN))
    {
      throw std::runtime_error("Negative measurements not supported. Please TARE the scale before use");
    }

    if (sign != static_cast<uint8_t>(CommonASCIIValues::PLUS_SIGN))
    {
      // If this isn't a plus or minus, then the data format didn't match what was expected
      throw std::invalid_argument("Unable to determine sign (+/-) of measurement, data does not match expected format");
    }

    // Now that the measurement must be valid, begin parsing.
    std::string measurement = "";

    // The units are included in the measurement itself, eg `measurement` will be "8 lbs" while measurementUnits will be "lbs"
    std::string measurementUnit = "";

    // Read the entire character portion -- remember the last two bytes are the CRLF
    for (std::size_t i = 1; i < mRawMeasurement.size() - 2; i++)
    {

      uint8_t currChar = mRawMeasurement[i];

      // Extract only the numeric part of the measurement, e.g. "+1.23g" becomes "1.23" -- the units get parsed separately below
      if (((currChar >= static_cast<uint8_t>(CommonASCIIValues::DIGIT_ZERO)) && (currChar <= static_cast<uint8_t>(CommonASCIIValues::DIGIT_NINE))) || (currChar == static_cast<uint8_t>(CommonASCIIValues::PERIOD)))
      {

        // Don't use the `currChar` value, it'll segfault. Remember you need the pointer to the char, not the char itself!
        measurement.append(std::string(reinterpret_cast<const char *>(mRawMeasurement.data() + i), 1));
      }

      // Check if current character is in range of:
      // uppercase letters in ASCII or lowercase letters,
      // if it is, it's part of the 'unit' description

      if (((currChar >= static_cast<uint8_t>(CommonASCIIValues::UPPER_CASE_A)) &&
           (currChar <= static_cast<uint8_t>(CommonASCIIValues::UPPER_CASE_Z))) ||
          ((currChar >= static_cast<uint8_t>(CommonASCIIValues::LOWER_CASE_A)) &&
           (currChar <= static_cast<uint8_t>(CommonASCIIValues::LOWER_CASE_Z))))
      {

        measurementUnit.append(std::string(reinterpret_cast<const char *>(mRawMeasurement.data() + i), 1));
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
  Units extractUnitName(const std::string measurementUnit) const
  {

    if (measurementUnit == "g")
    {
      return Units::GRAMS;
    }

    else if (measurementUnit == "kg")
    {
      return Units::KILOGRAMS;
    }

    else if (measurementUnit == "ct")
    {
      return Units::CARATS;
    }

    else if (measurementUnit == "T")
    {
      return Units::TOLA;
    }

    else if (measurementUnit == "TAR")
    {
      return Units::TAR;
    }

    else if (measurementUnit == "dr")
    {
      return Units::DRAM;
    }

    else if (measurementUnit == "PKT")
    {
      return Units::PKT;
    }

    else if (measurementUnit == "GN")
    {
      return Units::GRAIN;
    }

    else if (measurementUnit == "TMR")
    {
      return Units::TMR;
    }

    else if (measurementUnit == "gsm")
    {
      return Units::GSM;
    }

    else if (measurementUnit == "tlJ")
    {
      return Units::TAEL_JAPAN;
    }

    else if (measurementUnit == "mo")
    {
      return Units::MOMME;
    }

    else if (measurementUnit == "dwt")
    {
      return Units::PENNYWEIGHT;
    }

    else if (measurementUnit == "oz")
    {
      return Units::OUNCES;
    }

    else if (measurementUnit == "lb")
    {
      return Units::POUNDS;
    }

    else if (measurementUnit == "tlT")
    {
      return Units::TAEL_TAIWAN;
    }

    else if (measurementUnit == "ozt")
    {
      return Units::TROY_OUNCE;
    }

    else if (measurementUnit == "tlH")
    {
      return Units::TAEL_HONGKONG;
    }

    else if (measurementUnit == "%")
    {
      return Units::PERCENT;
    }

    else
    {
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
