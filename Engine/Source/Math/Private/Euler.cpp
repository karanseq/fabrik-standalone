#include "Math/Euler.h"

// Engine includes
#include "Assert/Assert.h"
#include "Math/MathUtil.h"
#include "Math/Quaternion.h"

namespace engine {
namespace math {

Euler::Euler(float i_degrees) : yaw_(i_degrees),
    pitch_(i_degrees),
    roll_(i_degrees)
{
    ASSERT(!IsNaN(yaw_) && !IsNaN(pitch_) && !IsNaN(roll_));
}

Euler::Euler(float i_yaw, float i_pitch, float i_roll) : yaw_(i_yaw),
    pitch_(i_pitch),
    roll_(i_roll)
{
    ASSERT(!IsNaN(yaw_) && !IsNaN(pitch_) && !IsNaN(roll_));
}

Euler::Euler(const Quaternion& i_quat)
{
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/

    static constexpr float singularity_threshold = 0.499f;
    const float singularity_test = i_quat.x() * i_quat.y() + i_quat.z() * i_quat.w();

    if (singularity_test > singularity_threshold)
    {
        yaw_    = 2.0f * std::atan2f(i_quat.x(), i_quat.w());
        pitch_  = 0.0f;
        roll_   = float(PI / 2);
    }
    else if (singularity_test < -singularity_threshold)
    {
        yaw_    = -2.0f * std::atan2f(i_quat.x(), i_quat.w());
        pitch_  = 0.0f;
        roll_   = float(PI / 2);
    }
    else
    {
        const float xsq = i_quat.x() * i_quat.x();
        const float ysq = i_quat.y() * i_quat.y();
        const float zsq = i_quat.z() * i_quat.z();
        yaw_    = std::atan2f(2 * i_quat.y() * i_quat.w() - 2 * i_quat.x() * i_quat.z(), 1 - 2 * ysq - 2 * zsq);
        pitch_  = std::atan2f(2 * i_quat.x() * i_quat.w() - 2 * i_quat.y() * i_quat.z(), 1 - 2 * xsq - 2 * zsq);
        roll_   = std::asinf(2 * singularity_test);
    }

    yaw_    = RadiansToDegrees(yaw_);
    pitch_  = RadiansToDegrees(pitch_);
    roll_   = RadiansToDegrees(roll_);

    ASSERT(!IsNaN(yaw_) && !IsNaN(pitch_) && !IsNaN(roll_));
}

} // namespace math
} // namespace engine
