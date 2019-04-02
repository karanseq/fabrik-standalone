#include "Euler.h"

// Engine includes
#include "Assert/Assert.h"
#include "Math/MathUtil.h"

namespace engine {
namespace math {

// Accessors and mutators
inline float Euler::Yaw() const
{
    return yaw_;
}

inline void Euler::Yaw(float i_yaw)
{
    ASSERT(!IsNaN(i_yaw));
    yaw_ = i_yaw;
}

inline float Euler::Pitch() const
{
    return pitch_;
}

inline void Euler::Pitch(float i_pitch)
{
    ASSERT(!IsNaN(i_pitch));
    pitch_ = i_pitch;
}

inline float Euler::Roll() const
{
    return roll_;
}

inline void Euler::Roll(float i_roll)
{
    ASSERT(!IsNaN(i_roll));
    roll_ = i_roll;
}

inline void Euler::Set(float i_yaw, float i_pitch, float i_roll)
{
    ASSERT(!IsNaN(i_yaw) && !IsNaN(i_pitch) && !IsNaN(i_roll));
    yaw_ = i_yaw;
    pitch_ = i_pitch;
    roll_ = i_roll;
}

// Arithmetic
inline Euler Euler::operator+(const Euler& i_other) const
{
    return Euler(yaw_ + i_other.Yaw(), pitch_ + i_other.Pitch(), roll_ + i_other.Roll());
}

inline Euler& Euler::operator+=(const Euler& i_other)
{
    Yaw(yaw_ + i_other.Yaw());
    Pitch(pitch_ + i_other.Pitch());
    Roll(roll_ + i_other.Roll());
    return *this;
}

inline Euler Euler::operator-(const Euler& i_other) const
{
    return Euler(yaw_ - i_other.Yaw(), pitch_ - i_other.Pitch(), roll_ - i_other.Roll());
}

inline Euler& Euler::operator-(const Euler& i_other)
{
    Yaw(yaw_ - i_other.Yaw());
    Pitch(pitch_ - i_other.Pitch());
    Roll(roll_ - i_other.Roll());
    return *this;
}

inline Euler Euler::operator*(float i_scale) const
{
    ASSERT(!IsNaN(i_scale));
    return Euler(yaw_ * i_scale, pitch_ * i_scale, roll_ * i_scale);
}

inline Euler& Euler::operator*=(float i_scale)
{
    ASSERT(!IsNaN(i_scale));
    Set(yaw_ * i_scale, pitch_ * i_scale, roll_ * i_scale);
    return *this;
}

// Relational
inline bool Euler::operator==(const Euler& i_other) const
{
    return FuzzyEquals(yaw_, i_other.Yaw()) && FuzzyEquals(pitch_, i_other.Pitch()) && FuzzyEquals(roll_, i_other.Roll());
}

inline bool Euler::operator!=(const Euler& i_other) const
{
    return !FuzzyEquals(yaw_, i_other.Yaw()) || !FuzzyEquals(pitch_, i_other.Pitch()) || !FuzzyEquals(roll_, i_other.Roll());
}

// Functions
inline bool Euler::IsZero() const
{
    return (FuzzyEquals(yaw_, 0.0f) && FuzzyEquals(pitch_, 0.0f) && FuzzyEquals(roll_, 0.0f));
}

inline void Euler::Normalize()
{
    yaw_    = ClampAngleDegrees(yaw_);
    pitch_  = ClampAngleDegrees(pitch_);
    roll_   = ClampAngleDegrees(roll_);
    ASSERT(!IsNaN(yaw_) && !IsNaN(pitch_) && !IsNaN(roll_));
}

inline Euler Euler::GetNormalized() const
{
    return Euler(ClampAngleDegrees(yaw_), ClampAngleDegrees(pitch_), ClampAngleDegrees(roll_));
}

} // namespace math
} // namespace engine
