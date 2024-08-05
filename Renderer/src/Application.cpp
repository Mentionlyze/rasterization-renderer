#include "Runtime/Application.hpp"
#include "Runtime/Renderer.hpp"

namespace Rasterization {
Application *Application::s_Instance = nullptr;

Application::Application(const std::string &title, const uint32_t width,
                         const uint32_t height) {
  s_Instance = this;
  Renderer::Init(width, height);
}

Application::~Application() {}
} // namespace Rasterization