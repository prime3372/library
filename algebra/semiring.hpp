#pragma once

#include <type_traits>
#include <concepts>

namespace cp {

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

} // namespace cp