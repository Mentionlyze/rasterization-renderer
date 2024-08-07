#pragma once

#include "Math.hpp"
#include <optional>
#include <tuple>

namespace Rasterization {
enum OUTCODE {
  INSIDE = 1 >> 1,
  LEFT = 1,
  RIGHT = 1 << 1,
  BOTTOM = 1 << 2,
  TOP = 1 << 3
};

inline int const ComputeOutCode(const Vec2 &point, const Vec2 &rect_min,
                                const Vec2 &rect_max) {
  auto outcode = 0;

  if (point.x < rect_min.x) {
    outcode |= OUTCODE::LEFT;
  } else if (point.x > rect_max.x) {
    outcode |= OUTCODE::RIGHT;
  }

  if (point.y < rect_min.y) {
    outcode |= OUTCODE::BOTTOM;
  } else if (point.y > rect_max.y) {
    outcode |= OUTCODE::TOP;
  }

  return outcode;
}

std::optional<std::tuple<Vec2, Vec2>> const inline CohenSutherlandLineClip(
    Vec2 &point_1, Vec2 &point_2, const Vec2 &rect_min, const Vec2 &rect_max) {
  auto outcode_1 = ComputeOutCode(point_1, rect_min, rect_max);
  auto outcode_2 = ComputeOutCode(point_2, rect_min, rect_max);

  while (true) {
    if (!(outcode_1 | outcode_2)) {
      return std::make_optional(std::make_tuple(point_1, point_2));
    } else if (outcode_1 & outcode_2) {
      return std::nullopt;
    } else {
      auto outcode = outcode_2 > outcode_1 ? outcode_2 : outcode_1;
      auto p = Vec2{0.0f};

      if (outcode & OUTCODE::TOP) {
        p.x = point_1.x + (point_2.x - point_1.x) * (rect_max.y - point_1.y) /
                              (point_2.y - point_1.y);
        p.y = rect_max.y;
      } else if (outcode & OUTCODE::BOTTOM) {
        p.x = point_1.x + (point_2.x - point_1.x) * (rect_min.y - point_1.y) /
                              (point_2.y - point_1.y);
        p.y = rect_min.y;
      }

      if (outcode & OUTCODE::RIGHT) {
        p.y = point_1.y + (point_2.y - point_1.y) * (rect_max.x - point_1.x) /
                              (point_2.x - point_1.x);
        p.x = rect_max.x;
      } else if (outcode & OUTCODE::LEFT) {
        p.y = point_1.y + (point_2.y - point_1.y) * (rect_min.x - point_1.x) /
                              (point_2.x - point_1.x);
        p.x = rect_min.x;
      }

      if (outcode == outcode_1) {
        point_1 = p;
        outcode_1 = ComputeOutCode(point_1, rect_min, rect_max);
      } else {
        point_2 = p;
        outcode_2 = ComputeOutCode(point_2, rect_min, rect_max);
      }
    }
  }
}
} // namespace Rasterization