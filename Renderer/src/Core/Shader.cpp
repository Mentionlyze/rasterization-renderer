#include "Core/Shader.hpp"

namespace Rasterization {
Shader::Shader(const std::function<Vertex(Vertex& vertex, const Uniform& uniform)>& vertext_lamda,
               const std::function<Color(Vertex& vertex, const Uniform& uniform)>& pixel_lamda) {
    m_VertexLamda = vertext_lamda;
    m_PixelLamda = pixel_lamda;
    m_Uniform = Uniform{};
}

Vertex Shader::CallVertexChanging(Vertex& vertex, const Uniform& uniform) {
    return m_VertexLamda(vertex, uniform);
}

Color Shader::CallPixelShading(Vertex& vertex, const Uniform& uniform) {
    return m_PixelLamda(vertex, uniform);
}
}  // namespace Rasterization