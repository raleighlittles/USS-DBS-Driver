/**
 * @file constants.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <cstdint>

const uint8_t gDataPacketLength = 17;

enum class Units
{
    GRAMS,
    KILOGRAMS,
    CARATS, // https://en.wikipedia.org/wiki/Carat_(mass)
    TOLA, // https://en.wikipedia.org/wiki/Tola_(unit)
    TAR, // ???
    DRAM, // https://en.wikipedia.org/wiki/Dram_(unit)
    PKT, // ???
    GRAIN, // https://en.wikipedia.org/wiki/Grain_(unit)
    TMR, // ???
    GSM, // https://en.wikipedia.org/wiki/Grammage
    TLJ, // ???
    MO, // ???
    DWT, // https://en.wikipedia.org/wiki/Pennyweight
    OZ,
    LB,
    TLT, // https://en.wikipedia.org/wiki/Tael - Tawain variant
    OZT, // https://en.wikipedia.org/wiki/Troy_weight
    TLH, // https://en.wikipedia.org/wiki/Tael - Hong Kong variant
};

