#pragma once

#include "FrameBuffer.hpp"
#include <cstdint>
namespace Rasterization {
class RendererInstance {
public:
  RendererInstance();
  virtual ~RendererInstance() = default;

  void Init(const int32_t width, const int32_t height);
  void SetViewport(const uint32_t width, const uint32_t height);
  void Clear(const Color &color);
  void ClearDepth(const float depth);
  Ref<FrameBuffer> GetFrameBuffer() { return m_FrameBuffer; }

protected:
  Ref<FrameBuffer> m_FrameBuffer;
};
} // namespace Rasterization