#pragma once

#include <algorithm>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

enum result { _ok = 0, _wa = 1, _pe = 2, _fail = 3 };

std::ifstream fin, fout, fans;

void open_files(int argc, char** argv) {
  if (argc < 4) {
    std::cout << "FAIL too few arguments" << std::endl;
    std::exit(_fail);
  }

  fin.open(argv[1]);
  fout.open(argv[2]);
  fans.open(argv[3]);

  if (!(fin.is_open() && fout.is_open() && fans.is_open())) {
    std::cout << "FAIL cannot open files" << std::endl;
    std::exit(_fail);
  }
}

std::string ordinal_suffix(int x) {
  x %= 100;
  if (x / 10 == 1) return "th";
  if (x % 10 == 1) return "st";
  if (x % 10 == 2) return "nd";
  if (x % 10 == 3) return "rd";
  return "th";
}

bool read_as_ll(const std::string& s, long long& n) {
  auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), n);
  return ec == std::errc{} && ptr == s.data() + s.size();
}

bool read_as_double(const std::string& s, double& n) {
  auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), n);
  return ec == std::errc{} && ptr == s.data() + s.size();
}

double double_delta(double expected, double result) {
  double absolute = std::abs(result - expected);
  double relative = std::abs(absolute / expected);
  return std::min(absolute, relative);
}