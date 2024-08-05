#pragma once

#include <cstdint>
namespace Rasterization {
class RendererInstance {
public:
  virtual void Init(const uint32_t width, const uint32_t height) = 0;
  virtual void SetViewport(const uint32_t width, const uint32_t height) = 0;
};
} // namespace Rasterization