#pragma once

#include "Core/Scanline.hpp"
#include "Runtime/RendererInstance.hpp"

namespace Rasterization {
class CPU_Renderer : public RendererInstance {
public:
    CPU_Renderer();

    void DrawArrays(const std::vector<Vertex> &vertices, const Ref<Shader> &shader) override;

    void DrawElements(const std::vector<Vertex> &vertices, const std::initializer_list<int32_t> &indices,
                      const Ref<Shader> &shader) override;

    void DrawLine(const std::vector<Vec2> &points) override;

private:
    void RasterizeTriangle(Vertex (&vertices)[3], const Ref<Shader> &shader);
    void DrawTrapezoid(const Trapezoid &trap);
    void DrawScanline(const Scanline &scanline);
    void DrawLineWithClip();
};
}  // namespace Rasterization