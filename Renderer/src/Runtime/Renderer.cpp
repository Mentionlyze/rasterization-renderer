#include "Runtime/Renderer.hpp"
#include "Platform/CPU_Renderer.hpp"
#include "Platform/GPU_Renderer.hpp"
#include "Runtime/RendererInstance.hpp"

namespace Rasterization {

// RendererInstance *Renderer::s_RendererInstance = new CPU_Renderer();
RendererInstance *Renderer::s_RendererInstance = new GPU_Renderer();

} // namespace Rasterization