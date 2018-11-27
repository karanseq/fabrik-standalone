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

        static float r = 0.15f;
        static float g = 0.25f;
        static float b = 0.35f;

        r = r + 0.001f > 1.0f ? 0.0f : r + 0.001f;
        g = g + 0.0015f > 1.0f ? 0.0f : g + 0.0015f;
        b = b + 0.002f > 1.0f ? 0.0f : b + 0.002f;
        glClearColor(r, g, b, 1.0f);
    }

} // namespace renderer
} // namespace engine

