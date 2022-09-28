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


#include <tuple>
#include <cstdint>
#include <map>
#include <pair>

#include "constants.h"

class Converter
{

    public:



    private:
        constexpr static uint8_t NUMBER_OF_SUPPORTED_UNITS = 16;
        
        // For convenience and simplicity, the reciprocal of each conversion factor is also stored in the table 
        // (hence the factor of 2)
        // The minus 2 is to account for the fact that there is no conversion factor needed in the trivial case 
        // when you're converting from grams to grams (in either direction!)
        constexpr static uint8_t CONVERSION_TABLE_SIZE = (NUMBER_OF_SUPPORTED_UNITS * 2) - 2;

        // Unit conversion tuple is: <source unit>, <destination unit>, <conversion factor>
        // e.g. to convert from milligrams into grams you would multiply by 0.001, so "0.001" is the conversion factor
        // milligram is the source unit, gram is the target unit.
        // This data comes from the conversion table (table 2)
        // The row unit is the source unit, and the column unit is the target unit
        // For the sake of simplicity, only conversion factors against grams are stored -- to convert between any two units
        // first convert into grams and then from grams into the target unit.

        std::array<std::tuple<double, Units, Units>, NUMBER_OF_SUPPORTED_UNITS * 2 - 2> conversionFactorTable = {
            std::make_tuple(0.001, Units::MILLIGRAMS, Units::GRAMS),
            std::make_tuple(0.01, Units::CENTIGRAMS, Units::GRAMS),
            std::make_tuple(1000, Units::KILOGRAMS, Units::GRAMS),
            std::make_tuple(0.2, Units::CARATS, Units::GRAMS),
            std::make_tuple(0.08573532418, Units::TOLA, Units::GRAMS),
            std::make_tuple(0.56438339119, Units::DRAM, Units::GRAMS),
            std::make_tuple(15.4323607345, Units::GRAIN, Units::GRAMS),
            std::make_tuple(0.02, Units::TAEL_JAPAN, Units::GRAMS),
            std::make_tuple(0.26666666666, Units::MOMME, Units::GRAMS),
            std::make_tuple(1.55517384, Units::PENNYWEIGHT, Units::GRAMS),
            std::make_tuple(28.3494925441, Units::OUNCES, Units::GRAMS),
            std::make_tuple(453.592909436, Units::POUNDS, Units::GRAMS),
            std::make_tuple(0.02666666666, Units::TAEL_TAIWAN, Units::GRAMS),
            std::make_tuple(31.10348, Units::TROY_OUNCE, Units::GRAMS),
            std::make_tuple(0.02645547146, Units::TAEL_HONGKONG, Units::GRAMS),
            // For convenience and simplicity, the reciprocal of each conversion factor is also stored
            std::make_tuple(1000, Units::GRAMS, Units::MILLIGRAMS),
            std::make_tuple(100, Units::GRAMS, Units::CENTIGRAMS),
            std::make_tuple(0.001, Units::GRAMS, Units::KILOGRAMS),
            std::make_tuple(5, Units::GRAMS, Units::CARATS),
            std::make_tuple(11.6638038, Units::GRAMS, Units::TOLA),
            std::make_tuple(1.77184519, Units::GRAMS, Units::DRAM),
            std::make_tuple(0.0647989, Units::GRAMS, Units::GRAIN),
            std::make_tuple(50, Units::GRAMS, Units::TAEL_JAPAN),
            std::make_tuple(3.75, Units::GRAMS, Units::MOMME),
            std::make_tuple(0.6430149, Units::GRAMS, Units::PENNYWEIGHT),
            std::make_tuple(0.035274, Units::GRAMS, Units::OUNCES),
            std::make_tuple(0.0022, Units::GRAMS, Units::POUNDS)
        }


        std::map<std::pair<Units, Units>, double> conversionTable = {

            { std::make_pair<Units, Units>(Units::MILLIGRAMS, Units::GRAMS), 0.001 },
            { std::make_pair<Units, Units>(Units::CENTIGRAMS, Units::GRAMS), 0.01 },
            { std::make_pair<Units, Units>(Units::KILOGRAMS, Units::GRAMS), 1000 },
            { std::make_pair<Units, Units>(Units::CARATS, Units::GRAMS), 0.2 },
            { std::make_pair<Units, Units>(Units::TOLA, Units::GRAMS), 0.08573532418 },
            { std::make_pair<Units, Units>(Units::DRAM, Units::GRAMS), 0.56438339119 },
            { std::make_pair<Units, Units>(Units::GRAIN, Units::GRAMS), 15.4323607345 },
            { std::make_pair<Units, Units>(Units::TAEL_JAPAN, Units::GRAMS), 0.02 },
            { std::make_pair<Units, Units>(Units::MOMME, Units::GRAMS), 0.26666666666 },
            { std::make_pair<Units, Units>(Units::PENNYWEIGHT, Units::GRAMS), 1.55517384 },
            { std::make_pair<Units, Units>(Units::OUNCES, Units::GRAMS), 28.3494925441 },
            { std::make_pair<Units, Units>(Units::POUNDS, Units::GRAMS), 453.592909436 },
            { std::make_pair<Units, Units>(Units::TAEL_TAIWAN, Units::GRAMS), 0.02666666666 },
            { std::make_pair<Units, Units>(Units::TROY_OUNCE, Units::GRAMS), 31.10348 },
            { std::make_pair<Units, Units>(Units::TAEL_HONGKONG, Units::GRAMS), 0.02645547146 },
            // The reciprocals of the conversion units above
            { std::make_pair<Units, Units>(Units::GRAMS, Units::MILLIGRAMS), 1000 },
            { std::make_pair<Units, Units>(Units::GRAMS, Units::CENTIGRAMS), 100 },
            { std::make_pair<Units, Units>(Units::GRAMS, Units::KILOGRAMS), 0.001 },
            { std::make_pair<Units, Units>(Units::GRAMS, Units::CARATS), 5 },
            { std::make_pair<Units, Units>(Units::GRAMS, Units::TOLA), 11.6638038 },
            { std::make_pair<Units, Units>(Units::GRAMS, Units::DRAM), 1.77184519 },
            { std::make_pair<Units, Units>(Units::GRAMS, Units::GRAIN), 0.0647989 },
            { std::make_pair<Units, Units>(Units::GRAMS, Units::TAEL_JAPAN), 50 },
            { std::make_pair<Units, Units>(Units::GRAMS, Units::MOMME), 3.75 },
            { std::make_pair<Units, Units>(Units::GRAMS, Units::PENNYWEIGHT), 0.6430149 },
            { std::make_pair<Units, Units>(Units::GRAMS, Units::OUNCES), 0.035274 },
            { std::make_pair<Units, Units>(Units::GRAMS, Units::POUNDS), 0.0022 },
            { std::make_pair<Units, Units>(Units::GRAMS, Units::TAEL_TAIWAN), 37.5 },
            { std::make_pair<Units, Units>(Units::GRAMS, Units::TROY_OUNCE), 0.0321507432 },
            { std::make_pair<Units, Units>(Units::GRAMS, Units::TAEL_HONGKONG), 37.799364169 }
        }
};