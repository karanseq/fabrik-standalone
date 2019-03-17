#include "Graphics/Renderer.h"

// Library includes

// External includes
#include <GL/glew.h>

// Engine includes
#include "Assert/Assert.h"
#include "Common/HelperMacros.h"
#include "Graphics/Camera.h"
#include "Graphics/Mesh.h"
#include "Graphics/Program.h"
#include "Logger/Logger.h"

namespace engine {
namespace graphics {

// Static member initialization
Renderer* Renderer::instance_ = nullptr;

Renderer* Renderer::Create(SDL_Window* i_window)
{
    if (Renderer::instance_ == nullptr)
    {
        Renderer::instance_ = new Renderer();
        if (Renderer::instance_->Init(i_window) == false)
        {
            SAFE_DELETE(Renderer::instance_);
        }
    }
    return Renderer::instance_;
}

void Renderer::Destroy()
{
    SAFE_DELETE(Renderer::instance_);
}

void Renderer::SubmitCamera(const Camera& i_camera)
{
    camera_ = &i_camera;
}

void Renderer::SubmitMesh(const Mesh& i_mesh, const Program& i_program, const math::Transform& i_transform)
{
    mesh_render_data_.push_back({ &i_mesh, &i_program, &i_transform });
}

void Renderer::StartCurrentFrame()
{
    ASSERT(camera_ != nullptr);
}

void Renderer::Draw() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    math::Mat44 camera_transformation;
    math::GetObjectToWorldTransform(camera_->GetTransform(), camera_transformation);

    for (const MeshRenderData& packet : mesh_render_data_)
    {
        const Program* program = packet.program;
        program->Bind();

        program->SetUniform("g_camera_view", camera_->GetPerspectiveProjection());
        program->SetUniform("g_world_camera", camera_transformation);

        math::Mat44 mesh_transformation;
        math::GetObjectToWorldTransform(*packet.transform, mesh_transformation);
        program->SetUniform("g_model_world", mesh_transformation);

        packet.mesh->Draw();
    }

    SDL_GL_SwapWindow(window_);
}

void Renderer::EndCurrentFrame()
{
    mesh_render_data_.clear();
}

bool Renderer::Init(SDL_Window* i_window)
{
    ASSERT(i_window);
    window_ = i_window;

    gl_context_ = SDL_GL_CreateContext(i_window);
    if (gl_context_ == nullptr)
    {
        LOG_ERROR("Failed to create an OpenGL context! Error:%s", SDL_GetError());
        return false;
    }

    // OpenGL core profile - deprecated functions are disabled
    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) < 0)
    {
        LOG_ERROR("Failed to set GL attribute! Error:%s", SDL_GetError());
        return false;
    }

    // Set GL version
    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) < 0 ||
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2) < 0)
    {
        LOG_ERROR("Failed to set GL attribute! Error:%s", SDL_GetError());
        return false;
    }

    // Enable double buffering
    if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0)
    {
        LOG_ERROR("Failed to set GL attribute! Error:%s", SDL_GetError());
        return false;
    }

    // Synchronize buffer swap with monitor's vertical retrace
    if (SDL_GL_SetSwapInterval(1) < 0)
    {
        LOG_ERROR("Failed to set swap interval! Error:%s", SDL_GetError());
        return false;
    }

    glEnable(GL_DEPTH_TEST);

    // Init GLEW
    GLenum glew_init_success = glewInit();
    if (glew_init_success != GLEW_OK)
    {
        LOG_ERROR("Failed to init GLEW! Error:%s", glewGetErrorString(glew_init_success));
        return false;
    }

    return true;
}

} // namespace renderer
} // namespace engine

