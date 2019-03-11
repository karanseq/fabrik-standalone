#include "Graphics/Program.h"

// Engine includes
#include "Assert/Assert.h"
#include "Data/PooledString.h"
#include "Graphics/Shader.h"
#include "Math/Mat44.h"
#include "Math/Vec4D.h"
#include "Math/Vec3D.h"
#include "Memory/AllocatorOverrides.h"
#include "Memory/UniquePointer.h"
#include "Util/FileUtils.h"

namespace engine {
namespace graphics {

bool Program::Initialize(const engine::data::PooledString& i_vertex_shader_path, const engine::data::PooledString& i_fragment_shader_path)
{
    Shader vertex_shader(Shader::ShaderType::VERTEX);
    if (vertex_shader.Initialize(i_vertex_shader_path) == false)
    {
        return false;
    }

    Shader fragment_shader(Shader::ShaderType::FRAGMENT);
    if (fragment_shader.Initialize(i_fragment_shader_path) == false)
    {
        return false;
    }

    return Initialize(vertex_shader, fragment_shader);
}

bool Program::Initialize(const Shader& i_vertex_shader, const Shader& i_fragment_shader)
{
    // Get a program handle
    GLuint program_id = glCreateProgram();

    // Attach the shaders
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
    ASSERT(program_id_ != 0);
    glUseProgram(program_id_);
    ASSERT(glGetError() == GL_NO_ERROR);
}

void Program::SetUniform(const char* i_uniform_name, const engine::math::Mat44& i_matrix) const
{
    static constexpr GLsizei        count = 1;
    static constexpr GLboolean      transpose = GL_TRUE;

    glUseProgram(program_id_);
    const GLint id = glGetUniformLocation(program_id_, reinterpret_cast<const GLchar*>(i_uniform_name));
    glUniformMatrix4fv(id, count, transpose, reinterpret_cast<const GLfloat*>(&i_matrix));
    ASSERT(glGetError() == GL_NO_ERROR);
}

void Program::SetUniform(const char* i_uniform_name, const engine::math::Vec4D& i_vector) const
{
    glUseProgram(program_id_);
    const GLint id = glGetUniformLocation(program_id_, reinterpret_cast<const GLchar*>(i_uniform_name));
    glUniform4f(id, i_vector.x(), i_vector.y(), i_vector.z(), i_vector.w());
    ASSERT(glGetError() == GL_NO_ERROR);
}

void Program::SetUniform(const char* i_uniform_name, const engine::math::Vec3D& i_vector) const
{
    glUseProgram(program_id_);
    const GLint id = glGetUniformLocation(program_id_, reinterpret_cast<const GLchar*>(i_uniform_name));
    glUniform3f(id, i_vector.x(), i_vector.y(), i_vector.z());
    ASSERT(glGetError() == GL_NO_ERROR);
}

void Program::SetUniform(const char* i_uniform_name, const float i_value) const
{
    glUseProgram(program_id_);
    const GLint id = glGetUniformLocation(program_id_, reinterpret_cast<const GLchar*>(i_uniform_name));
    glUniform1f(id, i_value);
    ASSERT(glGetError() == GL_NO_ERROR);
}

void Program::SetUniform(const char* i_uniform_name, const uint32_t i_value) const
{
    glUseProgram(program_id_);
    const GLint id = glGetUniformLocation(program_id_, reinterpret_cast<const GLchar*>(i_uniform_name));
    glUniform1ui(id, i_value);
    ASSERT(glGetError() == GL_NO_ERROR);
}

void Program::SetUniform(const char* i_uniform_name, const int32_t i_value) const
{
    glUseProgram(program_id_);
    const GLint id = glGetUniformLocation(program_id_, reinterpret_cast<const GLchar*>(i_uniform_name));
    glUniform1i(id, i_value);
    ASSERT(glGetError() == GL_NO_ERROR);
}

} // namespace graphics
} // namespace engine