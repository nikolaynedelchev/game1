#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cinttypes>
#include <cmath>
#include <fmt/format.h>

using namespace std;

template <typename S, typename... T>
inline void Print(const S& fmt, T&&... args)
{
    std::cout << vformat(fmt, fmt::make_format_args(args...));
}

template <typename S, typename... T>
inline void PrintLn(const S& fmt, T&&... args)
{
    std::cout << vformat(fmt, fmt::make_format_args(args...)) << std::endl;
}

template <typename S, typename... T>
[[noreturn]]
inline void FatalError(const S& fmt, T&&... args)
{
    std::string msg = vformat(fmt, fmt::make_format_args(args...));
    std::cout << msg << std::endl << std::flush;
    throw std::runtime_error(msg);
}

#include "operators.h"