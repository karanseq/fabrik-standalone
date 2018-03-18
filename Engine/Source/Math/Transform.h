#ifndef ENGINE_TRANSFORM_H_
#define ENGINE_TRANSFORM_H_

#include "Quaternion.h"
#include "Vec3D.h"

namespace engine {
namespace math {

    /*
        Transform
        - A class that represents the position, scale and rotation of an object in 3D space
    */

    class Transform
    {
    public:
        explicit Transform(const Quaternion& i_rotation = Quaternion::IDENTITY,
            const Vec3D& i_position = Vec3D::ZERO,
            float i_scale = 1.0f);
        Transform(const Transform& i_copy);

        ~Transform() = default;

        // assignment
        inline Transform& operator=(const Transform& i_transform);

        // accessors and mutators
        inline const Quaternion& GetRotation() const;
        inline void SetRotation(const Quaternion& i_rotation);
        inline const Vec3D& GetPosition() const;
        inline void SetPosition(const Vec3D& i_position);
        inline float GetScale() const;
        inline void SetScale(float i_scale);

        // constants
        static const Transform          ZERO;

    protected:
        Quaternion                      rotation_;
        Vec3D                           position_;
        float                           scale_;

    }; // class Transform

} // namespace math
} // namespace engine

#include "Transform-inl.h"

#endif // ENGINE_TRANSFORM_H_
