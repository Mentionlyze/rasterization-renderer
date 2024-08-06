#include "Runtime/Application.hpp"
#include "Runtime/Renderer.hpp"

namespace Rasterization {
Application *Application::s_Instance = nullptr;

Application::Application(const std::string &title, const uint32_t width,
                         const uint32_t height)
    : m_Title(title), m_Width(width), m_Height(height) {
  s_Instance = this;
  m_Window = Window::Create(title, width, height);
  Renderer::Init(width, height);
}

Application::~Application() {}

void Application::Run() {
  while (m_Running) {
    m_Window->PollInputEvents();

    for (Layer *layer : m_LayerStack) {
      layer->OnUpdate();
    }
    m_Window->OnUpdate();
  }
}

void Application::PushLayer(Layer *layer) { m_LayerStack.PushLayer(layer); }

} // namespace Rasterization