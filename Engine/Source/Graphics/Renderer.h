#ifndef ENGINE_GRAPHICS_RENDERER_H_
#define ENGINE_GRAPHICS_RENDERER_H_

// System includes
#include <vector>

// External includes
#include "SDL.h"

// Engine includes
#include "Common/Engine.h"
#include "Graphics/RenderData.h"

// Forward declarations
namespace engine {
namespace graphics {
    class Camera;
    class Mesh;
    class Program;
}
namespace math {
    class Transform;
}
}

namespace engine {
namespace graphics {

class Renderer
{
public:
    static Renderer* Create(SDL_Window* i_window);
    static void Destroy();
    static inline Renderer* Get() { return instance_; }

    void SubmitCamera(const Camera& i_camera);
    void SubmitMesh(const Mesh& i_mesh, const Program& i_program, const math::Transform& i_transform);

private:
    const Camera*                   camera_ = nullptr;
    std::vector<MeshRenderData>     mesh_render_data_;

private:
    bool Init(SDL_Window* i_window);

    void StartCurrentFrame();
    void Draw() const;
    void EndCurrentFrame();

    friend void engine::Render();

private:
    SDL_GLContext gl_context_;
    SDL_Window* window_;

private:
    Renderer() = default;
    ~Renderer() = default;
    static Renderer* instance_;

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

}; // class Renderer

} // namespace renderer
} // namespace engine

#endif // ENGINE_GRAPHICS_RENDERER_H_
