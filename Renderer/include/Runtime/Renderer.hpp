#include "RendererInstance.hpp"
#include <cstdint>

namespace Rasterization {
class Renderer {
public:
  static void Init(const uint32_t width, const uint32_t height);
  static void SetViewport(const uint32_t width, const uint32_t height);
  static void Clear();
  static void ClearDepth();
  static void BeginScene();
  static void EndScene();
  static void Submit();

private:
  static RendererInstance *s_RendererInstance;
};
} // namespace Rasterization