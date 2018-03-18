#include "Transform.h"

namespace engine {
namespace math {

    inline Transform& Transform::operator=(const Transform& i_transform)
    {
        // check for self assignment
        if (this != &i_transform)
        {
            position_ = i_transform.position_;
            rotation_ = i_transform.rotation_;
            scale_ = i_transform.scale_;
        }
        return *this;
    }

    inline const Quaternion& Transform::GetRotation() const
    {
        return rotation_;
    }

    inline void Transform::SetRotation(const Quaternion& i_rotation)
    {
        rotation_ = i_rotation;
    }

    inline const Vec3D& Transform::GetPosition() const
    {
        return position_;
    }

    inline void Transform::SetPosition(const Vec3D& i_position)
    {
        position_ = i_position;
    }

    inline float Transform::GetScale() const
    {
        return scale_;
    }

    inline void Transform::SetScale(float i_scale)
    {
        scale_ = i_scale;
    }

} // namespace math
} // namespace engine