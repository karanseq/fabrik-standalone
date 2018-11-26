#ifndef SHADER_BUILDER_H_
#define SHADER_BUILDER_H_

// Library includes
#include <GL\glew.h>

namespace engine {
namespace graphics {

class ShaderBuilder
{
public:
    static bool BuildShader(GLuint& o_shader, GLenum i_shader_type, const char* i_shader_source);
    static bool LinkProgram(GLuint& o_program, GLuint i_vertex_shader, GLuint i_fragment_shader);

private:
    ShaderBuilder() = delete;
    ~ShaderBuilder() = delete;

    ShaderBuilder(const ShaderBuilder&) = delete;
    ShaderBuilder& operator=(const ShaderBuilder&) = delete;

}; // class ShaderBuilder

} // namespace graphics
} // namespace engine

#endif // SHADER_BUILDER_H_
