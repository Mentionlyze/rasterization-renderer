#include "Runtime/RendererInstance.hpp"

namespace Rasterization {

RendererInstance::RendererInstance() {}

void RendererInstance::Init(const int32_t width, const int32_t height) {
  m_FrameBuffer = CreateRef<FrameBuffer>(width, height);
}

void RendererInstance::SetViewport(const int32_t width, const int32_t height) {
  m_Viewport = Viewport{width, height};
}

void RendererInstance::Clear(const Color &color) {
  m_FrameBuffer->Clear(color);
}

void RendererInstance::ClearDepth(const float depth) {
  m_FrameBuffer->ClearDepth(depth);
}

} // namespace Rasterization