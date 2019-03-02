#ifndef ENGINE_PROGRAM_H_
#define ENGINE_PROGRAM_H_

// Library includes
#include <GL/glew.h>

namespace engine {
namespace graphics {

// Forward declarations
class Shader;

class Program
{
public:
    Program() = default;
    ~Program() = default;

    bool Initialize(const Shader& i_vertex_shader, const Shader& i_fragment_shader);
    void Bind() const;

    inline GLuint GetProgramID() const;

private:
    GLuint program_id_ = 0;

}; // class Program

} // namespace graphics
} // namespace engine

#include "Program-inl.h"

#endif // ENGINE_PROGRAM_H_
