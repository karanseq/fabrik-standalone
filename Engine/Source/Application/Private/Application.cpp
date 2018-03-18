#include "Application/Application.h"

namespace engine {
namespace application {

    // Static member initialization
    ApplicationInterface* ApplicationInterface::g_application = nullptr;

    void ApplicationUpdateFunc()
    {
        ApplicationInterface::g_application->Update();
    }

    void ApplicationRenderFunc()
    {
        ApplicationInterface::g_application->Render();
    }

    void ApplicationKeyboardFunc(unsigned char key, int x, int y)
    {
        ApplicationInterface::g_application->ReceiveKeyboardInput(key, x, y);
    }

} // namespace application
} // namespace engine
