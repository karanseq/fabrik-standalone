#ifndef DEMO_APPLICATION_H_
#define DEMO_APPLICATION_H_

// Library includes
#include <GL/glew.h>

// External includes

// Engine includes
#include "Application/SDLApplication.h"
#include "Graphics/Program.h"

// Forward declarations
namespace engine {
namespace events {
    class MouseButtonEvent;
}
}

class DemoApplication : public engine::application::SDLApplication
{
public:
    DemoApplication() : engine::application::SDLApplication("Renderer Demo")
    {}
    virtual ~DemoApplication() = default;

    // ApplicationInterface implementation
public:
    bool Init() override;

private:
    void Render() override;

    // Demo functions
private:
    void OnMouseEvent(const engine::events::MouseButtonEvent& i_event);

    void InitGraphicsProgram();
    void InitMesh();

    // Data
private:
    engine::events::EventReceipt            mouse_event_receipt_;
    engine::graphics::Program               graphics_program_;
    GLuint                                  vertex_array_id_;
    GLuint                                  vertex_buffer_id_;
    GLuint                                  index_buffer_id_;

}; // class DemoApplication

#endif // DEMO_APPLICATION_H_
