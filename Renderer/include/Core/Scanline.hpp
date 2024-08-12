#pragma once

#include "Vertex.hpp"
#include <algorithm>
#include <array>
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
            const Edge &right)
      : top(top), bottom(bottom), left(left), right(right) {}
  ~Trapezoid() = default;

  // clang-format off
  std::tuple<std::optional<Trapezoid>, std::optional<Trapezoid>> const 
  static FromTriangle(const Vertex (&vertices)[3]) {

    // clang-format on
    std::array<Vertex, 3> t_Vertices = {vertices[0], vertices[1], vertices[2]};

    if (t_Vertices[0].position.x == t_Vertices[1].position.x ==
            t_Vertices[2].position.x ||
        t_Vertices[0].position.y == t_Vertices[1].position.y ==
            t_Vertices[2].position.y) {
      return {std::nullopt, std::nullopt};
    }

    std::sort(t_Vertices.begin(), t_Vertices.end(),
              [](const Vertex &prev, const Vertex &next) {
                return prev.position.y < next.position.y;
              });

    if (t_Vertices[0].position.y == t_Vertices[1].position.y) {
      if (t_Vertices[0].position.x > t_Vertices[1].position.x) {
        std::array<Vertex, 3> result = {t_Vertices[1], t_Vertices[0],
                                        t_Vertices[2]};
        t_Vertices.swap(result);
      }

      auto trap = Trapezoid{t_Vertices[0].position.y, t_Vertices[2].position.y,
                            Edge{t_Vertices[0], t_Vertices[2]},
                            Edge{t_Vertices[1], t_Vertices[2]}};

      return {std::make_optional(trap), std::nullopt};
    }

    if (t_Vertices[1].position.y == t_Vertices[2].position.y) {
      if (t_Vertices[1].position.x > t_Vertices[2].position.x) {
        std::array<Vertex, 3> result = {t_Vertices[0], t_Vertices[2],
                                        t_Vertices[1]};
        t_Vertices.swap(result);
      }
      auto trap = Trapezoid{t_Vertices[0].position.y, t_Vertices[2].position.y,
                            Edge{t_Vertices[0], t_Vertices[1]},
                            Edge{t_Vertices[0], t_Vertices[2]}};

      return {std::make_optional(trap), std::nullopt};
    }

    auto x = t_Vertices[0].position.x +
             (t_Vertices[2].position.x - t_Vertices[0].position.x) *
                 (t_Vertices[1].position.y - t_Vertices[0].position.y) /
                 (t_Vertices[2].position.y - t_Vertices[0].position.y);

    if (x > t_Vertices[1].position.x) {
      auto trap_1 =
          Trapezoid{t_Vertices[0].position.y, t_Vertices[1].position.y,
                    Edge{t_Vertices[0], t_Vertices[1]},
                    Edge{t_Vertices[0], t_Vertices[2]}};

      auto trap_2 =
          Trapezoid{t_Vertices[1].position.y, t_Vertices[2].position.y,
                    Edge{t_Vertices[1], t_Vertices[2]},
                    Edge{t_Vertices[0], t_Vertices[2]}};

      return {std::make_optional(trap_1), std::make_optional(trap_2)};
    } else {
      auto trap_1 =
          Trapezoid{t_Vertices[0].position.y, t_Vertices[1].position.y,
                    Edge{t_Vertices[0], t_Vertices[2]},
                    Edge{t_Vertices[0], t_Vertices[1]}};

      auto trap_2 =
          Trapezoid{t_Vertices[1].position.y, t_Vertices[2].position.y,
                    Edge{t_Vertices[0], t_Vertices[2]},
                    Edge{t_Vertices[1], t_Vertices[2]}};

      return {std::make_optional(trap_1), std::make_optional(trap_2)};
    }
  }
};

class Scanline {
public:
  Vertex vertex, step;
  float width, y;

  Scanline(const Vertex &vertex, const Vertex &step, const float init_Y,
           const float width)
      : vertex(vertex), step(step), y(init_Y), width(width) {}
  ~Scanline() = default;

  static Scanline FromTrapzoid(const Trapezoid &trap, const float init_Y) {
    auto t1 = (init_Y - trap.left.v1.position.y) /
              (trap.left.v2.position.y - trap.left.v1.position.y);
    auto t2 = (init_Y - trap.right.v1.position.y) /
              (trap.right.v2.position.y - trap.right.v1.position.y);

    auto vertex_Left = Vertex::LerpVertex(trap.left.v1, trap.left.v2, t1);
    auto vertex_Right = Vertex::LerpVertex(trap.right.v1, trap.right.v2, t2);

    auto width = vertex_Right.position.x - vertex_Left.position.x;
    auto rh_Width = 1.0f / width;

    auto step = Vertex::InterpVertex(vertex_Left, vertex_Right, rh_Width);

    return Scanline{vertex_Left, step, init_Y, width};
  };
};
} // namespace Rasterization