#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using ll = long long;

#undef assert
#define assert(expr) do { \
                       if (!(expr)) { \
                         cout << "wrong answer " << #expr << " is not satisfied, line " << __LINE__ << endl; \
                         exit(1); \
                       } \
                     } while (false)

#define cin

ifstream f_in, f_out, f_ans;

int main(int, char* argv[]) {
  f_in.open(argv[1]);
  f_out.open(argv[2]);
  f_ans.open(argv[3]);

  return 0;
}