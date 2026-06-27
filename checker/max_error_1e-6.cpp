#include <cmath>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>

constexpr double max_error = 1e-6;
constexpr int precision = 6;

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "usage: " << argv[0] << " <user_out> <expected_ans>" << std::endl;
    return 2;
  }

  std::ifstream f_out(argv[1]);
  std::ifstream f_ans(argv[2]);

  if (!f_out.is_open() || !f_ans.is_open()) {
    std::cerr << "error opening files" << std::endl;
    return 2;
  }

  std::string t_out, t_ans;
  int token_count = 0;

  while (true) {
    bool has_t_out = bool(f_out >> t_out);
    bool has_t_ans = bool(f_ans >> t_ans);
    if (!has_t_out && !has_t_ans) {
      std::cout << "ok " << token_count << " numbers" << std::endl;
      return 0;
    }
    token_count++;

    if (has_t_out && !has_t_ans) {
      std::cout << "wrong answer Participant output contains extra tokens" << std::endl;
      return 1;
    }

    if (!has_t_out && has_t_ans) {
      std::cout << "wrong answer Unexpected EOF in the participants output" << std::endl;
      return 1;
    }

    double n_out;
    try {
      size_t pos;
      n_out = std::stod(t_out, &pos);
      if (pos != t_out.size()) throw std::runtime_error("");
    } catch(...) {
      std::cout << "wrong output format Expected double, but " << t_out << " found" << std::endl;
      return 1;
    }

    double n_ans = std::stold(t_ans);
    if (std::abs(n_out - n_ans) > max_error) {
      std::cout << std::fixed << std::setprecision(precision);
      std::cout << "wrong answer " << token_count;
      std::cout << (token_count % 10 == 1 ? "st " : token_count % 10 == 2 ? "nd " : token_count == 3 ? "rd " : "th ");
      std::cout << "numbers differ - ";
      std::cout << "expected: '" << n_ans << "', ";
      std::cout << "found: '" << n_out << "', "; 
      std::cout << "error: '" << std::abs(n_out - n_ans) << "'" << std::endl; 
      return 1;
    }
  }
}
