#include "Graphics/Program.h"

// Engine includes
#include "Graphics/Shader.h"
#include "Graphics/ShaderBuilder.h"
#include "Memory/AllocatorOverrides.h"
#include "Memory/UniquePointer.h"

namespace engine {
namespace graphics {

bool Program::Initialize(const Shader& i_vertex_shader, const Shader& i_fragment_shader)
{
    // Get a program handle
    GLuint program_id = glCreateProgram();

    // Attached the shaders
    glAttachShader(program_id, i_vertex_shader.GetShaderID());
    glAttachShader(program_id, i_fragment_shader.GetShaderID());

    // Link the program
    glLinkProgram(program_id);

    // Check for link errors
    GLint link_status = 0;
    glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE)
    {
        GLint log_length = 0;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);
        if (log_length > 0)
        {
            memory::UniquePointer<GLchar> info_log = static_cast<GLchar*>(memory::Malloc(log_length));
            GLint log_length_generated = 0;
            glGetProgramInfoLog(program_id, log_length, &log_length_generated, info_log.Get());

            glDeleteProgram(program_id);
            LOG_ERROR("Failed to link program!\n%s", static_cast<char*>(info_log.Get()));
        }
        return false;
    }

    glDetachShader(program_id, i_vertex_shader.GetShaderID());
    glDetachShader(program_id, i_fragment_shader.GetShaderID());

    program_id_ = program_id;

    return true;
}

void Program::Bind() const
{

}

} // namespace graphics
} // namespace engine