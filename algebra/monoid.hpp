#pragma once

#include <concepts>
#include <type_traits>

namespace cp {

template <class M>
concept monoid = requires { typename M::S; }
&& std::is_default_constructible_v<typename M::S>
&& std::is_copy_constructible_v<typename M::S>
&& std::is_copy_assignable_v<typename M::S>
&& requires(typename M::S x, typename M::S y) {
  {M::op(x, y)} -> std::same_as<typename M::S>;
  {M::e()} -> std::same_as<typename M::S>;
};

} // namespace cp