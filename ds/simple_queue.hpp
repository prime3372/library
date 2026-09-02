#pragma once

#include <vector>

namespace cp {

template <class T> class simple_queue {
 public:
  simple_queue() {}
  void push(const T& x) { payload.push_back(x); }
  void pop() {
    assert(!empty());
    pos++;
  }
  T& front() {
    assert(!empty());
    return payload[pos];
  }
  const T& front() const {
    assert(!empty());
    return payload[pos];
  }
  int size() const { return int(payload.size()) - pos; }
  bool empty() const { return pos == int(payload.size()); }
  void reserve(int n) { payload.reserve(n); }
  void clear() {
    payload.clear();
    pos = 0;
  }

 private:
  std::vector<T> payload;
  int pos = 0;
};

}  // namespace cp