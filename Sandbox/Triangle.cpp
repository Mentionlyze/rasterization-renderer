#include "Triangle.hpp"
#include "Core/Texture.hpp"
#include "Runtime/Renderer.hpp"
#include <filesystem>
#include <iostream>

Triangle::Triangle() : Layer("Triangle"), m_Radius(0.0f) {
    m_Vertices = {
        Rasterization::Vertex{ Rasterization::Vec3{-0.5f, 0.5f},
                              {1.0f, 0.0f, 0.0f, 1.0f}},
        Rasterization::Vertex{  Rasterization::Vec3{0.5f, 0.5f},
                              {0.0f, 1.0f, 0.0f, 1.0f}},
        Rasterization::Vertex{Rasterization::Vec3{-0.5f, -0.5f},
                              {0.0f, 0.0f, 1.0f, 1.0f}},
        Rasterization::Vertex{ Rasterization::Vec3{0.5f, -0.5f},
                              {1.0f, 1.0f, 0.0f, 1.0f}},
    };

    // m_Vertices = {Rasterization::Vertex{Rasterization::Vec3{-0.5f, 0.5f},
    //                                     {1.0f, 0.0f, 0.0f, 1.0f}},
    //               Rasterization::Vertex{Rasterization::Vec3{0.5f, 0.5f},
    //                                     {0.0f, 1.0f, 0.0f, 1.0f}},
    //               Rasterization::Vertex{Rasterization::Vec3{0.0f, -0.5f},
    //                                     {0.0f, 0.0f, 1.0f, 1.0f}}};

    int width, height, nrComponents;
    std::filesystem::path path = "Assets/L04.png";

    std::cout << std::filesystem::absolute(path).string() << "\n";
    unsigned char *data =
        stbi_load(std::filesystem::absolute(path).string().c_str(), &width,
                  &height, &nrComponents, 0);
    if (data == nullptr) {
        ASSERT(data);
    }

    auto pixel = (unsigned int)data[100000];

    // std::cout << pixel << "\n";

    // auto texture_Storage = Rasterization::TextureStorage{};
    // auto path_result = path.c_str();
    // auto id = texture_Storage.CreateTexture("Assets/vue.jpg");
    // std::cout << id << "\n";
}

void Triangle::OnUpdate() {
    Rasterization::Renderer::Clear({0.0f, 0.0f, 0.0f, 1.0f});

    auto trans = Rasterization::CreateTranslation({0.0f, 0.0f, -4.0f});

    auto model = trans * Rasterization::CreateYRotation(m_Radius);

    auto indices = {0, 1, 2, 2, 3, 1};
    // auto indices = {0, 1, 2};

    Rasterization::Renderer::Submit(m_Vertices, indices, model);

    m_Radius += 0.01;
}