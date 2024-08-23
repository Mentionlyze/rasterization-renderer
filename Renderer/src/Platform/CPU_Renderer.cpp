#include "Platform/CPU_Renderer.hpp"
#include "Core/Bresenham.hpp"
#include "Core/Scanline.hpp"
#include "Core/Vertex.hpp"
#include "Platform/GPU_Renderer.hpp"
#include <cmath>

namespace Rasterization {
CPU_Renderer::CPU_Renderer() {}

void CPU_Renderer::DrawArrays(const std::vector<Vertex> &vertices, const Ref<Shader> &shader) {
    auto len = vertices.size() / 3;
    for (uint32_t i = 0; i < len; i++) {
        Vertex result[3] = {vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]};

        RasterizeTriangle(result, shader);
    }
}

void CPU_Renderer::DrawElements(const std::vector<Vertex> &vertices, const std::initializer_list<int32_t> &indices,
                                const Ref<Shader> &shader) {
    std::vector<Vertex> result;

    auto it = indices.begin();
    while (it != indices.end()) {
        result.push_back(vertices[*it]);
        it++;
    }

    DrawArrays(result, shader);
}

void CPU_Renderer::RasterizeTriangle(Vertex (&vertices)[3], const Ref<Shader> &shader) {
    for (uint32_t i = 0; i < 3; i++) {
        // call vertex_changing
        shader->CallVertexChanging(vertices[i]);

        // save true z
        vertices[i].position.z = -(vertices[i].position.w);

        // perspective transfrom
        vertices[i].position.x = 1 / vertices[i].position.w * vertices[i].position.x;
        vertices[i].position.y = 1 / vertices[i].position.w * vertices[i].position.y;
        vertices[i].position.w = 1.0f;

        // viewport transform
        vertices[i].position.x = (vertices[i].position.x + 1.0f) * 0.5f * (m_Viewport.w - 1.0f) + m_Viewport.x;

        vertices[i].position.y =
            m_Viewport.h - (vertices[i].position.y + 1.0f) * 0.5f * (m_Viewport.h - 1.0f) + m_Viewport.y;
    }
    auto [trap_1, trap_2] = Trapezoid::FromTriangle(vertices);
    if (trap_1) {
        DrawTrapezoid(trap_1.value(), shader);
    }

    if (trap_2) {
        DrawTrapezoid(trap_2.value(), shader);
    }
}

void CPU_Renderer::DrawTrapezoid(Trapezoid &trap, const Ref<Shader> &shader) {
    auto top = (uint32_t)(std::max({std::ceil(trap.top), 0.0f}));
    auto bottom = (uint32_t)std::min({std::ceil(trap.bottom), (float)(m_Viewport.h)}) - 1;

    auto y = top;

    InterpInit(trap.left.v1);
    InterpInit(trap.left.v2);
    InterpInit(trap.right.v1);
    InterpInit(trap.right.v2);

    while (y <= bottom) {
        auto scanline = Scanline::FromTrapzoid(trap, y);
        DrawScanline(scanline, shader);
        y++;
    }
}

void CPU_Renderer::InterpInit(Vertex &v) {
    auto interp_Z = 1.0f / v.position.z;
    v.position.z = interp_Z;
    Vertex::TransformVertex(v, [interp_Z](float value) { return value * interp_Z; });
}

void CPU_Renderer::DrawScanline(const Scanline &scanline, const Ref<Shader> &shader) {
    auto t_Scanline = scanline;
    auto vertex = t_Scanline.vertex;
    auto y = t_Scanline.y;

    while (t_Scanline.width > 0.0f) {
        auto x = vertex.position.x;
        if (x >= 0.0f && x < (float)(m_Viewport.w - 1)) {
            auto correct_vertex = vertex;
            auto correct_z = correct_vertex.position.z;
            auto z = 1.0f / correct_z;
            Vertex::TransformVertex(correct_vertex, [z](float value) { return value * z; });
            auto color = shader->CallPixelShading(correct_vertex);
            m_FrameBuffer->SetColor((uint32_t)x, (uint32_t)y, color);
        }

        t_Scanline.width -= 1.0f;
        vertex.position += t_Scanline.step.position;
        vertex.color += t_Scanline.step.color;
        vertex.uv += t_Scanline.step.uv;
        vertex.normal += t_Scanline.step.normal;
    }
}

void CPU_Renderer::DrawLine(const std::vector<Vec2> &points) {
    auto len = points.size() / 2;
    auto rect_min = Vec2{(float)m_Viewport.x, (float)m_Viewport.y};
    auto rect_max = Vec2{(float)m_Viewport.w, (float)m_Viewport.h};
    for (uint32_t i = 0; i < len; i++) {
        auto p1 = points[i * 2];
        auto p2 = points[i * 2 + 1];

        auto bresenham = Bresenham{p1, p2, rect_min, rect_max};
        bresenham.IteratorCallback(
            [&](int32_t x, int32_t y) { m_FrameBuffer->SetColor(x, y, {0.2f, 1.0f, 0.0f, 1.0f}); });
    }
}
}  // namespace Rasterization