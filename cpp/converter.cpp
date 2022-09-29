/**
 * @file converter.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */



#include "converter.h"
#include "constants.h"

const std::map<std::pair<Units, Units>, double> Converter::mConversionTable =
{
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
};