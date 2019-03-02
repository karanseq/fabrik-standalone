#include "Program.h"

namespace engine {
namespace graphics {

inline GLuint Program::GetProgramID() const
{
    return program_id_;
}

} // namespace graphics
} // namespace engine