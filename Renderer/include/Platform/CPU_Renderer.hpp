#pragma once

#include "Runtime/RendererInstance.hpp"

namespace Rasterization {
class CPU_Renderer : public RendererInstance {
public:
  CPU_Renderer();

  void DrawArrays() override;

  void DrawElements() override;

  void DrawLine(const std::vector<Vec2> &points) override;

private:
  void RasterizeTriangle();
  void DrawTrapezoid();
  void DrawScanline();
  void DrawLineWithClip();
};
} // namespace Rasterization