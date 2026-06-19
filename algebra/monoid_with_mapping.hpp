#pragma once

#include <concepts>
#include "monoid.hpp"

template <class M>
concept monoid_with_mapping = monoid<M> && requires {
  typename M::F;
} && requires (typename M::S x, typename M::F f, typename M::F g) {
  {M::mapping(f, x)} -> std::same_as<typename M::S>;
};
