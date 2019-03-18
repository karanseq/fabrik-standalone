#include "Camera/Camera.h"

// System includes
#include <cmath>

namespace engine {
namespace graphics {

void Camera::RecomputeProjection()
{
    const float y_scale = 1.0f / std::tan(fov_ * 0.5f);
    const float x_scale = y_scale / aspect_ratio_;
    const float z_diff_inverse = 1.0f / (near_plane_ - far_plane_);
    perspective_projection_.Set(x_scale, 0.0f, 0.0f, 0.0f,
        0.0f, y_scale, 0.0f, 0.0f,
        0.0f, 0.0f, (near_plane_ + far_plane_) * z_diff_inverse, (2.0f * near_plane_ * far_plane_) * z_diff_inverse,
        0.0f, 0.0f, -1.0f, 0.0f);
}

} // namespace graphics
} // namespace engine
