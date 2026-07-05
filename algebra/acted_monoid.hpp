#pragma once

#include <concepts>

#include "algebra/monoid.hpp"

namespace cp {

template <class M>
concept acted_monoid = monoid<M> && requires {
  typename M::F;
} && requires (typename M::S x, typename M::F f, typename M::F g) {
  {M::mapping(f, x)} -> std::same_as<typename M::S>;
  {M::composition(g, f)} -> std::same_as<typename M::F>;
  {M::id()} -> std::same_as<typename M::F>;
};

} // namespace cp