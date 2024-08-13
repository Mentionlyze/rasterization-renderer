#include "Runtime/RendererInstance.hpp"

namespace Rasterization {

RendererInstance::RendererInstance() {
    m_Camera = CreateRef<Camera>(45.0f, 1280.0f / 900.0f, 0.1, 100.0f);
}

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

}  // namespace Rasterization