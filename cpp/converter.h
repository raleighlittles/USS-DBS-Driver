/**
 * @file converter.h
 * @author Raleigh Littles (raleighlittles@gmail.com)
 * @brief Class used to convert units
 * @version 0.1
 * @date 2022-09-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <cstdint>
#include <map>
#include <stdexcept>
#include <tuple>
#include <utility>

#include "constants.h"

#pragma once

class Converter
{

public:
    static double convertMeasurement(double input, Units sourceUnit, Units destinationUnit)
    {

        const auto it = mConversionTable.find({sourceUnit, destinationUnit});

        if (it == mConversionTable.end())
        {
            throw std::invalid_argument("Can't convert measurement -- unsupported unit type");
        }

        else
        {
            return (it->second * input);
        }
    }

private:
    constexpr static uint8_t NUMBER_OF_SUPPORTED_UNITS = 16;

    // For convenience and simplicity, the reciprocal of each conversion factor is also stored in the table
    // (hence the factor of 2)
    // The minus 2 is to account for the fact that there is no conversion factor needed in the trivial case
    // when you're converting from the same unit (in either direction!)
    // i.e. there's no need to store the conversion factor when you're going from grams to grams (because it's just 1)
    constexpr static uint8_t CONVERSION_TABLE_SIZE = (NUMBER_OF_SUPPORTED_UNITS * 2) - 2;

    // Unit conversion tuple is: <source unit>, <destination unit>, <conversion factor>
    // e.g. to convert from milligrams into grams you would multiply by 0.001, so "0.001" is the conversion factor
    // milligram is the source unit, gram is the target unit.
    // This data comes from the conversion table (table 2)
    // The row unit is the source unit, and the column unit is the target unit
    // For the sake of simplicity, only conversion factors against grams are stored -- to convert between any two units
    // first convert into grams and then from grams into the target unit.
    static const std::map<std::pair<Units, Units>, double> mConversionTable;
};