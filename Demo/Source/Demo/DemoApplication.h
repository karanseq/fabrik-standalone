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
    void Update() override;
    void Render() override;

    // Demo functions
private:
    void OnMouseEvent(const engine::events::MouseButtonEvent& i_event);
    void OnKeyboardEvent(const engine::events::KeyboardEvent& i_event);

    void InitGraphicsProgram();
    void InitMesh();
    void InitTransforms();

    // Data
private:
    engine::events::EventReceipt            mouse_event_receipt_;
    engine::events::EventReceipt            keyboard_event_receipt_;
    engine::graphics::Program               graphics_program_;
    GLuint                                  vertex_array_id_ = 0;
    GLuint                                  vertex_buffer_id_ = 0;
    GLuint                                  index_buffer_id_ = 0;
    bool                                    is_forward_pressed_ = false;
    bool                                    is_back_pressed_ = false;
    bool                                    is_left_pressed_ = false;
    bool                                    is_right_pressed_ = false;
    bool                                    is_up_pressed_ = false;
    bool                                    is_down_pressed_ = false;

}; // class DemoApplication

#endif // DEMO_APPLICATION_H_
