#include "Core/Berycentric.hpp"

namespace Rasterization {
Berycentric::Berycentric(const Vec2 &point, const Vertex (&vertices)[3]) {
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
}  // namespace Rasterization