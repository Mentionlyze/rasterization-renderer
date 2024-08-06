#pragma once

#include "Math.hpp"
#include <functional>

namespace Rasterization {

class Bresenham {
public:
  Bresenham(Vec2 &p1, Vec2 &p2, const Vec2 &rect_min, const Vec2 &rect_max) {}
  ~Bresenham();

  void IteratorCallback(std::function<void(int32_t x, int32_t y)> callback) {}

private:
  int32_t final_X, x, y, step, desc, steep, e, x_Step, y_Step;
};
} // namespace Rasterization