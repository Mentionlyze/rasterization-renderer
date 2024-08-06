#include "Layer.hpp"
#include <vector>

namespace Rasterization {
class LayerStack {
public:
  LayerStack() = default;
  ~LayerStack();

  void PushLayer(Layer *layer);
  void PopLayer(Layer *layer);

  std::vector<Layer *>::iterator begin() { return m_Layers.begin(); }
  std::vector<Layer *>::iterator end() { return m_Layers.end(); }

private:
  std::vector<Layer *> m_Layers;
  uint32_t m_LayerInsert = 0;
};
} // namespace Rasterization