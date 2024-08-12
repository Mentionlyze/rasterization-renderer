#include "Runtime/Renderer.hpp"
#include "Platform/CPU_Renderer.hpp"
#include "Platform/GPU_Renderer.hpp"
#include "Runtime/RendererInstance.hpp"

namespace Rasterization {

#if USE_CPU_RENDERER
RendererInstance *Renderer::s_RendererInstance = new CPU_Renderer();
#endif

#if USE_GPU_RENDERER
RendererInstance *Renderer::s_RendererInstance = new GPU_Renderer();
#endif
} // namespace Rasterization