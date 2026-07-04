#pragma once

#include <concepts>

#include "monoid.hpp"

namespace cp {

template <class G>
concept group = monoid<G> && requires(typename G::S x) {
  {G::inv(x)} -> std::same_as<typename G::S>;
};

} // namespace cp