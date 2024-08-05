#include "Platform/CPU_Renderer.hpp"
#include <cstdint>

namespace Rasterization {
RendererInstance *s_RendererInstance = new CPU_Renderer();
void Renderer::Init(const uint32_t width, const uint32_t height) {}

inline void Renderer::SetViewport(const uint32_t width, const uint32_t height) {
  s_RendererInstance->SetViewport(width, height);
}

void Renderer::Clear() {}

void Renderer::ClearDepth() {}

void Renderer::BeginScene() {}

void Renderer::EndScene() {}

void Renderer::Submit() {}
} // namespace Rasterization