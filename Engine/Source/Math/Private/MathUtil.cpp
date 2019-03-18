#include "Math/MathUtil.h"

// engine includes
#include "Assert/Assert.h"
#include "Math/AABB.h"
#include "Math/Mat44.h"
#include "Math/Quaternion.h"
#include "Math/Transform.h"
#include "Math/Vec2D.h"
#include "Math/Vec3D.h"

namespace engine {
namespace math {

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

Vec3D CrossProduct(const Vec3D& i_v1, const Vec3D& i_v2)
{
    return Vec3D(i_v1.y() * i_v2.z() - i_v1.z() * i_v2.y(),
        i_v1.z() * i_v2.x() - i_v1.x() * i_v2.z(),
        i_v1.x() * i_v2.y() - i_v1.y() * i_v2.x());
}

void GetObjectToWorldTransform(const engine::math::Transform& i_transform, engine::math::Mat44& o_trans_mat)
{
    o_trans_mat = engine::math::Mat44(i_transform.GetRotation(), i_transform.GetPosition());
}

} // namespace math
} // namespace engine