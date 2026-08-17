#pragma once

#include <bitset>
#include <limits>
#include <string>

#include "string/trie_tree.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class T> requires internal::is_unsigned_int_v<T>
class binary_trie : public trie_tree<2, '0'> {
 public:
  using base = trie_tree<2, '0'>;
  using base::trie_tree;

  int insert(T x) {
    return base::insert(std::bitset<bit>(x).to_string());
  }
  bool erase(T x) {
    return base::erase(std::bitset<bit>(x).to_string());    
  }
  int count(T x) {
    return base::count(std::bitset<bit>(x).to_string());
  }
  int prefix(T x) {
    return base::prefix(std::bitset<bit>(x).to_string());
  }

 private:
  static constexpr int bit = std::numeric_limits<T>::digits;
};

} // namespace cp