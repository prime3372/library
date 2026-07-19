#pragma once

#include <bitset>
#include <limits>
#include <type_traits>
#include <string>

#include "string/trie_tree.hpp"

namespace cp {

template <class T> requires (std::is_unsigned_v<T>)
class binary_trie : public trie_tree<2, '0'> {
public:
  using trie_tree<2, '0'>::trie_tree;

  int insert(T x) {
    return trie_tree<2, '0'>::insert(std::bitset<bit>(x).to_string());
  }

  bool erase(T x) {
    return trie_tree<2, '0'>::erase(std::bitset<bit>(x).to_string());    
  }

  int count(T x) {
    return trie_tree<2, '0'>::count(std::bitset<bit>(x).to_string());
  }

  int prefix(T x) {
    return trie_tree<2, '0'>::prefix(std::bitset<bit>(x).to_string());
  }

private:
  static constexpr int bit = std::numeric_limits<T>::digits;
};

} // namespace cp