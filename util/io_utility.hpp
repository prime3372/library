#pragma once

#include <algorithm>
#include <array>
#include <cctype>
#include <cstddef>
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <vector>

#include "util/type_traits.hpp"

namespace std {

// __int128

istream& operator>>(istream& is, __int128& val) {
  string s;
  if (is >> s) {
    val = 0;
    for (int i = s[0] == '+' || s[0] == '-'; i < int(s.size()); i++) {
      if (!isdigit(s[i])) break;
      val = val * 10 + (s[i] - '0');
    }
    if (s[0] == '-') val = -val;
  }
  return is;
}

istream& operator>>(istream& is, unsigned __int128& val) {
  string s;
  if (is >> s) {
    val = 0;
    for (int i = s[0] == '+' || s[0] == '-'; i < int(s.size()); i++) {
      if (!isdigit(s[i])) break;
      val = val * 10 + (s[i] - '0');
    }
    if (s[0] == '-') val = ~val + 1;
  }
  return is;
}

ostream& operator<<(ostream& os, __int128 val) {
  if (val == 0) return os << '0';
  unsigned __int128 uval = val;
  if (val < 0) {
    os << '-';
    uval = -val;
  }
  string s;
  while (uval) {
    s.push_back((char)('0' + (uval % 10)));
    uval /= 10;
  }
  reverse(s.begin(), s.end());
  return os << s;
}

ostream& operator<<(ostream& os, unsigned __int128 val) {
  if (val == 0) return os << '0';
  string s;
  while (val) {
    s.push_back((char)('0' + (val % 10)));
    val /= 10;
  }
  reverse(s.begin(), s.end());
  return os << s;
}

} // namespace std

namespace cp {

namespace internal {

template <class T> struct delimiter {
  static constexpr char value[] = " ";
};

template <class T>
inline constexpr auto delimiter_v = delimiter<T>::value;

template <class T, class Alloc>
struct delimiter<std::deque<T, Alloc>> {
  static constexpr char value[] = "\n";
};

template <class Key, class Val, class Comp, class Alloc>
struct delimiter<std::map<Key, Val, Comp, Alloc>> {
  static constexpr char value[] = "\n";
};

template <class T, class Container, class Comp>
struct delimiter<std::priority_queue<T, Container, Comp>> {
  static constexpr char value[] = "\n";
};

template <class T, class Container>
struct delimiter<std::queue<T, Container>> {
  static constexpr char value[] = "\n";
};

template <class T, class Comp, class Alloc>
struct delimiter<std::set<T, Comp, Alloc>> {
  static constexpr char value[] = "\n";
};

template <> struct delimiter<std::string> {
  static constexpr char value[] = "\n";
};

template <class Key, class Val, class Hash, class Equal, class Alloc>
struct delimiter<std::unordered_map<Key, Val, Hash, Equal, Alloc>> {
  static constexpr char value[] = "\n";
};

template <class T, class Hash, class Equal, class Alloc>
struct delimiter<std::unordered_set<T, Hash, Equal, Alloc>> {
  static constexpr char value[] = "\n";
};

template <class T, class Alloc>
struct delimiter<std::vector<T, Alloc>> {
  static constexpr char value[] = "\n";
};

} // namespace internal

} // namespace cp

namespace std {

// forward declarations

template <class T, class Alloc>
ostream& operator<<(ostream& os, const deque<T, Alloc>& dq);

template <class Key, class Val, class Comp, class Alloc>
ostream& operator<<(ostream& os, const map<Key, Val, Comp, Alloc>& mp);

template <class T, class Container, class Comp>
ostream& operator<<(ostream& os, priority_queue<T, Container, Comp> pq);

template <class T, class Container>
ostream& operator<<(ostream& os, queue<T, Container> que);

template <class T, class Comp, class Alloc>
ostream& operator<<(ostream& os, const set<T, Comp, Alloc>& s);

template <class Tuple> requires cp::internal::is_tuple_like_v<Tuple>
ostream& operator<<(ostream& os, const Tuple& t);

template <class Key, class Val, class Hash, class Equal, class Alloc>
ostream& operator<<(ostream& os, const unordered_map<Key, Val, Hash, Equal, Alloc>& mp);

template <class T, class Hash, class Equal, class Alloc>
ostream& operator<<(ostream& os, const unordered_set<T, Hash, Equal, Alloc>& s);

template <class T, class Alloc>
ostream& operator<<(ostream& os, const vector<T, Alloc>& v);

// deque

template <class T, class Alloc>
ostream& operator<<(ostream& os, const deque<T, Alloc>& dq) {
  for (int i = 0; i < int(dq.size()); i++) {
    os << dq[i];
    if (i != int(dq.size()) - 1) {
      os << cp::internal::delimiter_v<T>;
    }
  }
  return os;
}

// map

template <class Key, class Val, class Comp, class Alloc>
ostream& operator<<(ostream& os, const map<Key, Val, Comp, Alloc>& mp) {
  for (auto itr = mp.begin(); itr != mp.end(); itr++) {
    os << *itr;
    if (next(itr) != mp.end()) {
      os << cp::internal::delimiter_v<pair<Key, Val>>;
    }
  }
  return os;
}

// priority_queue

template <class T, class Container, class Comp>
ostream& operator<<(ostream& os, priority_queue<T, Container, Comp> pq) {
  while (!pq.empty()) {
    os << pq.top();
    pq.pop();
    if (!pq.empty()) {
      os << cp::internal::delimiter_v<T>;
    }
  }
  return os;
}

// queue

template <class T, class Container>
ostream& operator<<(ostream& os, queue<T, Container> que) {
  while (!que.empty()) {
    os << que.front();
    que.pop();
    if (!que.empty()) {
      os << cp::internal::delimiter_v<T>;
    }
  }
  return os;
}

// set

template <class T, class Comp, class Alloc>
ostream& operator<<(ostream& os, const set<T, Comp, Alloc>& s) {
  for (auto itr = s.begin(); itr != s.end(); itr++) {
    os << *itr;
    if (next(itr) != s.end()) {
      os << cp::internal::delimiter_v<T>;
    }
  }
  return os;
}

// tuple_like (array, pair, tuple)

template <class Tuple> requires cp::internal::is_tuple_like_v<Tuple>
ostream& operator<<(ostream& os, const Tuple& t) {
  static constexpr size_t n = tuple_size_v<Tuple>; 
  if constexpr (n == 0) return os;
  os << "(";
  [&]<size_t... I>(index_sequence<I...>) {
    ([&]<class T>(const T& x) {
      os << x << cp::internal::delimiter_v<T>;
    }(get<I>(t)), ...);
  }(make_index_sequence<n - 1>());
  os << get<n - 1>(t) << ")";
  return os;
}

// unordered_map

template <class Key, class Val, class Hash, class Equal, class Alloc>
ostream& operator<<(ostream& os, const unordered_map<Key, Val, Hash, Equal, Alloc>& mp) {
  for (auto itr = mp.begin(); itr != mp.end(); itr++) {
    os << *itr;
    if (next(itr) != mp.end()) {
      os << cp::internal::delimiter_v<pair<Key, Val>>;
    }
  }
  return os;
}

// unordered_set

template <class T, class Hash, class Equal, class Alloc>
ostream& operator<<(ostream& os, const unordered_set<T, Hash, Equal, Alloc>& s) {
  for (auto itr = s.begin(); itr != s.end(); itr++) {
    os << *itr;
    if (next(itr) != s.end()) {
      os << cp::internal::delimiter_v<T>;
    }
  }
  return os;
}

// vector

template <class T, class Alloc>
ostream& operator<<(ostream& os, const vector<T, Alloc>& v) {
  for (int i = 0; i < int(v.size()); i++) {
    os << v[i];
    if (i != int(v.size()) - 1) {
      os << cp::internal::delimiter_v<T>;
    }
  }
  return os;
}

} // namespace std