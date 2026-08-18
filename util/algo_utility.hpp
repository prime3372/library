#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>

namespace cp {

template <class T> bool chmin(T& a, const T& b) {
  return b < a ? (a = b, true) : false;
}

template <class T> bool chmax(T& a, const T& b) {
  return b > a ? (a = b, true) : false;
}

template <class Container> void uniq(Container& a) {
  std::sort(a.begin(), a.end());
  a.erase(std::unique(a.begin(), a.end()), a.end());
}

template <class Container, class Comp>
std::vector<int> sort(Container& a, Comp comp) {
  std::vector<int> p(int(a.size()));
  std::iota(p.begin(), p.end(), 0);
  std::sort(p.begin(), p.end(), [&](int i, int j) { return comp(a[i], a[j]); });
  auto tmp = a;
  for (int i = 0; i < int(a.size()); i++) a[i] = std::move(tmp[p[i]]);
  return p;
}

template <class Container> std::vector<int> sort(Container& a) {
  return sort(a, std::less<std::decay_t<decltype(a[0])>>());
}

template <class... Containers, class Comp>
std::vector<int> zip_sort(std::tuple<Containers&...> t, Comp comp) {
  return std::apply(
      [&](auto&... containers) {
        int n = int(std::get<0>(t).size());
        assert(((int(containers.size()) == n) && ...));

        std::vector<int> p(n);
        std::iota(p.begin(), p.end(), 0);
        std::sort(p.begin(), p.end(), [&](int i, int j) {
          return comp(std::tie(containers[i]...), std::tie(containers[j]...));
        });

        (
            [&](auto& container) {
              auto tmp = container;
              for (int i = 0; i < n; i++) {
                container[i] = std::move(tmp[p[i]]);
              }
            }(containers),
            ...);

        return p;
      },
      t);
}

template <class... Containers>
std::vector<int> zip_sort(std::tuple<Containers&...> t) {
  return std::apply(
      [&](auto&... containers) {
        auto comp = std::less<decltype(std::make_tuple(containers[0]...))>();
        return zip_sort(t, comp);
      },
      t);
}

}  // namespace cp