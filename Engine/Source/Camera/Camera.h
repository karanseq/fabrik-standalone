#ifndef ENGINE_GRAPHICS_CAMERA_H_
#define ENGINE_GRAPHICS_CAMERA_H_

// Engine includes
#include "Math/Mat44.h"
#include "Math/MathUtil.h"
#include "Math/Transform.h"

// Forward declarations
namespace engine {
namespace math {
    class Quaternion;
    class Vec3D;
}
}

namespace engine {
namespace graphics {

class Camera
{
public:
    Camera() = default;
    ~Camera() = default;

    inline void Initialize( float i_fov = DEFAULT_FOV,
                            float i_aspect_ratio = DEFAULT_ASPECT_RATIO,
                            float i_near_plane = DEFAULT_NEAR_PLANE, 
                            float i_far_plane = DEFAULT_FAR_PLANE);

    inline void SetFOV(float i_fov);
    inline void SetAspectRatio(float i_aspect_ratio);
    inline void SetNearPlane(float i_near_plane);
    inline void SetFarPlane(float i_far_plane);

    inline const math::Mat44& GetPerspectiveProjection() const;

    inline const math::Transform& GetTransform() const;
    inline void SetTransform(const math::Transform& i_transform);

    inline const math::Vec3D& GetPosition() const;
    inline void SetPosition(engine::math::Vec3D& i_position);

    inline const math::Quaternion& GetRotation() const;
    inline void SetRotation(engine::math::Quaternion& i_rotation);

    static constexpr float DEFAULT_FOV = float(math::PI) * 0.25f;
    static constexpr float DEFAULT_ASPECT_RATIO = 1.0f;
    static constexpr float DEFAULT_NEAR_PLANE = 0.1f;
    static constexpr float DEFAULT_FAR_PLANE = 1000.0f;

private:
    void RecomputeProjection();

private:
    math::Mat44         perspective_projection_;
    math::Transform     transform_;
    float               fov_ = DEFAULT_FOV;
    float               aspect_ratio_ = DEFAULT_ASPECT_RATIO;
    float               near_plane_ = DEFAULT_NEAR_PLANE;
    float               far_plane_ = DEFAULT_FAR_PLANE;
};

} // namespace graphics
} // namespace engine

#include "Camera-inl.h"

#endif // ENGINE_GRAPHICS_CAMERA_H_