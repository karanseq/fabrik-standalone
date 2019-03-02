#include "Shader.h"

namespace engine {
namespace graphics {

inline Shader::ShaderType Shader::GetType() const
{
    return type_;
}

inline GLuint Shader::GetShaderID() const
{
    return shader_id_;
}

inline GLenum Shader::GetGLShaderType(ShaderType i_type) const
{
    return i_type == ShaderType::VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
}

} // namespace graphics
} // namespace engine
