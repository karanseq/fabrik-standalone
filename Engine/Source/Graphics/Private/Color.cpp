// Include Files
//==============

#include "Graphics/Color.h"

// System includes
#include <cmath>

// Engine includes
#include "Assert/Assert.h"
#include "Math/MathUtil.h"

namespace engine {
namespace graphics {

// Static Data Initialization
//===========================

const Color Color::BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const Color Color::BLUE(0.0f, 0.0f, 1.0f, 1.0f);
const Color Color::CYAN(0.0f, 1.0f, 1.0f, 1.0f);
const Color Color::EMERALD(0.18039f, 0.8f, 0.44314f, 1.0f);
const Color Color::GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const Color Color::MAGENTA(1.0f, 0.0f, 1.0f, 1.0f);
const Color Color::ORANGE(0.95294f, 0.61176f, 0.07059f, 1.0f);
const Color Color::PURPLE(0.66275f, 0.02745f, 0.89412f, 1.0f);
const Color Color::RED(1.0f, 0.0f, 0.0f, 1.0f);
const Color Color::SILVER(0.74118f, 0.76471f, 0.78039f, 1.0f);
const Color Color::TURQUOISE(0.10196f, 0.73725f, 0.61176f, 1.0f);
const Color Color::WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const Color Color::YELLOW(1.0f, 1.0f, 0.0f, 1.0f);

// Initialization / Shut Down
//---------------------------

Color::Color(const float i_r, const float i_g, const float i_b, const float i_a)
	: 
	r(engine::math::Clamp(i_r, 0.0f, 1.0f)), 
	g(engine::math::Clamp(i_g, 0.0f, 1.0f)),
	b(engine::math::Clamp(i_b, 0.0f, 1.0f)),
	a(engine::math::Clamp(i_a, 0.0f, 1.0f))
{}

// Interface
//==========

// Addition
//---------

Color Color::operator+(const Color& i_rhs) const
{
	return Color(r + i_rhs.r, g + i_rhs.g, b + i_rhs.b, a + i_rhs.a);
}

Color& Color::operator+=(const Color& i_rhs)
{
	r = engine::math::Clamp(r + i_rhs.r, 0.0f, 1.0f);
	g = engine::math::Clamp(g + i_rhs.g, 0.0f, 1.0f);
	b = engine::math::Clamp(b + i_rhs.b, 0.0f, 1.0f);
	a = engine::math::Clamp(a + i_rhs.a, 0.0f, 1.0f);
	return *this;
}

// Subtraction
//------------

Color Color::operator-(const Color& i_rhs) const
{
	return Color(r - i_rhs.r, g - i_rhs.g, b - i_rhs.b, a - i_rhs.a);
}

Color& Color::operator-=(const Color& i_rhs)
{
	r = engine::math::Clamp(r - i_rhs.r, 0.0f, 1.0f);
	g = engine::math::Clamp(g - i_rhs.g, 0.0f, 1.0f);
	b = engine::math::Clamp(b - i_rhs.b, 0.0f, 1.0f);
	a = engine::math::Clamp(a - i_rhs.a, 0.0f, 1.0f);
	return *this;
}

// Multiplication
//---------------

Color Color::operator*(const Color& i_rhs) const
{
	return Color(r * i_rhs.r, g * i_rhs.g, b * i_rhs.b, a * i_rhs.a);
}

Color& Color::operator*=(const Color& i_rhs)
{
	r = engine::math::Clamp(r * i_rhs.r, 0.0f, 1.0f);
	g = engine::math::Clamp(g * i_rhs.g, 0.0f, 1.0f);
	b = engine::math::Clamp(b * i_rhs.b, 0.0f, 1.0f);
	a = engine::math::Clamp(a * i_rhs.a, 0.0f, 1.0f);
	return *this;
}

Color Color::operator*(const float i_scalar) const
{
	return Color(r * i_scalar, g * i_scalar, b * i_scalar, a * i_scalar);
}

Color& Color::operator*=(const float i_scalar)
{
	r = engine::math::Clamp(r * i_scalar, 0.0f, 1.0f);
	g = engine::math::Clamp(g * i_scalar, 0.0f, 1.0f);
	b = engine::math::Clamp(b * i_scalar, 0.0f, 1.0f);
	a = engine::math::Clamp(a * i_scalar, 0.0f, 1.0f);
	return *this;
}

// Division
//---------

Color Color::operator/(const Color& i_rhs) const
{
	ASSERT(std::abs(i_rhs.r) > engine::math::MIN_EPSILON);//, "Can't divide by zero");
	ASSERT(std::abs(i_rhs.g) > engine::math::MIN_EPSILON);//, "Can't divide by zero");
	ASSERT(std::abs(i_rhs.b) > engine::math::MIN_EPSILON);//, "Can't divide by zero");
	ASSERT(std::abs(i_rhs.a) > engine::math::MIN_EPSILON);//, "Can't divide by zero");
	return Color(r / i_rhs.r, g / i_rhs.g, b / i_rhs.b, a / i_rhs.a);
}

Color& Color::operator/=(const Color& i_rhs)
{
	ASSERT(std::abs(i_rhs.r) > engine::math::MIN_EPSILON);//, "Can't divide by zero");
	ASSERT(std::abs(i_rhs.g) > engine::math::MIN_EPSILON);//, "Can't divide by zero");
	ASSERT(std::abs(i_rhs.b) > engine::math::MIN_EPSILON);//, "Can't divide by zero");
	ASSERT(std::abs(i_rhs.a) > engine::math::MIN_EPSILON);//, "Can't divide by zero");
	r = engine::math::Clamp(r / i_rhs.r, 0.0f, 1.0f);
	g = engine::math::Clamp(g / i_rhs.g, 0.0f, 1.0f);
	b = engine::math::Clamp(b / i_rhs.b, 0.0f, 1.0f);
	a = engine::math::Clamp(a / i_rhs.a, 0.0f, 1.0f);
	return *this;
}

Color Color::operator/(const float i_scalar) const
{
	ASSERT(std::abs(i_scalar) > engine::math::MIN_EPSILON);//, "Can't divide by zero");
	float inverseScalar = 1.0f / i_scalar;
	return Color(r * inverseScalar, g * inverseScalar, b * inverseScalar, a * inverseScalar);
}

Color& Color::operator/=(const float i_scalar)
{
	ASSERT(std::abs(i_scalar) > engine::math::MIN_EPSILON);//, "Can't divide by zero");
	float inverseScalar = 1.0f / i_scalar;
	r = engine::math::Clamp(r * inverseScalar, 0.0f, 1.0f);
	g = engine::math::Clamp(g * inverseScalar, 0.0f, 1.0f);
	b = engine::math::Clamp(b * inverseScalar, 0.0f, 1.0f);
	a = engine::math::Clamp(a * inverseScalar, 0.0f, 1.0f);
	return *this;
}

// Comparison
//-----------

bool Color::operator==(const Color& i_rhs) const
{
	return (r == i_rhs.r) & (g == i_rhs.g) & (b == i_rhs.b) & (a == i_rhs.a);
}

bool Color::operator!=(const Color& i_rhs) const
{
	return (r != i_rhs.r) | (g != i_rhs.g) | (b != i_rhs.b) | (a != i_rhs.a);
}

} // namespace graphics
} // namespace engine
