#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

std::ifstream f_in, f_out, f_ans;

void open_files(int argc, char** argv) {
  if (argc < 4) {
    std::cout << "usage: " << argv[0] << " <input-file> <output-file> <answer-file>" << std::endl;
    std::exit(2);
  }

  f_in.open(argv[1]);
  f_out.open(argv[2]);
  f_ans.open(argv[3]);

  if (!f_in.is_open() || !f_out.is_open() || !f_ans.is_open()) {
    std::cout << "error opening files" << std::endl;
    std::exit(2);
  }
}

inline std::string ordinal_suffix(int x) {
  x %= 100;
  if (x / 10 == 1) return "th";
  if (x % 10 == 1) return "st";
  if (x % 10 == 2) return "nd";
  if (x % 10 == 3) return "rd";
  return "th";
}

bool read_as_double(const std::string& t, double& n) {
  try {
    size_t pos;
    n = std::stod(t, &pos);
    if (pos != t.size()) throw std::runtime_error("");
  } catch (...) {
    return false;
  }
  return true;
}

inline double double_delta(double expected, double result) {
  double absolute = std::abs(result - expected);
  double relative = std::abs(absolute / expected);
  return std::min(absolute, relative);
}