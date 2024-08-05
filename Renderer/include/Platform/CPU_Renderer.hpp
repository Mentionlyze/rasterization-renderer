#pragma once

#include "Runtime/Renderer.hpp"
#include <cstdint>

namespace Rasterization {
class CPU_Renderer : public RendererInstance {
public:
  virtual void Init(const uint32_t width, const uint32_t height) override;
  virtual void SetViewport(const uint32_t width,
                           const uint32_t height) override;
};
} // namespace Rasterization