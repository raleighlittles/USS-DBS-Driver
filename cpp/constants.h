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

#pragma once

const uint8_t gDataPacketLength = 17;

enum class Units
{
    GRAMS,
    CENTIGRAMS,
    MILLIGRAMS,
    KILOGRAMS,
    CARATS,
    TOLA,
    TAR,
    DRAM,
    PKT,
    GRAIN,
    TMR,
    GSM,
    TAEL_JAPAN,
    MOMME,
    PENNYWEIGHT,
    OUNCES,
    POUNDS,
    TAEL_TAIWAN,
    TROY_OUNCE, 
    TAEL_HONGKONG, 
    PERCENT
};


///     Important ASCII values used
///
///     Oct   Dec   Hex   Char
///     012   10    0A    LF  '\n' (new line)
///     015   13    0D    CR  '\r' (carriage ret)
///     040   32    20    SPACE
///     053   43    2B    +
///     055   45    2D    -
///     056   46    2E    .
///     101   65    41    A
///     132   90    5A    Z
///     141   97    61    a
///     172   122   7A    z

enum class CommonASCIIValues : uint8_t
{
    NEWLINE = 0x0A,
    CARRIAGE_RET = 0x0D,
    SPACE = 0x20,
    PLUS_SIGN = 0x2B,
    MINUS_SIGN = 0x2D,
    PERIOD = 0x2E,
    UPPER_CASE_A = 0x41,
    UPPER_CASE_Z = 0x5A,
    LOWER_CASE_A = 0x61,
    LOWER_CASE_Z = 0x7A
};
