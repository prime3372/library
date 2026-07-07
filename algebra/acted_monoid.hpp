#pragma once

#include <type_traits>
#include <concepts>

#include "algebra/monoid.hpp"

namespace cp {

template <class M>
concept acted_monoid = monoid<M> && requires { typename M::F; }
&& std::is_default_constructible_v<typename M::S>
&& std::is_copy_constructible_v<typename M::S>
&& std::is_copy_assignable_v<typename M::S>
&& requires (typename M::S x, typename M::F f, typename M::F g) {
  {M::mapping(f, x)} -> std::same_as<typename M::S>;
  {M::composition(g, f)} -> std::same_as<typename M::F>;
  {M::id()} -> std::same_as<typename M::F>;
};

} // namespace cp