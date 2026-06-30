#include "checker.hpp"

int main(int argc, char* argv[]) {
  open_files(argc, argv);

  std::string t_out, t_ans;
  int t_cnt = 0;

  while (f_ans >> t_ans) {
    if (!(f_out >> t_out)) {
      std::cout << "wrong answer Unexpected EOF in the participants output" << std::endl;
      return 1;
    }
    t_cnt++;
    if (t_out != t_ans) {
      std::cout << "wrong answer " << t_cnt << ordinal_suffix(t_cnt) << " words differ - ";
      std::cout << "expected: '" << t_ans << "', ";
      std::cout << "found: '" << t_out << "'" << std::endl; 
      return 1;
    }
  }

  if (f_out >> t_out) {
    std::cout << "wrong answer Participant output contains extra tokens" << std::endl;
    return 1;
  }

  std::cout << "ok " << t_cnt << " tokens" << std::endl;
  return 0;
}
