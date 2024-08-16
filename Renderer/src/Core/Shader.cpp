#include "Core/Shader.hpp"

namespace Rasterization {
Shader::Shader(const std::function<Vertex(Vertex& vertex, const Uniform& uniform)>& vertext_lamda,
               const std::function<Color(Vertex& vertex, const Uniform& uniform)>& pixel_lamda) {
    m_VertexLamda = vertext_lamda;
    m_PixelLamda = pixel_lamda;
    m_Uniform = Uniform{};
}

Vertex Shader::CallVertexChanging(Vertex& vertex) {
    return m_VertexLamda(vertex, m_Uniform);
}

Color Shader::CallPixelShading(Vertex& vertex) {
    return m_PixelLamda(vertex, m_Uniform);
}
}  // namespace Rasterization