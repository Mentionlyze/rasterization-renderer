#pragma once

#include "CohenSutherland.hpp"
#include <functional>
#include <utility>

namespace Rasterization {

class Bresenham {
public:
  Bresenham(Vec2 &point_1, Vec2 &point_2, const Vec2 &rect_min,
            const Vec2 &rect_max) {
    auto result = CohenSutherlandLineClip(point_1, point_2, rect_min, rect_max);
    if (result) {
      auto [p1, p2] = result.value();
      auto x0 = (int32_t)p1.x;
      auto y0 = (int32_t)p1.y;
      auto x1 = (int32_t)p2.x;
      auto y1 = (int32_t)p2.y;

      auto dx = std::abs(x1 - x0);
      auto dy = std::abs(y1 - y0);

      x_Step = x1 >= x0 ? 1 : -1;
      y_Step = y1 >= y0 ? 1 : -1;
      x = x0;
      y = y0;

      steep = dx < dy ? 1 : -1;
      final_X = dx < dy ? y1 : x1;

      if (dx < dy) {
        std::swap(dx, dy);
        std::swap(x, y);
        std::swap(x_Step, y_Step);
      }

      e = -dx;
      step = 2 * dy;
      desc = -2 * dx;
    }
  }
  ~Bresenham() {}

  void IteratorCallback(std::function<void(int32_t x, int32_t y)> callback) {
    while (x != final_X) {
      if (steep > 0) {
        callback(y, x);
      } else {
        callback(x, y);
      }

      e += step;
      if (e > 0) {
        y += y_Step;
        e += desc;
      }

      x += x_Step;
    }
  }

private:
  int32_t x, y, dx, e, step, desc, final_X, steep, x_Step, y_Step;
};
} // namespace Rasterization