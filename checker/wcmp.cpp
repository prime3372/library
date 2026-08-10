#include "checker/common.hpp"

int main(int argc, char* argv[]) {
  open_files(argc, argv);

  std::string t_j, t_p;
  int cnt = 0;

  while (fans >> t_j) {
    if (!(fout >> t_p)) {
      std::cout << "wrong answer Unexpected EOF in the participants output" << std::endl;
      return _wa;
    }

    cnt++;

    if (t_j != t_p) {
      std::cout << "wrong answer " << cnt << ordinal_suffix(cnt) << " words differ - ";
      std::cout << "expected: '" << t_j << "', ";
      std::cout << "found: '" << t_p << "'" << std::endl; 
      return _wa;
    }
  }

  if (fout >> t_p) {
    std::cout << "wrong answer Participant output contains extra tokens" << std::endl;
    return _wa;
  }

  if (cnt == 1) {
    std::cout << "ok \"" << t_p << "\"" << std::endl;
  } else {
    std::cout << "ok " << cnt << " tokens" << std::endl;
  }
  return _ok;
}