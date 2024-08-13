#include "Core/Camera.hpp"

namespace Rasterization {
Camera::Camera(const float fov, const float aspect, const float near,
               const float far)
    : m_Fov(fov),
      m_Aspect(aspect),
      m_Near(near),
      m_Far(far),
      m_Position{0.0f, 0.0f, 0.0f},
      m_ViewMat(Mat4::Identity()),
      m_ViewDir{0.0f, 0.0f, 0.0f} {
    m_Perspective = CreateNDCFrustum(m_Fov, m_Aspect, m_Near, m_Far);
}
}  // namespace Rasterization