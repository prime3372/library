#include "checker/checker.hpp"
#include <cstdlib>

int main(int argc, char* argv[]) {
  open_files(argc, argv);

  std::string t_out, t_ans;
  int t_cnt = 0;

  while (f_ans >> t_ans) {
    if (!(f_out >> t_out)) {
      std::cout << "wrong answer Unexpected EOF in the participants output" << std::endl;
      std::exit(1);
    }

    t_cnt++;

    if (t_out != t_ans) {
      std::cout << "wrong answer " << t_cnt << ordinal_suffix(t_cnt) << " words differ - ";
      std::cout << "expected: '" << t_ans << "', ";
      std::cout << "found: '" << t_out << "'" << std::endl; 
      std::exit(1);
    }
  }

  if (f_out >> t_out) {
    std::cout << "wrong answer Participant output contains extra tokens" << std::endl;
    std::exit(1);
  }

  if (t_cnt == 1) {
    std::cout << "ok '" << t_out << "'" << std::endl;
    std::exit(0);
  }
  std::cout << "ok " << t_cnt << " tokens" << std::endl;
}