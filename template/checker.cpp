#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
#define all(a) a.begin(), a.end()
using namespace std;
using ll = long long;
template <class T> bool chmin(T& a, T b) { if (b < a) { a = b; return 1; } else return 0; }
template <class T> bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } else return 0; }

#undef assert
#define assert(expr) do { \
                       if (!(expr)) { \
                         cout << "wrong answer '" << #expr << "' is not satisfied, line " << __LINE__ << endl; \
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