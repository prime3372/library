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
    if (free_head) {
      slot* ptr = free_head;
      free_head = ptr->next;
      return reinterpret_cast<T*>(ptr);
    }
    if (chunk_pos == chunk_size) {
      chunks.push_back((slot*)(::operator new(chunk_size * sizeof(slot))));
      chunk_pos = 0;
    }
    return reinterpret_cast<T*>(chunks.back() + (chunk_pos++));
  }

  void free(T* x) {
    slot* ptr = reinterpret_cast<slot*>(x);
    ptr->next = free_head;
    free_head = ptr;
  }

 private:
  union slot {
    char data[sizeof(T)];
    slot* next;
  };
  static constexpr int chunk_size = 1 << 12;

  inline static std::vector<slot*> chunks;
  inline static slot* free_head = nullptr;
  inline static int chunk_pos = chunk_size;
};

}  // namespace cp