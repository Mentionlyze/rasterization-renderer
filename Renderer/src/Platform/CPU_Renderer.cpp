#include "Platform/CPU_Renderer.hpp"
#include "Core/Bresenham.hpp"

namespace Rasterization {
CPU_Renderer::CPU_Renderer() {}

void CPU_Renderer::DrawArrays() {}

void CPU_Renderer::DrawElements() {}

void CPU_Renderer::DrawLine(const std::vector<Vec2> &points) {
  auto len = points.size() / 2;
  auto rect_min = Vec2{(float)m_Viewport.x, (float)m_Viewport.y};
  auto rect_max = Vec2{(float)m_Viewport.w, (float)m_Viewport.h};
  for (uint32_t i = 0; i < len; i++) {
    auto p1 = points[i * 2];
    auto p2 = points[i * 2 + 1];

    auto bresenham = Bresenham{p1, p2, rect_min, rect_max};
    bresenham.IteratorCallback([&](int32_t x, int32_t y) {
      m_FrameBuffer->SetColor(x, y, {0.2f, 1.0f, 0.0f, 1.0f});
    });
  }
}
} // namespace Rasterization