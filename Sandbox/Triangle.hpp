#include "Runtime/Layer.hpp"

class Triangle : public Rasterization::Layer {
public:
  Triangle();

  void OnUpdate() override;
};