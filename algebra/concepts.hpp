#pragma once

#include <concepts>

template <class M>
concept monoid = requires {
  typename M::S;
} && requires(typename M::S x, typename M::S y) {
  {M::op(x, y)} -> std::same_as<typename M::S>;
  {M::e()} -> std::same_as<typename M::S>;
};

template <class G>
concept group = monoid<G> && requires(typename G::S x) {
  {G::inv(x)} -> std::same_as<typename G::S>;
};

template <class M>
concept acted_monoid = monoid<M> && requires {
  typename M::F;
} && requires (typename M::S x, typename M::F f, typename M::F g) {
  {M::mapping(f, x)} -> std::same_as<typename M::S>;
  {M::composition(g, f)} -> std::same_as<typename M::F>;
  {M::id()} -> std::same_as<typename M::F>;
};

template <class R>
concept semiring = requires {
  typename R::S;
} && requires(typename R::S x, typename R::S y) {
  {R::add(x, y)} -> std::same_as<typename R::S>;
  {R::mul(x, y)} -> std::same_as<typename R::S>;
  {R::zero()} -> std::same_as<typename R::S>;
  {R::one()} -> std::same_as<typename R::S>;
};

template <class R>
concept ring = semiring<R> && requires(typename R::S x) {
  {R::minus(x)} -> std::same_as<typename R::S>;
};

template <class K>
concept field = ring<K> && requires(typename K::S x) {
  {K::recip(x)} -> std::same_as<typename K::S>;
};
