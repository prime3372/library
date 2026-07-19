#include "checker/checker.hpp"
#include <cstdlib>
#include <iomanip>

constexpr double max_error = 1E-4;
constexpr int display_precision = 5;

int main(int argc, char** argv) {
  open_files(argc, argv);

  std::string t_out, t_ans;
  int t_cnt = 0;
  long long n_out, n_ans;
  std::string t_first;

  while (f_ans >> t_ans) {
    if (!(f_out >> t_out)) {
      int extra_ans_cnt = 1;
      while ((f_ans >> t_ans)) {
        extra_ans_cnt++;
      }
      std::cout << "Answer contains longer sequence [length = " << t_cnt + extra_ans_cnt << "], ";
      std::cout << "but output contains " << t_cnt << " elements" << std::endl;
      std::exit(1);
    }

    t_cnt++;

    if (!read_as_ll(t_ans, n_ans)) {
      std::cout << "FAIL Expected integer, but '" << t_ans << "' found" << std::endl;
      std::exit(2);
    }
    if (!read_as_ll(t_out, n_out)) {
      std::cout << "wrong output format Expected integer, but '" << t_out << "' found" << std::endl;
      std::exit(1);
    }

    if (n_ans != n_out) {
      std::cout << "wrong answer " << t_cnt << ordinal_suffix(t_cnt) << " numbers differ - ";
      std::cout << "expected: '" << n_ans << "', ";
      std::cout << "found: '" << n_out << "'" << std::endl;
      std::exit(1);
    } else if (t_cnt <= 5) {
      if (!t_first.empty()) {
        t_first.push_back(' ');
      }
      t_first.append(std::to_string(n_out));
    }
  }

  int extra_out_cnt = 0;

  while (f_out >> t_out) {
    extra_out_cnt++;
  }

  if (extra_out_cnt > 0) {
    std::cout << "wrong answer Output contains longer sequence [length = " << t_cnt + extra_out_cnt << "], ";
    std::cout << "but answer contains " << t_cnt << "elements" << std::endl;
    std::exit(1);
  }

  if (t_cnt <= 5) {
    std::cout << "ok "<< t_cnt << " number(s): \"" << t_first << "\"" << std::endl;
    std::exit(0);
  }

  std::cout << "ok " << t_cnt << " numbers" << std::endl;
}