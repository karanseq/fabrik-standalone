#ifndef ENGINE_RENDER_DATA_H_
#define ENGINE_RENDER_DATA_H_

// Engine includes
#include "Graphics/Color.h"
#include "Math/Vec3D.h"

// Forward declarations
namespace engine {
namespace graphics {
    class Mesh;
    class Program;
}
namespace math {
    class Transform;
}
}

namespace engine {
namespace graphics {

struct MeshVertexFormat
{
    math::Vec3D                     position;
    Color                           color;
    float                           padding;
};

struct MeshRenderData
{
    const Mesh*                     mesh = nullptr;
    const Program*                  program = nullptr;
    const math::Transform*          transform = nullptr;
};

} // namespace graphics
} // namespace engine

#endif // ENGINE_RENDER_DATA_H_
