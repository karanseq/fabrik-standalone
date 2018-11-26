#include "Graphics\ShaderBuilder.h"

// Library includes

// Engine includes
#include "Memory\AllocatorOverrides.h"
#include "Memory\UniquePointer.h"

namespace engine {
namespace graphics {

bool ShaderBuilder::BuildShader(GLuint& o_shader, GLenum i_shader_type, const char* i_shader_source)
{
    ASSERT(i_shader_source);

    switch (i_shader_type)
    {
    case GL_VERTEX_SHADER:
    case GL_FRAGMENT_SHADER:
        break;
    default:
        LOG_ERROR("Incorrect shader type:%d passed to %s", i_shader_type, __FUNCTION__);
        return false;
        break;
    }

    // Create an empty shader handle
    o_shader = glCreateShader(i_shader_type);

    // Send the shader code to GL
    const GLchar* source = static_cast<const GLchar*>(i_shader_source);
    glShaderSource(o_shader, /*count =*/ 1, &source, /*length =*/ 0);

    // Compile the shader
    glCompileShader(o_shader);

    // Check for compile errors
    GLint compile_status = 0;
    glGetShaderiv(o_shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        // Get information from the log
        GLint log_length = 0;
        glGetShaderiv(o_shader, GL_INFO_LOG_LENGTH, &log_length);
        if (log_length > 0)
        {
            memory::UniquePointer<GLchar> info_log = static_cast<GLchar*>(memory::Malloc(log_length));
            GLint log_length_generated = 0;
            glGetShaderInfoLog(o_shader, log_length, &log_length_generated, info_log.Get());

            glDeleteShader(o_shader);
            LOG_ERROR("Failed to compile shader!\n%s", static_cast<char*>(info_log.Get()));
        }
        return false;
    }

    return true;
}

bool ShaderBuilder::LinkProgram(GLuint& o_program, GLuint i_vertex_shader, GLuint i_fragment_shader)
{
    // Get a program handle
    o_program = glCreateProgram();

    // Attached the shaders
    glAttachShader(o_program, i_vertex_shader);
    glAttachShader(o_program, i_fragment_shader);

    // Link the program
    glLinkProgram(o_program);

    // Check for link errors
    GLint link_status = 0;
    glGetProgramiv(o_program, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE)
    {
        GLint log_length = 0;
        glGetProgramiv(o_program, GL_INFO_LOG_LENGTH, &log_length);
        if (log_length > 0)
        {
            memory::UniquePointer<GLchar> info_log = static_cast<GLchar*>(memory::Malloc(log_length));
            GLint log_length_generated = 0;
            glGetProgramInfoLog(o_program, log_length, &log_length_generated, info_log.Get());

            glDeleteProgram(o_program);
            LOG_ERROR("Failed to link program!\n%s", static_cast<char*>(info_log.Get()));
        }
        return false;
    }

    glDetachShader(o_program, i_vertex_shader);
    glDetachShader(o_program, i_fragment_shader);

    return true;
}

} // namespace graphics
} // namespace engine
