#pragma once

#include <vector>

namespace cp {

template <class T> struct simple_queue {
public:
  simple_queue() {}
  
  void reserve(int n) { payload.reserve(n); }
  
  int size() const { return int(payload.size()) - pos; }
  bool empty() const { return pos == int(payload.size()); }
  
  void push(const T& t) { payload.push_back(t); }
  
  T& front() {
    assert(!empty());
    return payload[pos];
  }
  const T& front() const {
    assert(!empty());
    return payload[pos];
  }
  
  void clear() {
    payload.clear();
    pos = 0;
  }
  
  void pop() {
    assert(!empty());
    pos++;
  }

private:
  std::vector<T> payload;
  int pos = 0;
};

}  // namespace cp