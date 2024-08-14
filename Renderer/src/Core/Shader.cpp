#include "Core/Shader.hpp"

namespace Rasterization {
Shader::Shader(const std::function<Vertex(Vertex& vertex, Texture& texture)>& vertext_lamda,
               const std::function<Color(Vertex& vertex, Texture& texture)>& pixel_lamda) {
    m_VertexLamda = vertext_lamda;
    m_PixelLamda = pixel_lamda;
    m_Uniform = Uniform{};
}
}  // namespace Rasterization