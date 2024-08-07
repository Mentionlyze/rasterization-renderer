#include "Runtime/Buffer.hpp"

namespace Rasterization {
VertexBuffer::VertexBuffer(const float (&vertices)[], uint32_t size) {
  auto len = size / sizeof(float);
  for (uint32_t i = 0; i < len; i++) {
  }
}

VertexBuffer::~VertexBuffer() {}
} // namespace Rasterization