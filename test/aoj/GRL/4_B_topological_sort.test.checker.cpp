#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char* argv[]) {
  std::ifstream in(argv[1]);
  std::ifstream out(argv[2]);

  int V, E;
  if (!(in >> V >> E)) return 1;

  std::vector<std::vector<int>> adj(V);
  for (int i = 0; i < E; ++i) {
    int u, v;
    in >> u >> v;
    adj[u].push_back(v);
  }

  std::vector<int> res(V);
  std::vector<int> pos(V, -1);
  for (int i = 0; i < V; ++i) {
    if (!(out >> res[i])) {
      return 1;
    }
    if (res[i] < 0 || res[i] >= V || pos[res[i]] != -1) {
      return 1;
    }
    pos[res[i]] = i;
  }

  for (int u = 0; u < V; ++u) {
    for (int v : adj[u]) {
      if (pos[u] >= pos[v]) {
        return 1;
      }
    }
  }

  return 0;
}