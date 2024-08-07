#pragma once

#include "LayerStack.hpp"
#include "Window.hpp"
#include <cstdint>
#include <string>

namespace Rasterization {
class Application {
public:
  Application(const std::string &title, const uint32_t width,
              const uint32_t height);
  ~Application();

  void Run();

  void Terminate();

  void PushLayer(Layer *layer);

private:
  std::string m_Title;
  uint32_t m_Width, m_Height;

  Scope<Window> m_Window;
  static Application *s_Instance;

  LayerStack m_LayerStack;
};
} // namespace Rasterization