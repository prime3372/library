#include "checker/checker.hpp"
#include <iomanip>

constexpr double max_error = 1E-9;
constexpr int display_precision = 10;

int main(int argc, char** argv) {
  open_files(argc, argv);

  std::cout << std::fixed << std::setprecision(display_precision);

  std::string t_out, t_ans;
  int t_cnt = 0;
  double n_out, n_ans;

  while (f_ans >> t_ans) {
    if (!(f_out >> t_out)) {
      std::cout << "wrong answer Unexpected EOF in the participants output" << std::endl;
      return 1;
    }

    t_cnt++;

    if (!read_as_double(t_ans, n_ans)) {
      std::cout << "FAIL Expected double, but '" << t_ans << "' found" << std::endl;
      return 2;
    }
    if (!read_as_double(t_out, n_out)) {
      std::cout << "wrong output format Expected double, but '" << t_out << "' found" << std::endl;
      return 1;
    }

    if (double_delta(n_ans, n_out) > max_error) {
      std::cout << "wrong answer " << t_cnt << ordinal_suffix(t_cnt) << " numbers differ - ";
      std::cout << "expected: '" << n_ans << "', ";
      std::cout << "found: '" << n_out << "', "; 
      std::cout << "error = '" << double_delta(n_ans, n_out) << "'" << std::endl; 
      return 1;
    }
  }

  if (f_out >> t_out) {
    std::cout << "wrong answer Participant output contains extra tokens" << std::endl;
    return 1;
  }

  if (t_cnt == 1) {
    std::cout << "ok found '" << n_out << "', expected '" << n_ans << "', error '" << double_delta(n_ans, n_out) << "'" << std::endl;
    return 0;
  }
  std::cout << "ok " << t_cnt << " numbers" << std::endl;
}