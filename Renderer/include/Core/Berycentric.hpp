#pragma once

#include "Math.hpp"
#include "Vertex.hpp"
#include <cstdlib>

namespace Rasterization {

class Berycentric {
public:
  Berycentric(const Vec2 &point, const Vertex (&vertices)[3]) {
    // auto AB = Vec2{vertices[1].position} - Vec2{vertices[0].position};
    // auto BC = Vec2{vertices[2].position} - Vec2{vertices[1].position};
    // auto CA = Vec2{vertices[0].position} - Vec2{vertices[2].position};

    // auto AP = point - Vec2{vertices[0].position};
    // auto BP = point - Vec2{vertices[1].position};
    // auto CP = point - Vec2{vertices[2].position};

    // auto SA = Cross(AB, AP);
    // auto SB = Cross(BC, BP);
    // auto SC = Cross(CA, CP);

    // if ((SA >= 0 && SB >= 0 && SC >= 0) || (SA < 0 && SB < 0 && SC < 0)) {
    //   m_Valid = true;
    // } else {
    //   m_Valid = false;
    // }

    auto area_twice =
        Cross(Vec2(vertices[1].position) - Vec2(vertices[0].position),
              Vec2(vertices[2].position) - Vec2(vertices[0].position));

    auto alpha = std::abs(Cross(Vec2(vertices[1].position) - point,
                                Vec2(vertices[2].position) - point) /
                          area_twice);

    auto beta = std::abs(Cross(Vec2(vertices[0].position) - point,
                               Vec2(vertices[2].position) - point) /
                         area_twice);

    auto gamma = std::abs(Cross(Vec2(vertices[0].position) - point,
                                Vec2(vertices[1].position) - point) /
                          area_twice);

    m_Alpha = alpha;
    m_Beta = beta;
    m_Gamma = gamma;
  }
  ~Berycentric() = default;

  bool Inside() { return m_Alpha + m_Beta + m_Gamma <= 1.000001; }

  float GetAlpha() const { return m_Alpha; }
  float GetBeta() const { return m_Beta; }
  float GetGamma() const { return m_Gamma; }

private:
  float m_Alpha, m_Beta, m_Gamma;
};
} // namespace Rasterization