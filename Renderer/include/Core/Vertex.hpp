#pragma once

#include "Math.hpp"

namespace Rasterization {
struct Vertex {
  Vec4 position;
  Color color;
  Vec2 uv;
  Vec4 normal;

  Vertex() : position{Vec4{}}, color{Color{}}, uv{Vec2{}}, normal{Vec4{}} {};

  Vertex(const Vec3 &pos)
      : position{Vec4(pos, 1.0f)}, color{Color{}}, uv{Vec2{}},
        normal{Vec4{}} {};

  Vertex(const Vec4 &pos)
      : position{Vec4{pos}}, color{Color{}}, uv{Vec2{}}, normal{Vec4{}} {};

  Vertex(const Vec3 &pos, const Color &color)
      : position{Vec4{pos, 1.0f}}, color{color}, uv{Vec2{}}, normal{Vec4{}} {};

  Vertex(const Vec3 &pos, const Vec2 &uv, const Vec4 &normal)
      : position{Vec4{pos, 1.0f}}, color{Color{}}, uv{uv}, normal{normal} {};

  Vertex(const Vec3 &pos, const Color &color, const Vec2 &uv,
         const Vec4 &normal)
      : position{Vec4{pos, 1.0f}}, color{color}, uv{uv}, normal{normal} {};

  Vertex(const Vec4 &pos, const Color &color, const Vec2 &uv,
         const Vec4 &normal)
      : position{Vec4{pos}}, color{color}, uv{uv}, normal{normal} {};

  static Vertex LerpVertex(const Vertex &left, const Vertex &right,
                           const float t) {
    auto position = LerpVec(left.position, right.position, t);
    auto color = LerpVec(left.color, right.color, t);
    auto uv = LerpVec(left.uv, right.uv, t);
    auto normal = LerpVec(left.normal, right.normal, t);

    return Vertex{position, color, uv, normal};
  }

  static Vertex InterpVertex(const Vertex &left, const Vertex &right,
                             const float t) {
    auto position = (right.position - left.position) * t;
    auto color = (right.color - left.color) * t;
    auto uv = (right.uv - left.uv) * t;
    auto normal = (right.normal - left.normal) * t;

    return {position, color, uv, normal};
  }
};
} // namespace Rasterization