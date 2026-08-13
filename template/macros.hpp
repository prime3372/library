#pragma once

#define rep(i, a, b)   for (int i = (a); i < int(b); i++)
#define REP(i, a, b)   for (int i = (a); i <= int(b); i++)
#define rrep(i, a, b)  for (int i = int(b) - 1; i >= (a); i--)
#define RREP(i, a, b)  for (int i = int(b); i >= (a); i--)
#define fore(x, a)     for (auto& x : (a))
#define all(a)         (a).begin(), (a).end()

#ifdef LOCAL

#define debug(...) \
  []<class... Args>(Args... args) -> void { \
    (std::cerr << ... << args); \
    std::cerr << "\n"; \
  }(__VA_ARGS__)

#else

#define debug(...)

#endif