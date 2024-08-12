#include "Platform/CPU_Renderer.hpp"
#include "Core/Bresenham.hpp"
#include "Core/Scanline.hpp"
#include <cmath>

namespace Rasterization {
CPU_Renderer::CPU_Renderer() {}

void CPU_Renderer::DrawArrays(const std::vector<Vertex> &vertices,
                              const Mat4 &model) {
  auto len = vertices.size() / 3;
  for (uint32_t i = 0; i < len; i++) {
    Vertex result[3] = {vertices[i * 3], vertices[i * 3 + 1],
                        vertices[i * 3 + 2]};

    RasterizeTriangle(result, model);
  }
}

void CPU_Renderer::DrawElements(const std::vector<Vertex> &vertices,
                                const std::initializer_list<int32_t> &indices,
                                const Mat4 &model) {
  std::vector<Vertex> result;

  auto it = indices.begin();
  while (it != indices.end()) {
    result.push_back(vertices[*it]);
    it++;
  }

  DrawArrays(result, model);
}

void CPU_Renderer::RasterizeTriangle(Vertex (&vertices)[3], const Mat4 &model) {
  for (uint32_t i = 0; i < 3; i++) {
    // mvp transform
    auto mvp = m_Camera->GetPerspective() * m_Camera->GetViewMat() * model;
    vertices[i].position = mvp * vertices[i].position;

    // perspective transfrom
    vertices[i].position = 1 / vertices[i].position.w * vertices[i].position;

    // viewport transform
    vertices[i].position.x =
        (vertices[i].position.x + 1.0f) * 0.5f * (m_Viewport.w - 1.0f) +
        m_Viewport.x;

    vertices[i].position.y =
        m_Viewport.h -
        (vertices[i].position.y + 1.0f) * 0.5f * (m_Viewport.h - 1.0f) +
        m_Viewport.y;
  }
  auto [trap_1, trap_2] = Trapezoid::FromTriangle(vertices);
  if (trap_1) {
    DrawTrapezoid(trap_1.value());
  }

  if (trap_2) {
    DrawTrapezoid(trap_2.value());
  }
}

void CPU_Renderer::DrawTrapezoid(const Trapezoid &trap) {
  auto top = (uint32_t)(std::max({std::ceil(trap.top), 0.0f}));
  auto bottom =
      (uint32_t)std::min({std::ceil(trap.bottom), (float)(m_Viewport.h)}) - 1;

  auto y = top;

  while (y <= bottom) {
    auto scanline = Scanline::FromTrapzoid(trap, y);
    DrawScanline(scanline);
    y++;
  }
}

void CPU_Renderer::DrawScanline(const Scanline &scanline) {
  auto t_Scanline = scanline;
  auto vertex = t_Scanline.vertex;
  auto y = t_Scanline.y;

  while (t_Scanline.width > 0.0f) {
    auto x = vertex.position.x;
    auto color = vertex.color;
    if (x >= 0.0f && x < (float)(m_Viewport.w - 1)) {
      m_FrameBuffer->SetColor((uint32_t)x, (uint32_t)y, color);
    }

    t_Scanline.width -= 1.0f;
    vertex.position += t_Scanline.step.position;
    vertex.color += t_Scanline.step.color;
  }
}

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