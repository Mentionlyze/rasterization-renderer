#pragma once

#include "Core/Base.hpp"
#include "Core/Window.hpp"
#include <cstdint>
#include <string>

namespace Rasterization {
class Application {
public:
  Application(const std::string &title, const uint32_t width,
              const uint32_t height);
  ~Application();

private:
  Scope<Window> m_Window;
  static Application *s_Instance;
};
} // namespace Rasterization