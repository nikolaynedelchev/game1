#pragma once
#include <iostream>
#include <string>
#include <map>
#include <cinttypes>

#include <raylib.h>
#include <raygui.h>
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

#include "image_loader.h"
#include "sprite.h"
