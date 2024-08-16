#include "Triangle.hpp"
#include "Core/Texture.hpp"
#include "Runtime/Renderer.hpp"

Triangle::Triangle() : Layer("Triangle"), m_Radius(0.0f) {
    m_Vertices = {
        Rasterization::Vertex{ {-0.5f, 0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

        Rasterization::Vertex{  {0.5f, 0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},

        Rasterization::Vertex{{-0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},

        Rasterization::Vertex{ {0.5f, -0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    };

    m_Texture = Rasterization::TextureStorage::CreateTexture("Assets/vue.jpg");

    auto vertex_lamda = [this](Rasterization::Vertex &vertex, const Rasterization::Uniform &uniform) {
        auto perspective = uniform.mat4_Map.at(1);
        auto view = uniform.mat4_Map.at(2);
        auto model = uniform.mat4_Map.at(3);

        vertex.position = perspective * view * model * vertex.position;

        return vertex;
    };

    auto pixel_lamda = [this](Rasterization::Vertex &vertex, const Rasterization::Uniform &uniform) {
        auto texture_id = uniform.texture_Map.at(1);
        auto texture = Rasterization::TextureStorage::GetTexture(texture_id);
        auto color = Rasterization::TextureSample(texture, vertex.uv);
        return color;
    };

    m_Shader = Rasterization::CreateRef<Rasterization::Shader>(vertex_lamda, pixel_lamda);

    m_Shader->SetTexture(1, m_Texture);
    m_Shader->SetMat4Uniform(1, Rasterization::Renderer::GetCamera()->GetPerspective());
    m_Shader->SetMat4Uniform(2, Rasterization::Renderer::GetCamera()->GetViewMat());
}

void Triangle::OnUpdate() {
    Rasterization::Renderer::Clear({0.0f, 0.0f, 0.0f, 1.0f});

    auto trans = Rasterization::CreateTranslation({0.0f, 0.0f, -4.0f});

    auto model = trans * Rasterization::CreateYRotation(m_Radius);
    m_Shader->SetMat4Uniform(3, model);

    auto indices = {0, 1, 2, 2, 3, 1};
    // auto indices = {0, 1, 2};

    Rasterization::Renderer::Submit(m_Vertices, indices, m_Shader);

    m_Radius += 0.01;
}