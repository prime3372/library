#pragma once

#include <concepts>
#include <type_traits>

namespace cp {

namespace internal {

template <class M>
concept monoid = requires { typename M::S; }
&& std::is_default_constructible_v<typename M::S>
&& std::is_copy_constructible_v<typename M::S>
&& std::is_copy_assignable_v<typename M::S>
&& requires (typename M::S x, typename M::S y) {
  {M::op(x, y)} -> std::same_as<typename M::S>;
  {M::e()} -> std::same_as<typename M::S>;
};

template <class M>
concept acted_monoid = monoid<M> && requires { typename M::F; }
&& std::is_default_constructible_v<typename M::F>
&& std::is_copy_constructible_v<typename M::F>
&& std::is_copy_assignable_v<typename M::F>
&& requires (typename M::S x, typename M::F f, typename M::F g) {
  {M::mapping(f, x)} -> std::same_as<typename M::S>;
  {M::composition(g, f)} -> std::same_as<typename M::F>;
  {M::id()} -> std::same_as<typename M::F>;
};

template <class R>
concept semiring = requires { typename R::S; }
&& std::is_default_constructible_v<typename R::S>
&& std::is_copy_constructible_v<typename R::S>
&& std::is_copy_assignable_v<typename R::S>
&& requires(typename R::S x, typename R::S y) {
  {R::add(x, y)} -> std::same_as<typename R::S>;
  {R::mul(x, y)} -> std::same_as<typename R::S>;
  {R::zero()} -> std::same_as<typename R::S>;
  {R::one()} -> std::same_as<typename R::S>;
};

} // namespace internal

} // namespace cp