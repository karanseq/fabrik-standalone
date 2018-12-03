#ifndef INPUT_TYPES_H_
#define INPUT_TYPES_H_

// Library includes
#include <cstdint>

namespace engine {
namespace input {

enum class InputType : uint8_t
{
    INPUT_TYPE_KEYBOARD,
    INPUT_TYPE_MOUSE
};

} // namespace input
} // namespace engine

#endif // INPUT_TYPES_H_