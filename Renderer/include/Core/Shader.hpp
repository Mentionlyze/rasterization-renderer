#pragma once

#include "Core/Texture.hpp"
#include "Core/Vertex.hpp"
#include <cstdint>
#include <functional>
#include <map>

namespace Rasterization {
struct Uniform {
    std::map<uint8_t, int32_t> int_Map;
    std::map<uint8_t, float> float_Map;
    std::map<uint8_t, Vec2> vec2_Map;
    std::map<uint8_t, Vec3> vec3_Map;
    std::map<uint8_t, Vec4> vec4_Map;
    std::map<uint8_t, Mat4> mat4_Map;
    std::map<uint8_t, uint32_t> texture_Map;
};

class Shader {
public:
    Shader(const std::function<Vertex(Vertex& vertex, const Uniform& uniform)>& vertext_lamda,
           const std::function<Color(Vertex& vertex, const Uniform& uniform)>& pixel_lamda);

    ~Shader() = default;

    Vertex CallVertexChanging(Vertex& vertex);
    Color CallPixelShading(Vertex& vertex);

    Uniform GetUniform() const { return m_Uniform; }

    void SetIntUniform(const uint8_t name, const int32_t value) { m_Uniform.int_Map[name] = value; }

    int32_t GetIntUniform(const uint8_t name) { return m_Uniform.int_Map[name]; }

    void SetFloatUniform(const uint8_t name, const float value) { m_Uniform.float_Map[name] = value; }

    int32_t GetFloatUniform(const uint8_t name) { return m_Uniform.float_Map[name]; }

    void SetVec2Uniform(const uint8_t name, const Vec2& value) { m_Uniform.vec2_Map[name] = value; }

    Vec2 GetVec2Uniform(const uint8_t name) { return m_Uniform.vec2_Map[name]; }

    void SetVec3Uniform(const uint8_t name, const Vec3& value) { m_Uniform.vec3_Map[name] = value; }

    Vec3 GetVec3Uniform(const uint8_t name) { return m_Uniform.vec3_Map[name]; }

    void SetVec4Uniform(const uint8_t name, const Vec4& value) { m_Uniform.vec4_Map[name] = value; }

    Vec4 GetVec4Uniform(const uint8_t name) { return m_Uniform.vec4_Map[name]; }

    void SetMat4Uniform(const uint8_t name, const Mat4& value) { m_Uniform.mat4_Map[name] = value; }

    Mat4 GetMat4Uniform(const uint8_t name) { return m_Uniform.mat4_Map[name]; }

    void SetTexture(const uint8_t name, const uint32_t value) { m_Uniform.texture_Map[name] = value; }

    uint32_t GetTexture(const uint8_t name) { return m_Uniform.texture_Map[name]; }

private:
    std::function<Vertex(Vertex& vertex, const Uniform& uniform)> m_VertexLamda;
    std::function<Color(Vertex& vertex, const Uniform& uniform)> m_PixelLamda;

private:
    Uniform m_Uniform;
};

inline Color TextureSample(const Ref<Texture>& texture, const Vec2& uv) {
    auto width = texture->GetWidth();
    auto height = texture->GetHeight();
    auto x = (uint32_t)(uv.x * (width - 1));
    auto y = (uint32_t)(uv.y * (height - 1));

    ASSERT(x < (width) && y < (height));

    auto color = texture->GetColor(x, y);
    return color;
}
}  // namespace Rasterization