#pragma once

#include <type_traits>
#include "Add.hpp"
#include "concepts.hpp"
#include "Range.hpp"
#include "../util/type_traits.hpp"

template <class T>
  requires std::is_arithmetic_v<T> || is_modint_v<T>
using Sum = Range<Add<T>>;
