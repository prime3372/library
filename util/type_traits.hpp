#pragma once

#include <array>
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace cp {

namespace internal {

// is_int128

template <class T> using is_signed_int128 = std::is_same<T, __int128>;

template <class T>
inline constexpr bool is_signed_int128_v = is_signed_int128<T>::value;

template <class T>
using is_unsigned_int128 = std::is_same<T, unsigned __int128>;

template <class T>
inline constexpr bool is_unsigned_int128_v = is_unsigned_int128<T>::value;

template <class T>
using is_int128 =
    std::conditional_t<is_signed_int128_v<T> || is_unsigned_int128_v<T>,
                       std::true_type, std::false_type>;

template <class T> inline constexpr bool is_int128_v = is_int128<T>::value;

// is_integral

template <class T>
using is_signed_int =
    std::conditional_t<(std::is_integral_v<T> && std::is_signed_v<T>) ||
                           is_signed_int128_v<std::remove_cv_t<T>>,
                       std::true_type, std::false_type>;

template <class T>
inline constexpr bool is_signed_int_v = is_signed_int<T>::value;

template <class T>
using is_unsigned_int =
    std::conditional_t<(std::is_integral_v<T> && std::is_unsigned_v<T>) ||
                           is_unsigned_int128_v<std::remove_cv_t<T>>,
                       std::true_type, std::false_type>;

template <class T>
inline constexpr bool is_unsigned_int_v = is_unsigned_int<T>::value;

template <class T>
using is_integral = std::conditional_t<std::is_integral_v<T> ||
                                           is_int128_v<std::remove_cv_t<T>>,
                                       std::true_type, std::false_type>;

template <class T> inline constexpr bool is_integral_v = is_integral<T>::value;

// is_modint

template <class> struct is_modint : public std::false_type {};

template <class T> inline constexpr bool is_modint_v = is_modint<T>::value;

template <class> struct is_static_modint : public std::false_type {};

template <class T>
inline constexpr bool is_static_modint_v = is_static_modint<T>::value;

template <class> struct is_dynamic_modint : public std::false_type {};

template <class T>
inline constexpr bool is_dynamic_modint_v = is_dynamic_modint<T>::value;

}  // namespace internal

}  // namespace cp