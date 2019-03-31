#include "Math/MathUtil.h"

// engine includes
#include "Assert/Assert.h"
#include "Math/Euler.h"
#include "Math/AABB.h"
#include "Math/Mat44.h"
#include "Math/Quaternion.h"
#include "Math/Transform.h"
#include "Math/Vec2D.h"
#include "Math/Vec3D.h"

namespace engine {
namespace math {

// Dot product

float DotProduct(const Vec2D& i_v1, const Vec2D& i_v2)
{
    return (i_v1.x() * i_v2.x() + i_v1.y() * i_v2.y());
}

float DotProduct(const Vec3D& i_v1, const Vec3D& i_v2)
{
    return (i_v1.x() * i_v2.x() + i_v1.y() * i_v2.y() + i_v1.z() * i_v2.z());
}

float DotProduct(const Quaternion& i_q1, const Quaternion& i_q2)
{
    return (i_q1.w() * i_q2.w() + i_q1.x() * i_q2.x() + i_q1.y() * i_q2.y() + i_q1.z() * i_q2.z());
}

// Cross product

Vec3D CrossProduct(const Vec3D& i_v1, const Vec3D& i_v2)
{
    return Vec3D(i_v1.y() * i_v2.z() - i_v1.z() * i_v2.y(),
        i_v1.z() * i_v2.x() - i_v1.x() * i_v2.z(),
        i_v1.x() * i_v2.y() - i_v1.y() * i_v2.x());
}

// Rotations

Vec3D RotateBy(const Vec3D& i_vector, const Quaternion& i_quat)
{
    // http://people.csail.mit.edu/bkph/articles/Quaternions.pdf
    // V' = V + 2w(Q x V) + (2Q x (Q x V))
    // refactor:
    // V' = V + w(2(Q x V)) + (Q x (2(Q x V)))
    // T = 2(Q x V);
    // V' = V + w*(T) + (Q x T)

    const Vec3D quat(i_quat.x(), i_quat.y(), i_quat.z());
    const Vec3D t = CrossProduct(quat, i_vector) * 2.0f;
    const Vec3D v = i_vector + (t * i_quat.w()) + CrossProduct(quat, t);
    return v;
}

Vec3D RotateBy(const Vec3D& i_vector, const Euler& i_euler)
{
    const Vec4D rotated = Mat44::GetRotation(i_euler).MultiplyLeft(Vec4D(i_vector));
    return Vec3D(rotated.x(), rotated.y(), rotated.z());
}

void GetObjectToWorldTransform(const engine::math::Transform& i_transform, engine::math::Mat44& o_trans_mat)
{
    o_trans_mat = engine::math::Mat44(i_transform.GetRotation(), i_transform.GetPosition());
}

} // namespace math
} // namespace engine