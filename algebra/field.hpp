#pragma once

#include <concepts>
#include "ring.hpp"

template <class K>
concept field = ring<K> && requires(typename K::S x) {
  {K::recip(x)} -> std::same_as<typename K::S>;
};
