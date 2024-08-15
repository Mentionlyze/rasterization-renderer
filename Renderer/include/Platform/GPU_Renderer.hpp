#pragma once

#include "Core/Berycentric.hpp"
#include "Runtime/RendererInstance.hpp"
#include <algorithm>

namespace Rasterization {

struct BoundingBox {
    Vec2 min;
    Vec2 max;
    std::vector<Vec2> points;

    BoundingBox(const Vertex (&vertices)[3], const Viewport &canvas) {
        auto min_X = std::max(
            {std::ceil(std::min({vertices[0].position.x, vertices[1].position.x, vertices[2].position.x})), 0.0f});

        auto min_Y = std::max(
            {std::ceil(std::min({vertices[0].position.y, vertices[1].position.y, vertices[2].position.y})), 0.0f});

        auto max_X =
            std::min({std::floor(std::max({vertices[0].position.x, vertices[1].position.x, vertices[2].position.x})),
                      (float)(canvas.w - 1)});

        auto max_Y =
            std::min({std::floor(std::max({vertices[0].position.y, vertices[1].position.y, vertices[2].position.y})),
                      (float)(canvas.h - 1)});

        min = Vec2{min_X, min_Y};
        max = Vec2{max_X, max_Y};

        for (int32_t x = min_X; x < max_X; x++) {
            for (int32_t y = min_Y; y < max_Y; y++) {
                points.push_back(Vec2{(float)x, (float)y});
            }
        }
    }
};

class GPU_Renderer : public RendererInstance {
public:
    GPU_Renderer();
    ~GPU_Renderer();

    void DrawArrays(const std::vector<Vertex> &vertices, const Ref<Shader> &shader) override;

    void DrawElements(const std::vector<Vertex> &vertices, const std::initializer_list<int32_t> &indices,
                      const Ref<Shader> &shader) override;

    void DrawLine(const std::vector<Vec2> &points) override;

private:
    void RasterizeTriangle(Vertex (&vertices)[3], const Ref<Shader> &shader);
    Vertex GetBerycentricFilteredVertex(Vertex (&vertices)[3], const Berycentric &berycentric);
};
}  // namespace Rasterization