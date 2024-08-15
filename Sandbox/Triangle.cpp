#include "Triangle.hpp"
#include "Core/Texture.hpp"
#include "Runtime/Renderer.hpp"

Triangle::Triangle() : Layer("Triangle"), m_Radius(0.0f) {
    m_Vertices = {
        Rasterization::Vertex{ Rasterization::Vec3{-0.5f, 0.5f}, Rasterization::Vec2{0.0f, 1.0f}},
        Rasterization::Vertex{  Rasterization::Vec3{0.5f, 0.5f}, Rasterization::Vec2{1.0f, 1.0f}},
        Rasterization::Vertex{Rasterization::Vec3{-0.5f, -0.5f}, Rasterization::Vec2{0.0f, 0.0f}},
        Rasterization::Vertex{ Rasterization::Vec3{0.5f, -0.5f}, Rasterization::Vec2{1.0f, 0.0f}},
    };

    m_Texture = Rasterization::TextureStorage::CreateTexture("Assets/vue.jpg");

    auto t = Rasterization::TextureStorage::GetTexture(m_Texture);
    auto c = t->GetColor(100, 100);

    auto vertex_lamda = [this](Rasterization::Vertex &vertex, const Rasterization::Uniform &uniform) {
        auto perspective = uniform.mat4_Map.at("perspective");
        auto view = uniform.mat4_Map.at("view");
        auto model = uniform.mat4_Map.at("model");

        vertex.position = perspective * view * model * vertex.position;

        return vertex;
    };

    auto pixel_lamda = [this](Rasterization::Vertex &vertex, const Rasterization::Uniform &uniform) {
        auto texture = Rasterization::TextureStorage::GetTexture(m_Texture);
        auto color = Rasterization::TextureSample(texture, vertex.uv);
        return vertex.color;
    };

    m_Shader = Rasterization::CreateRef<Rasterization::Shader>(vertex_lamda, pixel_lamda);

    m_Shader->SetTexture("texture_1", m_Texture);
    m_Shader->SetMat4Uniform("perspective", Rasterization::Renderer::GetCamera()->GetPerspective());
    m_Shader->SetMat4Uniform("view", Rasterization::Renderer::GetCamera()->GetViewMat());
}

void Triangle::OnUpdate() {
    Rasterization::Renderer::Clear({0.0f, 0.0f, 0.0f, 1.0f});

    auto trans = Rasterization::CreateTranslation({0.0f, 0.0f, -4.0f});

    auto model = trans * Rasterization::CreateYRotation(m_Radius);
    m_Shader->SetMat4Uniform("model", model);

    auto indices = {0, 1, 2, 2, 3, 1};
    // auto indices = {0, 1, 2};

    Rasterization::Renderer::Submit(m_Vertices, indices, m_Shader);

    m_Radius += 0.01;
}