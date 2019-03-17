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

inline const math::Transform& Camera::GetTransform() const
{
    return transform_;
}

inline void Camera::SetTransform(const math::Transform& i_transform)
{
    transform_ = i_transform;
}

inline const math::Vec3D& Camera::GetPosition() const
{
    return transform_.GetPosition();
}

inline void Camera::SetPosition(engine::math::Vec3D& i_position)
{
    transform_.SetPosition(i_position);
}

inline const math::Quaternion& Camera::GetRotation() const
{
    return transform_.GetRotation();
}

inline void Camera::SetRotation(engine::math::Quaternion& i_rotation)
{
    transform_.SetRotation(i_rotation);
}

} // namespace renderer
} // namespace engine

