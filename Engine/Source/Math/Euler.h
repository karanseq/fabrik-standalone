#ifndef ENGINE_MATH_EULER_H_
#define ENGINE_MATH_EULER_H_

namespace engine {
namespace math {

// Forward declarations
class Quaternion;

/*
Euler
- A class that represents rotations around the X (pitch), Y (yaw) and Z (roll) axes.
- Rotations are in degrees.
*/

class Euler
{
public:
    Euler() = default;
    explicit Euler(float i_degrees);
    explicit Euler(float i_yaw, float i_pitch, float i_roll);
    explicit Euler(const Quaternion& i_quat);

    ~Euler() = default;

    // Accessors and mutators
    inline float Yaw() const;
    inline void Yaw(float i_yaw);
    inline float Pitch() const;
    inline void Pitch(float i_pitch);
    inline float Roll() const;
    inline float Roll(float i_roll);
    inline void Set(float i_yaw, float i_pitch, float i_roll);

    // Arithmetic
    inline Euler operator+(const Euler& i_other) const;
    inline Euler& operator+=(const Euler& i_other);
    inline Euler operator-(const Euler& i_other) const;
    inline Euler& operator-(const Euler& i_other);
    inline Euler operator*(float i_scale) const;
    inline Euler& operator*=(float i_scale);

    // Relational
    inline bool operator==(const Euler& i_other) const;
    inline bool operator!=(const Euler& i_other) const;

    // Functions
    inline bool IsZero() const;
    inline void Normalize();
    inline Euler GetNormalized() const;

    // Constants

private:
    float yaw_ = 0.0f;
    float pitch_ = 0.0f;
    float roll_ = 0.0f;

}; // class Euler

} // namespace math
} // namespace engine

#include "Euler-inl.h"

#endif // ENGINE_MATH_EULER_H_
