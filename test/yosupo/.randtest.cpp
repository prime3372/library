#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;

random_device seed_gen;
mt19937_64 mt(seed_gen());

int main() {
//  ios_base::sync_with_stdio(false);
//  cin.tie(nullptr);
  int n = 1000, q = 1000;
  cerr << n << " " << q << "\n";
  multiset<int> s;
  vector<int> ans;
  rep(i, 0, n) {
    int si = mt() % 10;
    cerr << si << " ";
    s.insert(si);
  }
  cerr << "\n";
  while (q--) {
    int t = mt() % 3; 
    cerr << t << " ";
    if (t == 0) {
      int x = mt() % 10;
      cerr << x << " ";
      s.insert(x);
    } else if (t == 1) {
      auto x = s.begin();
      ans.push_back(*x);
      s.erase(x);
    } else {
      auto x = --s.end();
      ans.push_back(*x);
      s.erase(x);
    }
    cerr << "\n";
  }
  cerr << "hoge";
  for (int a : ans) cout << a << "\n"; 
}