#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "util/io_utility.hpp"

#ifdef LOCAL

#define dump(...)                               \
  [](const auto&... _args) {                    \
    std::string _args_str = #__VA_ARGS__;       \
    _args_str.append(": ");                     \
    std::cerr << _args_str;                     \
    std::string _indent(_args_str.size(), ' '); \
    std::ostringstream _oss;                    \
    _oss << std::make_tuple(_args...);          \
    for (char _c : _oss.str()) {                \
      std::cerr << _c;                          \
      if (_c == '\n') std::cerr << _indent;     \
    }                                           \
    std::cerr << "\n";                          \
  }(__VA_ARGS__)

#define msg(...) \
  [](const auto&... _args) -> void { (std::cerr << ... << _args); }(__VA_ARGS__)

#else

#define dump(...)
#define msg(...)

#endif