#include "template/template.hpp"

int main() {
  iflocal {
    cout << unitbuf;
  }
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}