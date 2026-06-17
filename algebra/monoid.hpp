#pragma once

#include <concepts>

template <class M>
concept monoid = requires {
  typename M::S;
} && requires(typename M::S x, typename M::S y) {
  {M::op(x, y)} -> std::same_as<typename M::S>;
  {M::e()} -> std::same_as<typename M::S>;
};
