#pragma once

#include <cstdint>
namespace Rasterization {
class VertexBuffer {
public:
  VertexBuffer(const float (&vertices)[], uint32_t size);
  ~VertexBuffer();
};
} // namespace Rasterization