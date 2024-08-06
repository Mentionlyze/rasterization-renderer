#include "Triangle.hpp"
#include "Runtime/Renderer.hpp"

Triangle::Triangle() : Layer("Triangle") {}

void Triangle::OnUpdate() {
  Rasterization::Renderer::Clear({2.0f, 5.0f, 0.0f, 1.0f});
}