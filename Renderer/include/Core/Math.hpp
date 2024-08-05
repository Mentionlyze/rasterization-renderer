#pragma once

#include "Runtime/Application.hpp"
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <ostream>
#include <type_traits>
namespace Rasterization {

constexpr float PI = static_cast<float>(3.14159265358979);

template <typename T>
using MustArithmetic = std::enable_if<std::is_arithmetic_v<T>>;

// clang-format off
template <typename T, typename = MustArithmetic<T>> 
T Rad2Deg(T radians) {
  return radians * 180.0f / PI;
}

template <typename T, typename = MustArithmetic<T>> 
T Deg2Rad(T degrees) {
  return degrees * PI / 180.0f;
}

template <typename T, uint32_t N, typename = MustArithmetic<T>> 
class Vec;


template <typename T, uint32_t Col, uint32_t Row, typename = MustArithmetic<T>> 
class Mat;

using Vec2 = Vec<float, 2>;
using Vec3 = Vec<float, 3>;
using Vec4 = Vec<float, 4>;
using Color = Vec4;

// clang-format on
template <typename T, uint32_t N>
std::ostream &operator<<(std::ostream &o, const Vec<T, N> &v) {
  o << "Vec" << N << "[";
  for (uint32_t i = 0; i < N; i++) {
    o << v.data[i] << " ";
  }
  o << "]";
  return o;
}

template <typename T, uint32_t N>
Vec<T, N> operator+(const Vec<T, N> &v1, const Vec<T, N> &v2);

template <typename T, uint32_t N>
Vec<T, N> operator-(const Vec<T, N> &v1, const Vec<T, N> &v2);

template <typename T, typename U, uint32_t N, typename = MustArithmetic<U>>
Vec<T, N> operator*(U value, const Vec<T, N> &v);

template <typename T, typename U, uint32_t N, typename = MustArithmetic<U>>
Vec<T, N> operator*(const Vec<T, N> &v, U value);

template <typename T, typename U, uint32_t N, typename = MustArithmetic<U>>
Vec<T, N> operator/(const Vec<T, N> &v, U value);

template <typename T, uint32_t N>
Vec<T, N> operator*(const Vec<T, N> &v1, const Vec<T, N> &v2);

template <typename T, uint32_t N>
Vec<T, N> operator/(const Vec<T, N> &v1, const Vec<T, N> &v2);

// clang-format off
template<typename T, uint32_t N>
T LenthSqrd(const Vec<T, N> &v);

template<typename T, uint32_t N>
T Lenth(const Vec<T, N> &v);

template<typename T, uint32_t N>
T Dot(const Vec<T, N>& v1, const Vec<T, N> &v2);

template<typename T>
T Cross(const Vec<T, 2> &v1, const Vec<T, 2> &v2);

template<typename T>
Vec<T, 3> Cross(const Vec<T, 3> &v1, const Vec<T, 3> &v2);

template<typename T, uint32_t N>
Vec<T, N> Normalize(const Vec<T, N> &v);

// clang-format on
template <typename T, uint32_t N>
Vec<T, N> operator+(const Vec<T, N> &v1, const Vec<T, N> &v2) {
  Vec<T, N> result;
  for (uint32_t i = 0; i < N; i++) {
    result.data[i] = v1.data[i] + v2.data[i];
  }
  return result;
}

template <typename T, uint32_t N>
Vec<T, N> operator-(const Vec<T, N> &v1, const Vec<T, N> &v2) {
  Vec<T, N> result;
  for (uint32_t i = 0; i < N; i++) {
    result.data[i] = v1.data[i] - v2.data[i];
  }
  return result;
}

template <typename T, uint32_t N>
Vec<T, N> operator*(const Vec<T, N> &v1, const Vec<T, N> &v2) {
  Vec<T, N> result;
  for (uint32_t i = 0; i < N; i++) {
    result.data[i] = v1.data[i] * v2.data[i];
  }
  return result;
}

template <typename T, typename U, uint32_t N, typename>
Vec<T, N> operator*(U value, const Vec<T, N> &v) {
  Vec<T, N> result;
  for (uint32_t i = 0; i < N; i++) {
    result.data[i] = value * v.data[i];
  }
  return result;
}

template <typename T, typename U, uint32_t N, typename>
Vec<T, N> operator*(const Vec<T, N> &v, U value) {
  return value * v;
}

template <typename T, typename U, uint32_t N, typename>
Vec<T, N> operator/(const Vec<T, N> &v, U value) {
  Vec<T, N> result;
  for (uint32_t i = 0; i < N; i++) {
    result.data[i] = v.data[i] / value;
  }
  return result;
}

template <typename T, uint32_t N>
T Dot(const Vec<T, N> &v1, const Vec<T, N> &v2) {
  T sum{};
  for (uint32_t i = 0; i < N; i++) {
    sum += v1.data[i] * v2.data[i];
  }
  return sum;
}

template <typename T, uint32_t N>
bool operator==(const Vec<T, N> &v1, const Vec<T, N> &v2) {
  for (uint32_t i = 0; i < N; i++) {
    if (v1.data[i] != v2.data[i]) {
      return false;
    }
  }
  return true;
}

template <typename T, uint32_t N>
bool operator!=(const Vec<T, N> &v1, const Vec<T, N> &v2) {
  return !(v1 == v2);
}

template <typename T> T Cross(const Vec<T, 2> &v1, const Vec<T, 2> &v2) {
  return v1.x * v2.y - v1.y * v2.x;
}

template <typename T>
Vec<T, 3> Cross(const Vec<T, 3> &v1, const Vec<T, 3> &v2) {
  Vec<T, 3> result;
  result.x = v1.y * v2.z - v1.z * v2.y;
  result.y = v1.z * v2.x - v1.x * v2.z;
  result.z = v1.x * v2.y - v1.y * v2.x;
  return result;
}

template <typename T, uint32_t N> T LengthSqrd(const Vec<T, N> &v) {
  return Dot(v, v);
}

template <typename T, uint32_t N> T Length(const Vec<T, N> &v) {
  return std::sqrt(LengthSqrd(v));
}

template <typename T, uint32_t N> Vec<T, N> Normalize(const Vec<T, N> &v) {
  return v / Length(v);
}

// vec class
template <typename T, uint32_t N> struct CommonVecOperations {
  using underlying_type = Vec<T, N>;

  T Dot(const underlying_type &o) {
    return Dot(static_cast<const underlying_type &>(*this), o);
  }

  T operator[](uint32_t idx) const {
    return static_cast<const underlying_type &>(*this).data[idx];
  }

  T &operator[](uint32_t idx) {
    return static_cast<underlying_type &>(*this).data[idx];
  }

  underlying_type operator-() const {
    underlying_type result;
    for (uint32_t i = 0; i < N; i++) {
      result.data[i] = -static_cast<const underlying_type &>(*this).data[i];
    }
    return result;
  }

  underlying_type &operator+=(const underlying_type &o) {
    auto &v = static_cast<underlying_type &>(*this);
    v = v + o;
    return v;
  }

  underlying_type &operator-=(const underlying_type &o) {
    auto &v = static_cast<underlying_type &>(*this);
    v = v - o;
    return v;
  }

  underlying_type &operator*=(const underlying_type &o) {
    auto &v = static_cast<underlying_type &>(*this);
    v = v * o;
    return v;
  }

  underlying_type &operator/=(const underlying_type &o) {
    auto &v = static_cast<underlying_type &>(*this);
    v = v / o;
    return v;
  }

  underlying_type &operator*=(T value) {
    auto &v = static_cast<underlying_type &>(*this);
    v = v * value;
    return v;
  }

  underlying_type &operator/=(T value) {
    auto &v = static_cast<underlying_type &>(*this);
    v = v / value;
    return v;
  }

  T LengthSqrd() const {
    return LengthSqrd(static_cast<const underlying_type &>(*this));
  }

  T Length() const {
    return Length(static_cast<const underlying_type &>(*this));
  }

  void Normalize() {
    static_cast<underlying_type &>(*this) =
        Normalize(static_cast<const underlying_type &>(*this));
  }

  underlying_type &operator=(const underlying_type &o) {
    auto &v = static_cast<underlying_type &>(*this);
    for (uint32_t i = 0; i < N; i++) {
      v.data[i] = o.data[i];
    }
    return v;
  }
};

template <typename T, uint32_t N, typename>
class Vec : public CommonVecOperations<T, N> {
public:
  T data[N];

  Vec() { memset(data, 0, N); }

  template <typename U, uint32_t N2> explicit Vec(const Vec<T, N2> &ohter) {
    int i = 0;
    for (; i < std::min(N, N2); i++) {
      data[i] = static_cast<T>(ohter.data[i]);
    }

    while (i < N) {
      data[i++] = T{};
    }
  }

  template <typename U, uint32_t N2> Vec(const Vec<U, N2> &other, T value) {
    int i = 0;
    for (; i < std::min(N, N2); i++) {
      data[i] = static_cast<T>(other.data[i]);
    }

    while (i < N) {
      data[i++] = T{value};
    }
  }

  Vec(const std::initializer_list<T> &initList) {
    auto it = initList.begin();
    uint32_t idx = 0;
    while (it != initList.end() && idx < N) {
      data[idx] = *it;
      it++;
      idx++;
    }

    while (idx < N) {
      data[idx] = T{};
    }
  }
};

template <typename T> class Vec<T, 2> final : public CommonVecOperations<T, 2> {
public:
  union {
    struct {
      T x, y;
    };
    struct {
      T w, h;
    };
    T data[2];
  };

  Vec() : x{}, y{} {}

  explicit Vec(T x) : x(x), y{} {}

  template <typename U, uint32_t N2> explicit Vec(const Vec<U, N2> &other) {
    x = other.data[0];
    y = other.data[1];
  }

  Vec(T x, T y) : x(x), y(y) {}

  Vec(const Vec &) = default;
  Vec &operator=(const Vec &) = default;

  void Set(T x, T y) {
    this->x = x;
    this->y = y;
  }

  T Cross(const Vec<T, 2> &other) { return Cross(*this, other); }
};

template <typename T> class Vec<T, 3> final : public CommonVecOperations<T, 3> {
public:
  union {
    struct {
      T x, y, z;
    };

    struct {
      T r, s, t;
    };

    T data[3];
  };

  Vec() : x{}, y{}, z{} {}

  template <typename U, uint32_t N2> explicit Vec(const Vec<U, N2> &other) {
    Set(other);
  }

  template <typename U, uint32_t N2> Vec(const Vec<U, N2> &other, T value) {
    Set(other, value);
  }

  explicit Vec(T x) : x(x), y{}, z{} {}

  Vec(T x, T y) : x(x), y(y), z{} {}

  Vec(T x, T y, T z) : x(x), y(y), z(z) {}

  Vec(const Vec &) = default;
  Vec &operator=(const Vec &) = default;

  void Set(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  template <typename U, uint32_t N2> void Set(const Vec<U, N2> &other) {
    x = other.data[0];
    y = other.data[1];
    z = N2 >= 3 ? other.data[2] : T{};
  }

  template <typename U, uint32_t N2>
  void Set(const Vec<U, N2> &other, T value) {
    x = other.data[0];
    y = other.data[1];
    z = N2 >= 3 ? other.data[2] : T{value};
  }

  auto Cross(const Vec<T, 3> &o) const { return Cross(*this, o); }
};

template <typename T> class Vec<T, 4> final : public CommonVecOperations<T, 4> {
public:
  union {
    struct {
      T x, y, z, w;
    };

    struct {
      T r, g, b, a;
    };

    T data[4];
  };

  Vec() : x{}, y{}, z{}, w{} {}

  explicit Vec(T x) : x(x), y{}, z{}, w{} {}

  template <typename U, uint32_t N2> explicit Vec(const Vec<U, N2> &other) {
    Set(other);
  }

  template <typename U, uint32_t N2> Vec(const Vec<U, N2> &other, T value) {
    Set(other, value);
  }

  Vec(T x, T y) : x(x), y(y), z{}, w{} {}

  Vec(T x, T y, T z) : x(x), y(y), z(z), w{} {}

  Vec(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

  Vec(const Vec &) = default;
  Vec &operator=(const Vec &) = default;

  void Set(T x, T y, T z, T w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
  }

  template <typename U, uint32_t N2>
  void Set(const Vec<U, N2> &other, T value) {
    x = other.data[0];
    y = other.data[1];
    z = N2 >= 3 ? other.data[2] : T{value};
    w = N2 >= 4 ? other.data[3] : T{value};
  }

  template <typename U, uint32_t N2> void Set(const Vec<U, N2> &other) {
    x = other.data[0];
    y = other.data[1];
    z = N2 >= 3 ? other.data[2] : T{};
    w = N2 >= 4 ? other.data[3] : T{};
  }
};

// mat class
template <typename T, uint32_t Col, uint32_t Row, typename> class Mat {
public:
  T data[Col * Row] = {T{}};

  static Mat Zeros() {
    Mat mat;
    memset(mat.data, 0, sizeof(mat.data));
  }

  static Mat FromCol(const std::initializer_list<Vec<T, Row>> &initVecs) {
    Mat mat;
    auto it = initVecs.begin();
    uint32_t x = 0;
    while (it != initVecs.end()) {
      for (uint32_t y = 0; y < Row; y++) {
        mat.Set(x, y, it->data[y]);
      }
      it++;
      x++;
    }
    return mat;
  }

  static Mat FromRow(const std::initializer_list<Vec<T, Col>> &initVecs) {
    Mat mat;
    auto it = initVecs.begin();
    uint32_t y = 0;
    while (it != initVecs.end()) {
      for (uint32_t x = 0; x < Col; x++) {
        mat.Set(x, y, it->data[x]);
      }
      it++;
      y++;
    }
    return mat;
  }

  static Mat FromCol(const std::initializer_list<T> &initList) {
    auto it = initList.begin();
    uint32_t idx = 0;
    Mat m;

    while (it != initList.end() && idx < Col * Row) {
      m.Set(idx / Row, idx % Row, *it);
      it++;
      idx++;
    }

    return m;
  }

  static Mat FromRow(const std::initializer_list<T> &initList) {
    auto it = initList.begin();
    uint32_t idx = 0;
    Mat m;

    while (it != initList.end() && idx < Col * Row) {
      m.Set(idx % Col, idx / Col, *it);
      it++;
      idx++;
    }

    return m;
  }

  static Mat Identity() {
    static_assert(Row == Col);

    Mat mat = Zeros();
    for (int i = 0; i < Row; i++) {
      mat.Set(i, i, 1);
    }
    return mat;
  }

  static Mat Ones() {
    Mat mat;
    memset(mat.data, 1, sizeof(mat.data));
    return mat;
  }

  T &Get(int x, int y) {
    ASSERT(x >= 0 && x < Col && y >= 0 && y < Row);
    return data[x + y * Col];
  }

  T Get(int x, int y) const {
    ASSERT(x >= 0 && x < Col && y >= 0 && y < Row);
    return data[x + y * Col];
  }

  void Set(int x, int y, T value) { Get(x, y) = value; }

  constexpr int W() const { return Col; }

  constexpr int H() const { return Row; }

  Mat() = default;
};

template <typename T, uint32_t Common, uint32_t Mat1Row, uint32_t Mat2Col>
Mat<T, Mat2Col, Mat1Row> operator*(const Mat<T, Common, Mat1Row> &m1,
                                   const Mat<T, Mat2Col, Common> &m2) {
  Mat<T, Mat2Col, Mat1Row> result = Mat<T, Mat2Col, Mat1Row>::Zeros();
  for (uint32_t i = 0; i < Mat1Row; i++) {
    for (uint32_t j = 0; j < Mat2Col; j++) {
      T sum{};
      for (uint32_t k = 0; k < Common; k++) {
        sum += m1.Get(k, i) * m2.Get(j, k);
      }
      result.Set(j, i, sum);
    }
  }
  return result;
}

template <typename T, typename U, uint32_t Col, uint32_t Row>
Mat<T, Col, Row> operator*(const Mat<T, Col, Row> &m, U value) {
  Mat<T, Col, Row> result = Mat<T, Col, Row>::Zeros();
  for (uint32_t i = 0; i < Col * Row; i++) {
    result.data[i] = m.data[i] * value;
  }
}

template <typename T, typename U, uint32_t Col, uint32_t Row>
Mat<T, Col, Row> operator*(U value, const Mat<T, Col, Row> &m) {
  return m * value;
}

template <typename T, typename U, uint32_t Col, uint32_t Row>
Mat<T, Col, Row> operator/(const Mat<T, Col, Row> &m, T value) {
  Mat<T, Col, Row> result;
  for (uint32_t i = 0; i < Col * Row; i++) {
    result.data[i] = m.data[i] / value;
  }
  return result;
}

template <typename T, uint32_t Col, uint32_t Row>
Mat<T, Col, Row> operator+(const Mat<T, Col, Row> &m1,
                           const Mat<T, Col, Row> &m2) {
  Mat<T, Col, Row> result = Mat<T, Col, Row>::Zeros();
  for (uint32_t i = 0; i < Col * Row; i++) {
    result.data[i] = m1.data[i] + m2.data[i];
  }
  return result;
}

template <typename T, uint32_t Col, uint32_t Row>
Mat<T, Col, Row> operator-(const Mat<T, Col, Row> &m1,
                           const Mat<T, Col, Row> &m2) {
  Mat<T, Col, Row> result = Mat<T, Col, Row>::Zeros();
  for (uint32_t i = 0; i < Col * Row; i++) {
    result.data[i] = m1.data[i] - m2.data[i];
  }
  return result;
}

template <typename T, uint32_t Col, uint32_t Row>
auto operator*(const Mat<T, Col, Row> &m, const Vec<T, Col> &v) {
  Vec<T, Row> result;
  for (uint32_t y = 0; y < Row; y++) {
    T sum{};
    for (uint32_t x = 0; x < Col; x++) {
      sum += m.Get(x, y) * v.data[x];
    }
    result.data[y] = sum;
  }
  return result;
}

template <typename T, uint32_t Col, uint32_t Row>
auto Transpose(const Mat<T, Col, Row> &m) {
  auto result = Mat<T, Col, Row>::Zeros();
  for (uint32_t x = 0; x < Col; x++) {
    for (uint32_t y = 0; y < Row; y++) {
      result.Set(x, y, m.Get(y, x));
    }
  }
  return result;
}

using Mat2 = Mat<float, 2, 2>;
using Mat3 = Mat<float, 3, 3>;
using Mat4 = Mat<float, 4, 4>;

inline Mat4 CreatePersp(float fov, float aspect, float near, float far,
                        bool GLCoord) {
  float focal = 1.0 / (near * std::tan(fov));
  // clang-format off
  return Mat4::FromRow({
    focal / aspect, 0,                          0,                          0,
    0,              (GLCoord ? 1 : -1) *focal,  0,                          0,
    0,              0,                         2.f * near / (far - near), 2.f * near * far / (far - near),
   0,             0,                        -1,                         0,
  });
  // clang-format on
}

inline Mat4 CreateFrustum(float fov, float aspect, float near, float far,
                          bool GLCoord) {
  float focal = 1.0 / (near * std::tan(fov));

  // clang-format off
  return Mat4::FromRow({
    focal,  0,              0,            0,
    0,      aspect * focal, 0,            0,
    0,      0,             1.0,         0,
   0,     0,            -1.0f / near, 0,
  });
  // clang-format on
}

inline Mat4 CreateNDCFrustum(float fov, float aspect, float near, float far,
                             bool GLCoord = 1) {
  float half_w = near * std::tan(fov);
  float half_h = half_w / aspect;
  near = std::abs(near);
  far = std::abs(far);

  // with far plane, clamp x, y, z in [-1, 1]

  // clang-format off
  return Mat4::FromCol({
    near / half_w,  0,              0,                            0,
    0,              near / half_h,  0,                            0,
    0,              0,             (far + near) / (near - far), 2 * far * near / (near - far),
   0,             0,             -1.0f,                       0
  });
  // clang-format on
}

inline Mat4 CreateOrtho(float left, float right, float top, float bottom,
                        float near, float far, bool GLCoord) {
  // clang-format off
  if (GLCoord) {
    return Mat4::FromRow({
      2.0f / (right - left),  0.0f,                   0.0f,                 (left + right) / (left - right),
      0.0f,                   2.0f / (top - bottom),  0.0f,                 (bottom + top) / (bottom - top),
      0.0f,                   0.0f,                  2.0f / (near - far), (near + far) / (far - near),
     0.0f,                  0.0f,                  0.0f,                1.0f,
    });
  } else {
    return Mat4::FromRow({
      2.0f / (right - left),  0.0f,                   0.0f,                 (left + right) / (left - right),
      0.0f,                  -2.0f / (top - bottom),  0.0f,                 (bottom + top) / (bottom - top),
      0.0f,                   0.0f,                  1.0f / (near - far), far/ (far - near),
     0.0f,                  0.0f,                  0.0f,                1.0f,
    });
  }
}
// clang-format on

inline Mat4 CreateTranslation(const Vec3 &position) {
  // clang-format off
  return Mat4::FromRow({
    1.0f, 0.0f, 0.0f, position.x,
    0.0f, 1.0f, 0.0f, position.y,
    0.0f, 0.0f,1.0f,position.z,
   0.0f,0.0f,0.0f,1.0f,
  });
  // clang-format on
}

inline Mat4 CreateZRotation(float radians) {
  float cos = std::cos(radians);
  float sin = std::sin(radians);
  // clang-format off
  return Mat4::FromRow({
    cos, -sin,   0.0f,  0.0f,
    sin,  cos,   0.0f,  0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
   0.0f,0.0f, 1.0f, 1.0f,
  });
  // clang-format on
}

inline Mat4 CreateYRotation(float radians) {
  float cos = std::cos(radians);
  float sin = std::sin(radians);
  // clang-format off
    return Mat4::FromRow({
        cos,  0.0f,  sin,  0.0f,
        0.0f, 1.0f,  0.0,  0.0f,
       -sin,  0.0f, cos, 0.0f,
       0.0f,0.0f, 0.0f,1.0f,
    });
  // clang-format on
}

inline Mat4 CreateXRotation(float radians) {
  float cos = std::cos(radians);
  float sin = std::sin(radians);
  // clang-format off
  return Mat4::FromRow({
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, cos,  sin,  0.0f,
    0.0f,-sin, cos, 0.0f,
   0.0f,0.0f,0.0f,1.0f
  });
  // clang-format on
}

inline Mat4 CreateXYZRotation(const Vec3 &r) {
  return CreateXRotation(r.x) * CreateYRotation(r.y) * CreateZRotation(r.z);
}

inline Mat2 CreateRotation2D(float radians) {
  auto cos = std::cos(radians);
  auto sin = std::sin(radians);
  return Mat2::FromRow({
      cos,
      -sin,
      sin,
      cos,
  });
}

inline Mat4 CreateScale(const Vec3 &scale) {
  // clang-format off
  return Mat4::FromRow({
  scale.x,  0.0,      0.0f,     0.0f,
  0.0f,     scale.y,  0.0f,     0.0f,
  0.0f,     0.0f,    scale.z, 0.0f,
 0.0f,    0.0f,    0.0f,    1.0f,
  });
  // clang-format on
}

template <typename T, typename U, uint32_t N, typename = MustArithmetic<U>>
Vec<T, N> LerpVec(const Vec<T, N> &left, const Vec<T, N> right, U value);

template <typename T, typename U, uint32_t N, typename>
Vec<T, N> LerpVec(const Vec<T, N> &left, const Vec<T, N> right, U value) {
  Vec<T, N> result;

  for (uint32_t i = 0; i < N; i++) {
    result.data[i] = (right.data[i] - left.data[i]) * value + left.data[i];
  }

  return result;
}
} // namespace Rasterization