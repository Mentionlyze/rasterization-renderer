#pragma once

#include "Vertex.hpp"
#include <optional>
#include <tuple>

namespace Rasterization {
struct Edge {
    Vertex v1;
    Vertex v2;
};

class Trapezoid {
public:
    float top, bottom;
    Edge left, right;

    Trapezoid(const float top, const float bottom, const Edge &left,
              const Edge &right);

    ~Trapezoid() = default;

    // clang-format off
  std::tuple<std::optional<Trapezoid>, std::optional<Trapezoid>> const 
  static FromTriangle(const Vertex (&vertices)[3]);
};

class Scanline {
public:
  Vertex vertex, step;
  float width, y;

  Scanline(const Vertex &vertex, const Vertex &step, const float init_Y,
           const float width);
  ~Scanline() = default;

  static Scanline FromTrapzoid(const Trapezoid &trap, const float init_Y);
};
} // namespace Rasterization