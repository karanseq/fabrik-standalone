#ifndef MATH_UTIL_H_
#define MATH_UTIL_H_

// library includes
#include <cmath>

namespace engine {
namespace math {

// forward declarations
struct AABB;
class Euler;
class Mat44;
class Quaternion;
class Transform;
class Vec2D;
class Vec3D;
class Vec4D;

namespace optimized {
class Mat44;
class Vec3D;
}

constexpr double        PI = 3.14159265358979323846;
constexpr float         MIN_EPSILON = 1.0e-9f;
constexpr float         MAX_EPSILON = 1.0e-3f;

// Angles

inline float RadiansToDegrees(float i_radians)
{
    return (i_radians * 180.0f / float(PI));
}

inline float DegreesToRadians(float i_degrees)
{
    return (i_degrees * float(PI) / 180.0f);
}

inline float ClampAngleDegrees(float i_degrees)
{
    const float mod = std::fmod(i_degrees, 360.0f);
    return (mod < 0.0f ? mod + 360.0f : mod);
}

// Floats

inline bool IsNaN(float i_number)
{
    volatile float temp = i_number;
    return (temp != i_number);
}

inline bool FuzzyEquals(float i_lhs, float i_rhs, float i_epsilon = MAX_EPSILON)
{
    return std::fabs(i_rhs - i_lhs) < i_epsilon;
}

inline bool IsZero(float i_number)
{
    return FuzzyEquals(i_number, MIN_EPSILON);
}

template<typename T>
inline T Clamp(const T i_value, const T i_min, const T i_max)
{
    return (i_value < i_min ? i_min : (i_value > i_max ? i_max : i_value));
}

inline float GetMinOfFour(float i_first, float i_second, float i_third, float i_fourth)
{
    float first_two = i_first < i_second ? i_first : i_second;
    float last_two = i_third < i_fourth ? i_third : i_fourth;
    return first_two < last_two ? first_two : last_two;
}

inline float GetMaxOfFour(float i_first, float i_second, float i_third, float i_fourth)
{
    float first_two = i_first > i_second ? i_first : i_second;
    float last_two = i_third > i_fourth ? i_third : i_fourth;
    return first_two > last_two ? first_two : last_two;
}

// Dot product
float DotProduct(const Vec2D& i_v1, const Vec2D& i_v2);
float DotProduct(const Vec3D& i_v1, const Vec3D& i_v2);
float DotProduct(const engine::math::optimized::Vec3D& i_v1, const engine::math::optimized::Vec3D& i_v2);
float DotProduct(const Quaternion& i_q1, const Quaternion& i_q2);

// Cross product
Vec3D CrossProduct(const Vec3D& i_v1, const Vec3D& i_v2);
engine::math::optimized::Vec3D CrossProduct(const engine::math::optimized::Vec3D& i_v1, const engine::math::optimized::Vec3D& i_v2);

// Rotations
Vec3D RotateBy(const Vec3D& i_vector, const Quaternion& i_quat);
Vec3D RotateBy(const Vec3D& i_vector, const Euler& i_euler);

// Transforms
// the transform matrix as a result of this function must be left multiplied
// with the vector/point that will be transformed
void GetObjectToWorldTransform(const engine::math::Transform& i_transform, engine::math::Mat44& o_trans_mat);

} // namespace math
} // namespace engine

#endif // MATH_UTIL_H_

