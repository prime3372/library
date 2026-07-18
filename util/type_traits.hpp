#pragma once

#include <type_traits>

namespace cp {

template <class> struct is_modint : std::false_type {};
template <class T>
inline constexpr bool is_modint_v = is_modint<T>::value;

template <class> struct is_static_modint : std::false_type {};
template <class T>
inline constexpr bool is_static_modint_v = is_static_modint<T>::value;

template <class> struct is_dynamic_modint : std::false_type {};
template <class T>
inline constexpr bool is_dynamic_modint_v = is_dynamic_modint<T>::value;

} // namespace cp