#include "template/template.hpp"

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  if (local) cout << unitbuf;
  i128 x = 1;
  cout << make_tuple(x) << "\n";
}