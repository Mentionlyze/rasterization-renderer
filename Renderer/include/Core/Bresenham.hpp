#pragma once

#include "Math.hpp"
#include <functional>

namespace Rasterization {

class Bresenham {
public:
    Bresenham(Vec2 &point_1, Vec2 &point_2, const Vec2 &rect_min,
              const Vec2 &rect_max);

    ~Bresenham() {}

    void IteratorCallback(std::function<void(int32_t x, int32_t y)> callback);

private:
    int32_t x, y, dx, e, step, desc, final_X, steep, x_Step, y_Step;
};
}  // namespace Rasterization