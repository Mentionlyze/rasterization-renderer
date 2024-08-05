#include "Platform/CPU_Renderer.hpp"
#include <cstdint>

namespace Rasterization {
void Renderer::Init(const uint32_t width, const uint32_t height) {
  s_RendererInstance = new CPU_Renderer(width, height);
}

void Renderer::SetViewport(const uint32_t width, const uint32_t height) {
  s_RendererInstance->SetViewport(width, height);
}

void Renderer::Clear() {}

void Renderer::ClearDepth() {}

void Renderer::BeginScene() {}

void Renderer::EndScene() {}

void Renderer::Submit() {}
} // namespace Rasterization