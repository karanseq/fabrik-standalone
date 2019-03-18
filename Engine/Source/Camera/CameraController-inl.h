#include "CameraController.h"

namespace engine {
namespace graphics {

inline const memory::SharedPointer<Camera>& CameraController::GetCamera() const
{
    return camera_;
}

inline void CameraController::SetCamera(const memory::SharedPointer<Camera>& i_camera)
{
    if (camera_ == i_camera)
    {
        return;
    }

    camera_ = i_camera;
    if (camera_ == nullptr && IsListeningForInput())
    {
        StopListeningForInput();
        StopUpdating();
    }
    else if (camera_ != nullptr && IsListeningForInput() == false)
    {
        StartListeningForInput();
        StartUpdating();
    }
}

inline bool CameraController::IsListeningForInput() const
{
    return keyboard_event_receipt_.IsValid() && mouse_event_receipt_.IsValid();
}

} // namespace graphics
} // namespace engine
