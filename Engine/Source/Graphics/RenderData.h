#ifndef ENGINE_RENDER_DATA_H_
#define ENGINE_RENDER_DATA_H_

// Engine includes
#include "Graphics/Color.h"
#include "Math/Vec3D.h"

namespace engine {
namespace graphics {

struct MeshVertexFormat
{
    engine::math::Vec3D         position;
    engine::graphics::Color     color;
    float                       padding;
}; // struct MeshVertexFormat

} // namespace graphics
} // namespace engine

#endif // ENGINE_RENDER_DATA_H_
