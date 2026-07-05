#pragma once

#include <concepts>

#include "algebra/ring.hpp"

namespace cp {

template <class K>
concept field = ring<K> && requires(typename K::S x) {
  {K::recip(x)} -> std::same_as<typename K::S>;
};

} // namespace cp