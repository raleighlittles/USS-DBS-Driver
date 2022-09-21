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
    TAEL_JAPAN, // https://en.wikipedia.org/wiki/Tael - The regular Chinese (and Japanese) version
    MOMME, // https://en.wikipedia-.org/wiki/Pearl#Momme_weight
    PENNYWEIGHT, // https://en.wikipedia.org/wiki/Pennyweight
    OUNCES, // https://en.wikipedia.org/wiki/Ounce#International_avoirdupois_ounce
    POUNDS, // https://en.wikipedia.org/wiki/Pound_(mass)
    TAEL_TAIWAN, // https://en.wikipedia.org/wiki/Tael - Taiwan variant
    TROY_OUNCE, // https://en.wikipedia.org/wiki/Troy_weight
    TAEL_HONGKONG, // https://en.wikipedia.org/wiki/Tael - Hong Kong variant
    PERCENT // ???
};


///     Important ASCII values used -- these show up in each message
///     012   10    0A    LF  '\n' (new line)
///     015   13    0D    CR  '\r' (carriage ret)
///     040   32    20    SPACE
///     053   43    2B    +
///     055   45    2D    -
///     056   46    2E    .
enum class CommonASCIIValues : uint8_t
{
    NEWLINE = 0x0A,
    CARRIAGE_RET = 0x0D,
    SPACE = 0x20,
    PLUS_SIGN = 0x2B,
    MINUS_SIGN = 0x2D,
    PERIOD = 0x2E
};
