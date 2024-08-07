#include "Triangle.hpp"
#include "Runtime/Renderer.hpp"

Triangle::Triangle() : Layer("Triangle") {
  points = {
      Rasterization::Vec2{0.0f, 0.0f},
      Rasterization::Vec2{100.0f, 100.0f},
      Rasterization::Vec2{100.0f, 100.0f},
      Rasterization::Vec2{200.0f, 0.0f},
  };

  float va[8 * 24] = {};
}

void Triangle::OnUpdate() {
  Rasterization::Renderer::Clear({0.0f, 0.0f, 0.0f, 1.0f});
  Rasterization::Renderer::SubmitLine(points);
}