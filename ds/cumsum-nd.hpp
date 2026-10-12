#pragma once

#include <array>
#include <cassert>
#include <vector>

namespace cp {

template <class T, int dim> class cumsum_nd {
 public:
  cumsum_nd() {}
  explicit cumsum_nd(const std::array<int, dim>& sh) : shape(sh) {
    for (int i = 0; i < dim; i++) assert(0 <= shape[i]);
    int size = 1;
    for (int i = dim - 1; i >= 0; i--) {
      stride[i] = size;
      size *= (shape[i] + 1);
    }
    data.resize(size);
  }

  void accumulate() {
    for (int i = 0; i < dim; i++) {
      for (int j = 0; j < int(data.size()); j++) {
        int pos = (j / stride[i]) % (shape[i] + 1);
        if (pos > 0) data[j] += data[j - stride[i]];
      }
    }
    accumulated = true;
  }

  void add(const std::array<int, dim>& p, T w) {
    for (int i = 0; i < dim; i++) assert(0 <= p[i] && p[i] < shape[i]);
    int idx = 0;
    for (int i = 0; i < dim; i++) idx += (p[i] + 1) * stride[i];
    data[idx] += w;
  }

  T sum(const std::array<int, dim>& l, const std::array<int, dim>& r) const {
    assert(accumulated);
    for (int i = 0; i < dim; i++) {
      assert(0 <= l[i] && l[i] <= r[i] && r[i] <= shape[i]);
    }
    T res = 0;
    for (int mask = 0; mask < (1 << dim); mask++) {
      int idx = 0;
      int sign = 1;
      for (int i = 0; i < dim; i++) {
        if ((mask >> i) & 1) {
          idx += l[i] * stride[i];
          sign = -sign;
        } else {
          idx += r[i] * stride[i];
        }
      }
      res += sign * data[idx];
    }
    return res;
  }

  void imos_add(const std::array<int, dim>& l, const std::array<int, dim>& r,
                T w) {
    for (int i = 0; i < dim; i++) {
      assert(0 <= l[i] && l[i] <= r[i] && r[i] <= shape[i]);
    }
    for (int mask = 0; mask < (1 << dim); mask++) {
      int idx = 0;
      int sign = 1;
      for (int i = 0; i < dim; i++) {
        if ((mask >> i) & 1) {
          idx += r[i] * stride[i];
          sign = -sign;
        } else {
          idx += l[i] * stride[i];
        }
      }
      data[idx] += sign * w;
    }
  }

  T imos_get(const std::array<int, dim>& p) const {
    assert(accumulated);
    for (int i = 0; i < dim; i++) assert(0 <= p[i] && p[i] < shape[i]);
    int idx = 0;
    for (int i = 0; i < dim; i++) idx += p[i] * stride[i];
    return data[idx];
  }

 private:
  std::array<int, dim> shape;
  std::array<int, dim> stride;
  std::vector<T> data;
  bool accumulated = false;
};

}  // namespace cp