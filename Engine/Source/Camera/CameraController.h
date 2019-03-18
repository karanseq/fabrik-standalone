#ifndef ENGINE_GRAPHICS_CAMERA_CONTROLLER_H_
#define ENGINE_GRAPHICS_CAMERA_CONTROLLER_H_

// Engine includes
#include "Events/EventReceipt.h"
#include "Camera/Camera.h"
#include "Math/Vec3D.h"
#include "Memory/SharedPointer.h"
#include "Time/InterfaceTickable.h"

// Forward declarations
namespace engine {
namespace events {
    class KeyboardEvent;
    class MouseButtonEvent;
}
}

namespace engine {
namespace graphics {

class CameraController : public time::InterfaceTickable
{
public:
    CameraController() = default;
    ~CameraController() = default;

    inline const memory::SharedPointer<Camera>& GetCamera() const;
    inline void SetCamera(const memory::SharedPointer<Camera>& i_camera);

    // InterfaceTickable implementation
private:
    void Tick(float dt) override;
    void StartUpdating();
    void StopUpdating();

    // Internal - Input handling
private:
    void StartListeningForInput();
    void StopListeningForInput();
    inline bool IsListeningForInput() const;

    void OnMouseEvent(const events::MouseButtonEvent& i_event);
    void OnKeyboardEvent(const events::KeyboardEvent& i_event);

private:
    memory::SharedPointer<Camera>       camera_ = nullptr;
    events::EventReceipt                keyboard_event_receipt_;
    events::EventReceipt                mouse_event_receipt_;

    // Internal - Input response
private:
    math::Vec3D                         movement_input_accumulated_;
    bool                                mouse_button_pressed_ = false;
    bool                                is_forward_pressed_ = false;
    bool                                is_back_pressed_ = false;
    bool                                is_left_pressed_ = false;
    bool                                is_right_pressed_ = false;
    bool                                is_up_pressed_ = false;
    bool                                is_down_pressed_ = false;

}; // class CameraController

} // namespace graphics
} // namespace engine

#include "CameraController-inl.h"

#endif // ENGINE_GRAPHICS_CAMERA_CONTROLLER_H_
