#include <iostream>
#include <fstream>
#include <string>

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
      std::cout << "ok " << token_count << " tokens" << std::endl;
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

    if (t_out != t_ans) {
      std::cout << "wrong answer " << token_count;
      std::cout << (token_count % 10 == 1 ? "st " : token_count % 10 == 2 ? "nd " : token_count == 3 ? "rd " : "th ");
      std::cout << "words differ - ";
      std::cout << "expected: '" << t_ans << "', ";
      std::cout << "found: '" << t_out << "'" << std::endl; 
      return 1;
    }
  }
}
