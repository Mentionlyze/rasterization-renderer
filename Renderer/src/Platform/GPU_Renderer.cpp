#include "Platform/GPU_Renderer.hpp"
#include "Core/Berycentric.hpp"
#include "Core/Texture.hpp"

namespace Rasterization {
GPU_Renderer::GPU_Renderer() {}

GPU_Renderer::~GPU_Renderer() {}

void GPU_Renderer::DrawArrays(const std::vector<Vertex> &vertices, const Ref<Shader> &shader) {
    auto len = vertices.size() / 3;
    for (uint32_t i = 0; i < len; i++) {
        Vertex result[3] = {vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]};
        RasterizeTriangle(result, shader);
    }
}

void GPU_Renderer::DrawElements(const std::vector<Vertex> &vertices, const std::initializer_list<int32_t> &indices,
                                const Ref<Shader> &shader) {
    std::vector<Vertex> result;

    auto it = indices.begin();
    while (it != indices.end()) {
        result.push_back(vertices[*it]);
        it++;
    }

    DrawArrays(result, shader);
}

void GPU_Renderer::RasterizeTriangle(Vertex (&vertices)[3], const Ref<Shader> &shader) {
    auto uniform = shader->GetUniform();
    for (uint32_t i = 0; i < 3; i++) {
        // vertex_change
        shader->CallVertexChanging(vertices[i], uniform);

        // perspective transfrom
        vertices[i].position = 1 / vertices[i].position.w * vertices[i].position;

        // viewport transform
        vertices[i].position.x = (vertices[i].position.x + 1.0f) * 0.5f * (m_Viewport.w - 1.0f) + m_Viewport.x;

        vertices[i].position.y =
            m_Viewport.h - (vertices[i].position.y + 1.0f) * 0.5f * (m_Viewport.h - 1.0f) + m_Viewport.y;
    }

    auto box = BoundingBox{vertices, m_Viewport};
    // for (uint32_t x = box.min.x; x < box.max.x; x++) {
    //   for (uint32_t y = box.min.y; y < box.max.y; y++) {
    //     auto point = Vec2{(float)x, (float)y};
    //     auto berycentric = Berycentric{point, vertices};
    //     if (berycentric.Inside()) {
    //       auto color = berycentric.GetAlpha() * vertices[0].color +
    //                    berycentric.GetBeta() * vertices[1].color +
    //                    berycentric.GetGamma() * vertices[2].color;
    //       m_FrameBuffer->SetColor((uint32_t)x, (uint32_t)y, color);
    //     }
    //   }

    //   // std::cout << y << "\n";
    // }

    for (const Vec2 &point : box.points) {
        auto berycentric = Berycentric{point, vertices};
        if (!berycentric.Inside()) continue;
        auto vertex = GetBerycentricFilteredVertex(vertices, berycentric);

        auto color = shader->CallPixelShading(vertex, uniform);

        m_FrameBuffer->SetColor((uint32_t)(point.x), (uint32_t)(point.y), color);
    }
}

void GPU_Renderer::DrawLine(const std::vector<Vec2> &line) {}

Vertex GPU_Renderer::GetBerycentricFilteredVertex(Vertex (&vertices)[3], const Berycentric &berycentric) {
    auto position = vertices[0].position * berycentric.GetAlpha() + vertices[1].position * berycentric.GetBeta() +
                    vertices[2].position * berycentric.GetGamma();

    auto color = vertices[0].color * berycentric.GetAlpha() + vertices[1].color * berycentric.GetBeta() +
                 vertices[2].color * berycentric.GetGamma();

    auto uv = vertices[0].uv * berycentric.GetAlpha() + vertices[1].uv * berycentric.GetBeta() +
              vertices[2].uv * berycentric.GetGamma();

    auto normal = vertices[0].normal * berycentric.GetAlpha() + vertices[1].normal * berycentric.GetBeta() +
                  vertices[2].normal * berycentric.GetGamma();

    return Vertex{position, color, uv, normal};
}
}  // namespace Rasterization