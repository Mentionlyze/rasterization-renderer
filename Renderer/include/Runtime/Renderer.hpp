#pragma once

#include "RendererInstance.hpp"
#include <cstdint>

namespace Rasterization {
class Renderer {
public:
  inline static void Init(const uint32_t width, const uint32_t height) {
    s_RendererInstance->Init(width, height);
  }
  inline static void SetViewport(const uint32_t width, const uint32_t height) {
    s_RendererInstance->SetViewport(width, height);
  }
  inline static void Clear(const Color &color) {
    s_RendererInstance->Clear(color);
  }
  inline static void ClearDepth(const float depth) {
    s_RendererInstance->ClearDepth(depth);
  }
  inline static void BeginScene() {}
  inline static void EndScene() {}
  inline static void Submit() {}

  static Ref<FrameBuffer> GetFrameBuffer() {
    return s_RendererInstance->GetFrameBuffer();
  }

private:
  static RendererInstance *s_RendererInstance;
};
} // namespace Rasterization