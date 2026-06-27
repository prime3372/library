#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "usage: " << argv[0] << " <user_out> <expected_ans>" << std::endl;
    return 2;
  }

  std::ifstream f1(argv[1]);
  std::ifstream f2(argv[2]);

  if (!f1.is_open() || !f2.is_open()) {
    std::cerr << "error opening files" << std::endl;
    return 2;
  }

  std::string t1, t2;
  int token_count = 0;

  while (true) {
    bool has_t1 = bool(f1 >> t1);
    bool has_t2 = bool(f2 >> t2);
    if (!has_t1 && !has_t2) {
      std::cout << "ok " << token_count << " tokens" << std::endl;
      return 0;
    }   
    token_count++;

    if (has_t1 && !has_t2) {
      std::cout << "wrong answer Participant output contains extra tokens" << std::endl;
      return 1;
    }

    if (!has_t1 && has_t2) {
      std::cout << "wrong answer Unexpected EOF in the participants output" << std::endl;
      return 1;
    }

    if (t1 != t2) {
      std::cout << "wrong answer " << token_count;
      std::cout << (token_count % 10 == 1 ? "st " : token_count % 10 == 2 ? "nd " : token_count == 3 ? "rd " : "th ");
      std::cout << "words differ - ";
      std::cout << "expected: '" << t2 << "', ";
      std::cout << "found: '" << t1 << "'" << std::endl; 
      return 1;
    }
  }
}
