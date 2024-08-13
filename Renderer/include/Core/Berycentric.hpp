#pragma once

#include "Math.hpp"
#include "Vertex.hpp"
#include <cstdlib>

namespace Rasterization {

class Berycentric {
public:
    Berycentric(const Vec2 &point, const Vertex (&vertices)[3]);
    ~Berycentric() = default;

    bool Inside() { return m_Alpha + m_Beta + m_Gamma <= 1.000001; }

    float GetAlpha() const { return m_Alpha; }

    float GetBeta() const { return m_Beta; }

    float GetGamma() const { return m_Gamma; }

private:
    float m_Alpha, m_Beta, m_Gamma;
};
}  // namespace Rasterization