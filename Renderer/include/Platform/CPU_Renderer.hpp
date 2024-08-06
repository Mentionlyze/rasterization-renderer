#pragma once

#include "Runtime/RendererInstance.hpp"

namespace Rasterization {
class CPU_Renderer : public RendererInstance {
public:
  CPU_Renderer();

  void DrawArrays() {}

  void DrawElements() {}

  void DrawLine() {}

private:
  void RasterizeTriangle();
  void DrawTrapezoid();
  void DrawScanline();
  void DrawLineWithClip();
};
} // namespace Rasterization