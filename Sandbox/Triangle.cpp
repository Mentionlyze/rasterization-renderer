#include "Triangle.hpp"
#include "Core/Texture.hpp"
#include "Runtime/Renderer.hpp"
#include <iostream>

Triangle::Triangle() : Layer("Triangle"), m_Radius(0.0f) {
  m_Vertices = {
      Rasterization::Vertex{Rasterization::Vec3{-0.5f, 0.5f},
                            {1.0f, 0.0f, 0.0f, 1.0f}},
      Rasterization::Vertex{Rasterization::Vec3{0.5f, 0.5f},
                            {0.0f, 1.0f, 0.0f, 1.0f}},
      Rasterization::Vertex{Rasterization::Vec3{-0.5f, -0.5f},
                            {0.0f, 0.0f, 1.0f, 1.0f}},
      Rasterization::Vertex{Rasterization::Vec3{0.5f, -0.5f},
                            {1.0f, 1.0f, 0.0f, 1.0f}},
  };

  // m_Vertices = {Rasterization::Vertex{Rasterization::Vec3{-0.5f, 0.5f},
  //                                     {1.0f, 0.0f, 0.0f, 1.0f}},
  //               Rasterization::Vertex{Rasterization::Vec3{0.5f, 0.5f},
  //                                     {0.0f, 1.0f, 0.0f, 1.0f}},
  //               Rasterization::Vertex{Rasterization::Vec3{0.0f, -0.5f},
  //                                     {0.0f, 0.0f, 1.0f, 1.0f}}};

  auto texture_Storage = Rasterization::TextureStorage{};
  auto path = std::string{"/Assets/vue.jpg"};
  auto path_result = path.c_str();
  std::cout << path.c_str() << "\n";
  auto id = texture_Storage.CreateTexture("Sandbox/vue.jpg");
  std::cout << id << "\n";
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