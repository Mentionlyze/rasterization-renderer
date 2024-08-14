#pragma once

#include "Core/Texture.hpp"
#include "Core/Vertex.hpp"
#include <functional>
#include <unordered_map>

namespace Rasterization {
class Shader {
public:
    Shader(const std::function<Vertex(Vertex& vertex, Texture& texture)>& vertext_lamda,
           const std::function<Color(Vertex& vertex, Texture& texture)>& pixel_lamda);

    ~Shader() = default;

    void CallVertexChanging();
    void CallPixelShading();

    void SetUniform(const std::string& name, const int32_t value) { m_Uniform.int_Map[name] = value; }

    void SetUniform(const std::string& name, const float value) { m_Uniform.float_Map[name] = value; }

    void SetUniform(const std::string& name, const Vec2& value) { m_Uniform.vec2_Map[name] = value; }

    void SetUniform(const std::string& name, const Vec3& value) { m_Uniform.vec3_Map[name] = value; }

    void SetUniform(const std::string& name, const Vec4& value) { m_Uniform.vec4_Map[name] = value; }

    void SetUniform(const std::string& name, const Mat4& value) { m_Uniform.mat4_Map[name] = value; }

    void SetTexture(const std::string& name, const uint32_t value) { m_Uniform.texture_Map[name] = value; }

private:
    std::function<Vertex(Vertex& vertex, Texture& texture)> m_VertexLamda;
    std::function<Color(Vertex& vertex, Texture& texture)> m_PixelLamda;

private:
    struct Uniform {
        std::unordered_map<std::string, int32_t> int_Map;
        std::unordered_map<std::string, float> float_Map;
        std::unordered_map<std::string, Vec2> vec2_Map;
        std::unordered_map<std::string, Vec3> vec3_Map;
        std::unordered_map<std::string, Vec4> vec4_Map;
        std::unordered_map<std::string, Mat4> mat4_Map;
        std::unordered_map<std::string, uint32_t> texture_Map;
    };

    Uniform m_Uniform;
};
}  // namespace Rasterization