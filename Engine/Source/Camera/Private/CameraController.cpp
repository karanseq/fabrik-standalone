#include "Camera/CameraController.h"

// Engine includes
#include "Assert/Assert.h"
#include "Events/KeyboardEvent.h"
#include "Events/MouseButtonEvent.h"
#include "Input/InputProcessor.h"
#include "Math/MathUtil.h"
#include "Math/Vec3D.h"
#include "Math/Quaternion.h"
#include "Time/Updater.h"

namespace engine {
namespace graphics {

void CameraController::Tick(float dt)
{
    if (mouse_button_pressed_ == false)
    {
        return;
    }

    // Update position
    {
        static constexpr float move_speed = 0.1f;
        const math::Vec3D camera_delta(
            (is_left_pressed_ ? move_speed : (is_right_pressed_ ? -move_speed : 0.0f)),
            (is_up_pressed_ ? -move_speed : (is_down_pressed_ ? move_speed : 0.0f)),
            (is_forward_pressed_ ? move_speed : (is_back_pressed_ ? -move_speed : 0.0f))
        );

        camera_->SetPosition(camera_->GetPosition() + camera_delta);
    }

    // Update rotation
    {
        static constexpr float rotate_speed = 0.001f;

        input::InputProcessor* input_processor = input::InputProcessor::Get();
        ASSERT(input_processor);

        const float mouse_motion_x = float(input_processor->GetCurrentMouseX() - input_processor->GetPreviousMouseX());
        const float mouse_motion_y = float(input_processor->GetCurrentMouseY() - input_processor->GetPreviousMouseY());

        math::Quaternion new_rotation = camera_->GetRotation();
        if (math::IsZero(mouse_motion_x) == false)
        {
            const math::Quaternion yaw_delta(-rotate_speed * mouse_motion_x, math::Vec3D::UNIT_Y);
            new_rotation *= yaw_delta;
            new_rotation.Normalize();
        }

        if (math::IsZero(mouse_motion_y) == false)
        {
            const math::Quaternion pitch_delta(-rotate_speed * mouse_motion_y, math::Vec3D::UNIT_X);
            new_rotation *= pitch_delta;
            new_rotation.Normalize();
        }

        camera_->SetRotation(new_rotation);
    }
}

void CameraController::StartUpdating()
{
    time::Updater::Get()->AddTickable(this);
}

void CameraController::StopUpdating()
{
    time::Updater::Get()->RemoveTickable(this);
}

void CameraController::StartListeningForInput()
{
    keyboard_event_receipt_ = input::InputProcessor::Get()->AddListener(
        std::bind(&CameraController::OnKeyboardEvent, this, std::placeholders::_1)
    );
    ASSERT(keyboard_event_receipt_.IsValid());

    mouse_event_receipt_ = input::InputProcessor::Get()->AddListener(
        std::bind(&CameraController::OnMouseEvent, this, std::placeholders::_1)
    );
    ASSERT(mouse_event_receipt_.IsValid());
}

void CameraController::StopListeningForInput()
{
    input::InputProcessor::Get()->RemoveListener(keyboard_event_receipt_);
    ASSERT(keyboard_event_receipt_.IsValid() == false);
    input::InputProcessor::Get()->RemoveListener(mouse_event_receipt_);
    ASSERT(mouse_event_receipt_.IsValid() == false);
}

void CameraController::OnMouseEvent(const events::MouseButtonEvent& i_event)
{
    mouse_button_pressed_ = input::InputProcessor::IsRightMouseButtonPressed(i_event.GetSDLEvent());
}

void CameraController::OnKeyboardEvent(const events::KeyboardEvent& i_event)
{
    const SDL_KeyboardEvent& sdl_event = i_event.GetSDLEvent();
    is_forward_pressed_ = sdl_event.keysym.sym == SDLK_w ? sdl_event.state == SDL_PRESSED : is_forward_pressed_;
    is_back_pressed_    = sdl_event.keysym.sym == SDLK_s ? sdl_event.state == SDL_PRESSED : is_back_pressed_;
    is_left_pressed_    = sdl_event.keysym.sym == SDLK_a ? sdl_event.state == SDL_PRESSED : is_left_pressed_;
    is_right_pressed_   = sdl_event.keysym.sym == SDLK_d ? sdl_event.state == SDL_PRESSED : is_right_pressed_;
    is_up_pressed_      = sdl_event.keysym.sym == SDLK_e ? sdl_event.state == SDL_PRESSED : is_up_pressed_;
    is_down_pressed_    = sdl_event.keysym.sym == SDLK_q ? sdl_event.state == SDL_PRESSED : is_down_pressed_;
}

} // namespace graphics
} // namespace engine
