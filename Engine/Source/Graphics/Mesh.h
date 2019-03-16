#ifndef ENGINE_MESH_H_
#define ENGINE_MESH_H_

// System includes
#include <stdint.h>

// Library includes
#include <GL/glew.h>

namespace engine {

namespace data {
    class PooledString;
}

namespace graphics {

class Mesh
{
public:
    Mesh() = default;
    ~Mesh() = default;

    bool Initialize(const engine::data::PooledString& i_file_path);
    void Draw() const;

private:
    uint32_t    index_count_ = 0;
    GLuint      vertex_array_id_ = 0;

}; // class Mesh

} // namespace graphics
} // namespace engine

#endif // ENGINE_MESH_H_
