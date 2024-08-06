#include "Platform/WindowsWindow.hpp"

namespace Rasterization {
Scope<Window> Window::Create(const std::string &title, const uint32_t width,
                             const uint32_t height) {
  return CreateScope<WindowsWindow>(title, width, height);
}
} // namespace Rasterization
