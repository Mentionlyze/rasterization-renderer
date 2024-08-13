#pragma once

#include "Core/Camera.hpp"
#include "Core/Vertex.hpp"
#include "FrameBuffer.hpp"
#include <cstdint>
#include <initializer_list>
#include <vector>

namespace Rasterization {

struct Viewport {
    int32_t x, y;
    int32_t w, h;

    Viewport() = default;

    Viewport(int32_t width, int32_t height) {
        x = 0;
        y = 0;
        w = width;
        h = height;
    }
};

class RendererInstance {
public:
    RendererInstance();
    virtual ~RendererInstance() = default;

    void Init(const int32_t width, const int32_t height);
    void SetViewport(const int32_t width, const int32_t height);
    void Clear(const Color &color);
    void ClearDepth(const float depth);

    Ref<FrameBuffer> GetFrameBuffer() { return m_FrameBuffer; }

    Viewport GetViewport() { return m_Viewport; }

    virtual void DrawArrays(const std::vector<Vertex> &vertices,
                            const Mat4 &model) {}

    virtual void DrawElements(const std::vector<Vertex> &vertices,
                              const std::initializer_list<int32_t> &indices,
                              const Mat4 &model) {}

    virtual void DrawLine(const std::vector<Vec2> &points) {}

protected:
    Viewport m_Viewport;
    Ref<FrameBuffer> m_FrameBuffer;
    Ref<Camera> m_Camera;
};
}  // namespace Rasterization