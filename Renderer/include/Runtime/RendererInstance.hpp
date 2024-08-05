#include <cstdint>
namespace Rasterization {
class RendererInstance {
public:
  virtual ~RendererInstance() = default;

  virtual void SetViewport(const uint32_t width,
                           const uint32_t height) const = 0;
};
} // namespace Rasterization