#pragma once

#include "Math.hpp"

namespace Rasterization {
class Camera {
public:
  Camera(const float fov, const float aspect, const float near, const float far)
      : m_Fov(fov), m_Aspect(aspect), m_Near(near), m_Far(far),
        m_Position{0.0f, 0.0f, 0.0f}, m_ViewMat(Mat4::Identity()),
        m_ViewDir{0.0f, 0.0f, 0.0f} {
    m_Perspective = CreateNDCFrustum(m_Fov, m_Aspect, m_Near, m_Far);
  }

  ~Camera() = default;

  Mat4 GetPerspective() const { return m_Perspective; }
  Mat4 GetViewMat() const { return m_ViewMat; }

  void SetPosition(const Vec3 &pos) { m_Position = pos; }
  Vec3 GetPosition() const { return m_Position; }

private:
  float m_Fov, m_Aspect, m_Near, m_Far;
  Mat4 m_Perspective;
  Vec3 m_Position;
  Mat4 m_ViewMat;
  Vec3 m_ViewDir;
};
} // namespace Rasterization