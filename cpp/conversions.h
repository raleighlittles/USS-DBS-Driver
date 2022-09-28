/**
 * @file conversions.h
 * @author your name (you@domain.com)
 * @brief Conversion constants
 * @version 0.1
 * @date 2022-09-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <vector>
#include <tuple>
#include <cstdint>
#include <array>

#include "constants.h"

class Converter
{

    public:



    private:
        constexpr static uint8_t NUMBER_OF_SUPPORTED_UNITS = 16;

        std::array<std::tuple<double, Units, Units>, NUMBER_OF_SUPPORTED_UNITS * NUMBER_OF_SUPPORTED_UNITS> conversionFactorTable = {
            {}
        }

    

};