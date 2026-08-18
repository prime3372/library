#include <iomanip>

#include "checker/common.hpp"

constexpr double max_error = 1E-9;
constexpr int display_precision = 10;

int main(int argc, char** argv) {
  open_files(argc, argv);

  std::cout << std::fixed << std::setprecision(display_precision);

  std::string t_j, t_p;
  int cnt = 0;
  double n_j, n_p;

  while (fans >> t_j) {
    if (!(fout >> t_p)) {
      std::cout << "wrong answer Unexpected EOF in the participants output"
                << std::endl;
      return _wa;
    }

    cnt++;

    if (!read_as_double(t_j, n_j)) {
      std::cout << "FAIL Expected double, but '" << t_j << "' found"
                << std::endl;
      return _fail;
    }
    if (!read_as_double(t_p, n_p)) {
      std::cout << "wrong output format Expected double, but '" << t_p
                << "' found" << std::endl;
      return _pe;
    }

    if (double_delta(n_j, n_p) > max_error) {
      std::cout << "wrong answer " << cnt << ordinal_suffix(cnt)
                << " numbers differ - expected: '" << n_j << "', found: '"
                << n_p << "', error = '" << double_delta(n_j, n_p) << "'"
                << std::endl;
      return _wa;
    }
  }

  if (fout >> t_p) {
    std::cout << "wrong answer Participant output contains extra tokens"
              << std::endl;
    return _wa;
  }

  if (cnt == 1) {
    std::cout << "ok found '" << n_p << "', expected '" << n_j << "', error '"
              << double_delta(n_j, n_p) << "'" << std::endl;
  } else {
    std::cout << "ok " << cnt << " numbers" << std::endl;
  }
  return _ok;
}