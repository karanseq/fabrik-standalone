#ifndef ENGINE_PROGRAM_H_
#define ENGINE_PROGRAM_H_

// System includes
#include <stdint.h>

// Library includes
#include <GL/glew.h>

namespace engine {

// Forward declarations
namespace data {
class PooledString;
}
namespace math {
class Mat44;
class Vec4D;
class Vec3D;
}

namespace graphics {

class Shader;

class Program
{
public:
    Program() = default;
    ~Program() = default;

    bool Initialize(const engine::data::PooledString& i_vertex_shader_path, const engine::data::PooledString& i_fragment_shader_path);
    bool Initialize(const Shader& i_vertex_shader, const Shader& i_fragment_shader);
    void Bind() const;

    void SetUniform(const char* i_uniform_name, const engine::math::Mat44& i_matrix) const;
    void SetUniform(const char* i_uniform_name, const engine::math::Vec4D& i_vector) const;
    void SetUniform(const char* i_uniform_name, const engine::math::Vec3D& i_vector) const;
    void SetUniform(const char* i_uniform_name, const float i_value) const;
    void SetUniform(const char* i_uniform_name, const uint32_t i_value) const;
    void SetUniform(const char* i_uniform_name, const int32_t i_value) const;

    inline GLuint GetProgramID() const;

private:
    GLuint program_id_ = 0;

}; // class Program

} // namespace graphics
} // namespace engine

#include "Program-inl.h"

#endif // ENGINE_PROGRAM_H_
