#include "Core/Vertex.hpp"
#include "Runtime/Layer.hpp"
#include <vector>

class Triangle : public Rasterization::Layer {
public:
    Triangle();

    void OnUpdate() override;

private:
    std::vector<Rasterization::Vertex> m_Vertices;
    float m_Radius;
};