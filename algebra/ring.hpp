#pragma once

#include <concepts>

#include "semiring.hpp"

namespace cp {

template <class R>
concept ring = semiring<R> && requires(typename R::S x) {
  {R::minus(x)} -> std::same_as<typename R::S>;
};

} // namespace cp