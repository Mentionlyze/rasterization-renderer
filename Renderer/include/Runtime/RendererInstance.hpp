#pragma once

#include "FrameBuffer.hpp"
#include <cstdint>
#include <vector>
namespace Rasterization {

struct Viewport {
  int32_t x, y;
  int32_t w, h;

  Viewport() = default;
  Viewport(int32_t width, int32_t height) {
    x = 0;
    y = 0;
    w = width;
    h = height;
  }
};

class RendererInstance {
public:
  RendererInstance();
  virtual ~RendererInstance() = default;

  void Init(const int32_t width, const int32_t height);
  void SetViewport(const int32_t width, const int32_t height);
  void Clear(const Color &color);
  void ClearDepth(const float depth);
  Ref<FrameBuffer> GetFrameBuffer() { return m_FrameBuffer; }
  Viewport GetViewport() { return m_Viewport; }

  virtual void DrawArrays() {}

  virtual void DrawElements() {}

  virtual void DrawLine(const std::vector<Vec2> &points) {}

protected:
  Viewport m_Viewport;
  Ref<FrameBuffer> m_FrameBuffer;
};
} // namespace Rasterization