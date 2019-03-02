#ifndef ENGINE_SHADER_H_
#define ENGINE_SHADER_H_

// System includes
#include <stdint.h>

// Library includes
#include <GL/glew.h>

namespace engine {

// Forward declarations
namespace data {
    class PooledString;
}

namespace graphics {

class Shader
{
public:
    enum class ShaderType : uint8_t
    {
        INVALID,
        VERTEX,
        FRAGMENT
    };

public:
    Shader(const ShaderType i_type);
    ~Shader() = default;

    bool Initialize(const engine::data::PooledString& i_file_path);

    inline ShaderType GetType() const;
    inline GLuint GetShaderID() const;

private:
    inline GLenum GetGLShaderType(ShaderType i_type) const;

private:
    GLuint                  shader_id_ = 0;
    const ShaderType        type_ = ShaderType::INVALID;

}; // class Shader

} // namespace graphics
} // namespace engine

#include "Shader-inl.h"

#endif // ENGINE_SHADER_H_
