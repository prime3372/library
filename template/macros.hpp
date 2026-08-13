#pragma once

#define rep(i, a, b)   for (int i = (a); i < int(b); i++)
#define REP(i, a, b)   for (int i = (a); i <= int(b); i++)
#define rrep(i, a, b)  for (int i = int(b) - 1; i >= (a); i--)
#define RREP(i, a, b)  for (int i = int(b); i >= (a); i--)
#define fore(x, a)     for (auto& x : (a))
#define all(a)         (a).begin(), (a).end()

#ifdef LOCAL

#define EMPTY
#define DEFER(m) m EMPTY

#define EVAL(...)  EVAL1(EVAL1(__VA_ARGS__))
#define EVAL1(...) EVAL2(EVAL2(__VA_ARGS__))
#define EVAL2(...) EVAL3(EVAL3(__VA_ARGS__))
#define EVAL3(...) EVAL4(EVAL4(__VA_ARGS__))
#define EVAL4(...) EVAL5(EVAL5(__VA_ARGS__))
#define EVAL5(...) EVAL6(EVAL6(__VA_ARGS__))
#define EVAL6(...) __VA_ARGS__

#define INVOKE_RECURSIVE_INDIRECT() INVOKE_RECURSIVE

#define INVOKE_RECURSIVE(macro, first, ...) \
  do { \
    macro(first); \
    __VA_OPT__(DEFER(INVOKE_RECURSIVE_INDIRECT)()(macro, __VA_ARGS__)); \
  } while (false)

#define INVOKE(macro, ...) EVAL(INVOKE_RECURSIVE(macro, __VA_ARGS__))

#define DEBUG(a) do { std::cerr << (a); } while (false)

#define debug(...) do { INVOKE(DEBUG, __VA_ARGS__); std::cerr << "\n"; } while (false)

#else

#define debug(...)

#endif