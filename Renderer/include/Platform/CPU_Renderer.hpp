#include "Runtime/Renderer.hpp"
#include <cstdint>

namespace Rasterization {
class CPU_Renderer : public RendererInstance {
public:
  CPU_Renderer(const uint32_t width, const uint32_t height);
  ~CPU_Renderer();

  virtual void SetViewport(const uint32_t width,
                           const uint32_t height) const override;
};
} // namespace Rasterization