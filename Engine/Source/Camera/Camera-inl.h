#include "Camera.h"

namespace engine {
namespace graphics {

inline void Camera::Initialize(float i_fov, float i_aspect_ratio, float i_near_plane, float i_far_plane)
{
    fov_ = i_fov;
    aspect_ratio_ = i_aspect_ratio;
    near_plane_ = i_near_plane;
    far_plane_ = i_far_plane;
    RecomputeProjection();
}

inline void Camera::SetFOV(float i_fov)
{
    fov_ = i_fov;
    RecomputeProjection();
}

inline void Camera::SetAspectRatio(float i_aspect_ratio)
{
    aspect_ratio_ = i_aspect_ratio;
    RecomputeProjection();
}

inline void Camera::SetNearPlane(float i_near_plane)
{
    near_plane_ = i_near_plane;
    RecomputeProjection();
}

inline void Camera::SetFarPlane(float i_far_plane)
{
    far_plane_ = i_far_plane;
    RecomputeProjection();
}

inline const math::Mat44& Camera::GetPerspectiveProjection() const
{
    return perspective_projection_;
}

inline const math::Vec3D& Camera::GetPosition() const
{
    return position_;
}

inline void Camera::SetPosition(math::Vec3D& i_position)
{
    position_ = i_position;
}

inline const math::Quaternion& Camera::GetRotation() const
{
    return rotation_;
}

inline void Camera::SetRotation(math::Quaternion& i_rotation)
{
    rotation_ = i_rotation;
}

} // namespace graphics
} // namespace engine
