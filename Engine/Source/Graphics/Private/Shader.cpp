#include "Graphics/Shader.h"

// Engine includes
#include "Assert/Assert.h"
#include "Graphics/ShaderBuilder.h"
#include "Logger/Logger.h"
#include "Memory/AllocatorOverrides.h"
#include "Memory/UniquePointer.h"
#include "Util/FileUtils.h"

namespace engine {
namespace graphics {

Shader::Shader(const ShaderType i_type) :
    type_(i_type)
{
    ASSERT(type_ != ShaderType::INVALID);
}

bool Shader::Initialize(const engine::data::PooledString& i_file_path)
{
    const engine::util::FileUtils::FileData shader_data = engine::util::FileUtils::Get()->ReadFile(i_file_path);
    if (shader_data.file_size == 0)
    {
        LOG_ERROR("Failed to read shader file:%s", i_file_path.GetString());
        return false;
    }

    // Create an empty shader handle
    GLuint shader_id = glCreateShader(GetGLShaderType(type_));

    // Send the shader code to GL
    const GLchar* source = reinterpret_cast<const GLchar*>(shader_data.file_contents);
    glShaderSource(shader_id, /*count =*/ 1, &source, /*length =*/ 0);

    // Compile the shader
    glCompileShader(shader_id);

    // Check for compile errors
    GLint compile_status = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        // Get information from the log
        GLint log_length = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
        if (log_length > 0)
        {
            memory::UniquePointer<GLchar> info_log = static_cast<GLchar*>(memory::Malloc(log_length));
            GLint log_length_generated = 0;
            glGetShaderInfoLog(shader_id, log_length, &log_length_generated, info_log.Get());

            glDeleteShader(shader_id);
            LOG_ERROR("Failed to compile shader!\n%s", static_cast<char*>(info_log.Get()));
        }
        return false;
    }

    shader_id_ = shader_id;

    return true;
}

} // namespace graphics
} // namespace engine
