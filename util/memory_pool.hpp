#pragma once

#include <cassert>
#include <memory>
#include <new>
#include <utility>
#include <vector>

namespace cp {

template <class T> class memory_pool {
 public:
  T* malloc() {
    if (!free_list.empty()) {
      T* ptr = free_list.back();
      free_list.pop_back();
      return ptr;
    }
    if (chunk_pos == chunk_size) {
      chunks.push_back((T*)(::operator new(chunk_size * sizeof(T))));
      chunk_pos = 0;
    }
    return reinterpret_cast<T*>(chunks.back() + (chunk_pos++));
  }

  void free(T* x) {
    if (x) free_list.push_back(x);
  }

 private:
  static constexpr int chunk_size = 1 << 12;
  inline static std::vector<T*> chunks;
  inline static std::vector<T*> free_list;
  inline static int chunk_pos = chunk_size;
};

}  // namespace cp