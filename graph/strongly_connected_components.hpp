#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

namespace cp {

// Tarjan's strongly connected components algorithm
class strongly_connected_components {
 public:
  strongly_connected_components() : strongly_connected_components(0) {}
  explicit strongly_connected_components(int _n) : id(_n), n(_n), g(_n) {}

  void add_edge(int from, int to) {
    assert(0 <= from && from < n);
    assert(0 <= to && to < n);
    g[from].push_back(to);
  }

  int group_num = -1;
  // `id[u] == id[v]` : It is possible to go from u to v and from `v` to `u`.
  // `id[u] < id[v]` : It is impossible to go from `v` to `u`.
  std::vector<int> id;
  // Each `v` is contained in `groups[id[v]]`.
  std::vector<std::vector<int>> groups;

  strongly_connected_components& build() {
    int now_ord = 0;
    std::vector<int> st, low(n), ord(n, -1);
    st.reserve(n);
    group_num = 0;

    auto dfs = [&](auto self, int v) -> void {
      low[v] = ord[v] = now_ord++;
      st.push_back(v);
      for (int to : g[v]) {
        if (ord[to] == -1) {
          self(self, to);
          low[v] = std::min(low[v], low[to]);
        } else {
          low[v] = std::min(low[v], ord[to]);
        }
      }
      if (low[v] == ord[v]) {
        while (true) {
          int u = st.back();
          st.pop_back();
          ord[u] = n;
          id[u] = group_num;
          if (u == v) break;
        }
        group_num++;
      }
    };
    for (int i = 0; i < n; i++) {
      if (ord[i] == -1) dfs(dfs, i);
    }
    for (int& x : id) x = group_num - 1 - x;

    groups.assign(group_num, {});
    for (int i = 0; i < n; i++) groups[id[i]].push_back(i);

    return *this;
  }

 private:
  int n;
  std::vector<std::vector<int>> g;
};

}  // namespace cp