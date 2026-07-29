#pragma once

#include <type_traits>
#include <utility>
#include <vector>

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

template <class T>
struct is_pair : std::false_type {};

template <class T, class U>
struct is_pair<std::pair<T, U>> : std::true_type {};

template <class T>
constexpr bool is_pair_v = is_pair<T>::value;

template <class T>
struct is_vector : std::false_type {};

template <class T, class Alloc>
struct is_vector<std::vector<T, Alloc>> : std::true_type {};

template <class T>
constexpr bool is_vector_v = is_vector<T>::value;

} // namespace cp