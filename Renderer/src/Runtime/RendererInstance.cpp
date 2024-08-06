#include "Runtime/RendererInstance.hpp"

namespace Rasterization {

RendererInstance::RendererInstance() {}

void RendererInstance::Init(const int32_t width, const int32_t height) {
  m_FrameBuffer = CreateRef<FrameBuffer>(width, height);
}

void RendererInstance::SetViewport(const uint32_t width,
                                   const uint32_t height) {}

void RendererInstance::Clear(const Color &color) {
  m_FrameBuffer->Clear(color);
}

void RendererInstance::ClearDepth(const float depth) {
  m_FrameBuffer->ClearDepth(depth);
}

} // namespace Rasterization