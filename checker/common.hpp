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
    std::cout << "FAIL too few arguments" << std::endl;
    std::exit(3);
  }

  f_in.open(argv[1]);
  f_out.open(argv[2]);
  f_ans.open(argv[3]);

  if (!(f_in.is_open() && f_out.is_open() && f_ans.is_open())) {
    std::cout << "FAIL cannot open files" << std::endl;
    std::exit(3);
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

bool read_as_double(const std::string& s, double& d) {
  auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), d);
  return ec == std::errc{} && ptr == s.data() + s.size();
}

double double_delta(double expected, double result) {
  double absolute = std::abs(result - expected);
  double relative = std::abs(absolute / expected);
  return std::min(absolute, relative);
}