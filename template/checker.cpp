#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using ll = long long;

#define must(expr) do { \
                     if (!(expr)) { \
                       cout << "wrong answer " << #expr << " is not satisfied, line " << __LINE__ << endl; \
                       exit(1); \
                     } \
                   } while (false)

#define mustnt(expr) do { \
                      if (expr) { \
                         cout << "wrong answer " << #expr << " is satisfied, line " << __LINE__ << endl; \
                         exit(1); \
                       } \
                     } while (false)

#define cin

ifstream f_in, f_out, f_ans;

void check() {

}

int main(int argc, char* argv[]) {
  assert(argc >= 4);
  f_in.open(argv[1]);
  f_out.open(argv[2]);
  f_ans.open(argv[3]);
  check();
  string dummy;
  mustnt(f_out >> dummy);
  return 0;
}