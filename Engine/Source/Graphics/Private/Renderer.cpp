#include "Graphics\Renderer.h"

// Library includes

// External includes
#include <GL/glew.h>

// Engine includes

namespace engine {
namespace graphics {

    void Render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

} // namespace renderer
} // namespace engine

