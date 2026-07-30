#pragma once

#include <array>
#include <cstddef>
#include <type_traits>
#include <tuple>
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
struct is_tuple_like : std::false_type {};

template <class T, size_t Size>
struct is_tuple_like<std::array<T, Size>> : std::true_type {};

template <class... Args>
struct is_tuple_like<std::tuple<Args...>> : std::true_type {};

template <class T, class U>
struct is_tuple_like<std::pair<T, U>> : std::true_type {};

template <class T>
constexpr bool is_tuple_like_v = is_tuple_like<T>::value;

template <class T>
struct is_vector : std::false_type {};

template <class T, class Alloc>
struct is_vector<std::vector<T, Alloc>> : std::true_type {};

template <class T>
constexpr bool is_vector_v = is_vector<T>::value;

} // namespace cp