#include <iomanip>

#include "checker/common.hpp"

constexpr int display_max = 30;

int main(int argc, char** argv) {
  open_files(argc, argv);

  std::string t_j, t_p;
  int cnt = 0;
  long long n_j, n_p;
  std::string t_first;

  while (fans >> t_j) {
    if (!(fout >> t_p)) {
      int extra_ans_cnt = 1;
      while (fans >> t_p) extra_ans_cnt++;
      std::cout << "wrong answer Answer contains longer sequence [length = "
                << cnt + extra_ans_cnt << "], but output contains " << cnt
                << " elements" << std::endl;
      return _wa;
    }

    cnt++;

    if (!read_as_ll(t_j, n_j)) {
      std::cout << "FAIL Expected integer, but '" << t_j << "' found"
                << std::endl;
      return _fail;
    }
    if (!read_as_ll(t_p, n_p)) {
      std::cout << "wrong output format Expected integer, but '" << t_p
                << "' found" << std::endl;
      return _pe;
    }

    if (n_j != n_p) {
      std::cout << "wrong answer " << cnt << ordinal_suffix(cnt)
                << " numbers differ - expected: '" << n_j << "', found: '"
                << n_p << "'" << std::endl;
      return _wa;
    } else if (cnt <= display_max) {
      if (!t_first.empty()) t_first.push_back(' ');
      t_first.append(std::to_string(n_p));
    }
  }

  int extra_out_cnt = 0;
  while (fout >> t_p) extra_out_cnt++;  
  if (extra_out_cnt > 0) {
    std::cout << "wrong answer Output contains longer sequence [length = "
              << cnt + extra_out_cnt << "], but answer contains " << cnt
              << "elements" << std::endl;
    return _wa;
  }

  if (cnt <= display_max) {
    std::cout << "ok " << cnt << " number(s): \"" << t_first << "\""
              << std::endl;
  } else {
    std::cout << "ok " << cnt << " numbers" << std::endl;
  }
  return _ok;
}