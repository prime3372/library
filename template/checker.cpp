#include <bits/stdc++.h>
#include "util/static_modint.hpp"
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using namespace cp;
using ll = long long;
using mint = modint998244353;

#define check(expr) do { \
                      if (!(expr)) { \
                        std::cout << "wrong answer " << #expr << " is not satisfied" << std::endl; \
                        std::exit(1); \
                      } \
                    } while (false)

int main(int argc, char* argv[]) {
  assert(argc >= 4);
  std::ifstream f_in(argv[1]);
  std::ifstream f_out(argv[2]);
  std::ifstream f_ans(argv[3]);

  {
    string dummy;
    check(!(f_out >> dummy));
  }
}