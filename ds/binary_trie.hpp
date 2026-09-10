#pragma once

#include <bitset>
#include <limits>
#include <string>

#include "string/trie.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class T> requires(internal::is_unsigned_int_v<T>)
class binary_trie : public trie<2, '0'> {
  using base = trie<2, '0'>;

 public:
  using base::trie;
  int insert(T x) { return base::insert(std::bitset<bit>(x).to_string()); }
  bool erase(T x) { return base::erase(std::bitset<bit>(x).to_string()); }
  int count(T x) { return base::count(std::bitset<bit>(x).to_string()); }
  int count_prefix(T x) {
    return base::count_prefix(std::bitset<bit>(x).to_string());
  }

 private:
  static constexpr int bit = std::numeric_limits<T>::digits;
};

}  // namespace cp