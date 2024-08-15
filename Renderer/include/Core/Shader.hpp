#pragma once

#include "Core/Texture.hpp"
#include "Core/Vertex.hpp"
#include <functional>
#include <unordered_map>

namespace Rasterization {
struct Uniform {
    std::unordered_map<std::string, int32_t> int_Map;
    std::unordered_map<std::string, float> float_Map;
    std::unordered_map<std::string, Vec2> vec2_Map;
    std::unordered_map<std::string, Vec3> vec3_Map;
    std::unordered_map<std::string, Vec4> vec4_Map;
    std::unordered_map<std::string, Mat4> mat4_Map;
    std::unordered_map<std::string, uint32_t> texture_Map;
};

class Shader {
public:
    Shader(const std::function<Vertex(Vertex& vertex, const Uniform& uniform)>& vertext_lamda,
           const std::function<Color(Vertex& vertex, const Uniform& uniform)>& pixel_lamda);

    ~Shader() = default;

    Vertex CallVertexChanging(Vertex& vertex, const Uniform& uniform);
    Color CallPixelShading(Vertex& vertex, const Uniform& uniform);

    Uniform GetUniform() const { return m_Uniform; }

    void SetIntUniform(const std::string& name, const int32_t value) { m_Uniform.int_Map[name] = value; }

    int32_t GetIntUniform(const std::string& name) { return m_Uniform.int_Map[name]; }

    void SetFloatUniform(const std::string& name, const float value) { m_Uniform.float_Map[name] = value; }

    int32_t GetFloatUniform(const std::string& name) { return m_Uniform.float_Map[name]; }

    void SetVec2Uniform(const std::string& name, const Vec2& value) { m_Uniform.vec2_Map[name] = value; }

    Vec2 GetVec2Uniform(const std::string& name) { return m_Uniform.vec2_Map[name]; }

    void SetVec3Uniform(const std::string& name, const Vec3& value) { m_Uniform.vec3_Map[name] = value; }

    Vec3 GetVec3Uniform(const std::string& name) { return m_Uniform.vec3_Map[name]; }

    void SetVec4Uniform(const std::string& name, const Vec4& value) { m_Uniform.vec4_Map[name] = value; }

    Vec4 GetVec4Uniform(const std::string& name) { return m_Uniform.vec4_Map[name]; }

    void SetMat4Uniform(const std::string& name, const Mat4& value) { m_Uniform.mat4_Map[name] = value; }

    Mat4 GetMat4Uniform(const std::string& name) { return m_Uniform.mat4_Map[name]; }

    void SetTexture(const std::string& name, const uint32_t value) { m_Uniform.texture_Map[name] = value; }

    uint32_t GetTexture(const std::string& name) { return m_Uniform.texture_Map[name]; }

private:
    std::function<Vertex(Vertex& vertex, const Uniform& uniform)> m_VertexLamda;
    std::function<Color(Vertex& vertex, const Uniform& uniform)> m_PixelLamda;

private:
    Uniform m_Uniform;
};

inline Color TextureSample(const Ref<Texture>& texture, const Vec2& uv) {
    auto x = uv.x * ((float)(texture->GetWidth()) - 1.0f);
    auto y = uv.y * ((float)(texture->GetHeight()) - 1.0f);

    ASSERT(x < texture->GetWidth() && y < texture->GetHeight());

    auto color = texture->GetColor((uint32_t)x, (uint32_t)y);
    return color;
}
}  // namespace Rasterization