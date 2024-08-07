#include "Runtime/LayerStack.hpp"
#include <algorithm>

namespace Rasterization {
LayerStack::~LayerStack() {
  for (Layer *layer : m_Layers) {
    delete layer;
  }
}

void LayerStack::PushLayer(Layer *layer) {
  m_Layers.emplace(m_Layers.begin(), layer);
  m_LayerInsert++;
}

void LayerStack::PopLayer(Layer *layer) {
  auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
  if (it != m_Layers.end()) {
    layer->OnDetach();
    m_Layers.erase(it);
    m_LayerInsert--;
  }
}
} // namespace Rasterization