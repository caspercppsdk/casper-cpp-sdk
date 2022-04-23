/*
    This file is created mainly for working with big integers but other global
   definitions can also be added here.

    We are using a library for big integers:
        https://github.com/sercantutar/infint

    in case a different approach is needed in the future, we will we use a
   typename for big integers.
*/

#pragma once

#include "infint/infint.h"
typedef InfInt big_int;
/*
typedef unsigned long long TimeDiff;

TimeDiff string_to_timediff (const std::string &str) {
    std::istringstream iss(str);
    TimeDiff result;
    iss >> result;
    return result;
}
*/



