#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_4_C"

#include "ds/hash_set.hpp"

#include <iostream>
#include <string>

using namespace std;
using namespace cp;

int main() {
  int n;
  cin >> n;
  hash_set<string> s;
  while (n--) {
    string t, str;
    cin >> t >> str;
    if (t == "insert") s.insert(str);
    else cout << (s.count(str) ? "yes\n" : "no\n");
  }
}