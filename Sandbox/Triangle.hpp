#include "Core/Math.hpp"
#include "Runtime/Layer.hpp"
#include <vector>

class Triangle : public Rasterization::Layer {
public:
  Triangle();

  void OnUpdate() override;

private:
  std::vector<Rasterization::Vec2> points;
};