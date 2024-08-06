#pragma once

#include <string>
namespace Rasterization {

class Layer {
public:
  Layer(const std::string &name = "Layer");
  virtual ~Layer() = default;

  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnUpdate() {}
  virtual void OnEvent() {}

  inline const std::string &GetName() { return m_DebugName; }

private:
  std::string m_DebugName;
};

} // namespace Rasterization