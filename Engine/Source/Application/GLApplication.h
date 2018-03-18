#ifndef GL_APPLICATION_H_
#define GL_APPLICATION_H_

// Library includes
#include <stdint.h>

// External includes

// Engine includes
#include "Application/Application.h"

// Forward declarations

namespace engine {
namespace application {

    class GLApplication : public ApplicationInterface
    {
    public:
        GLApplication() = default;
        virtual ~GLApplication() = default;

        // ApplicationInterface implementation
    public:
        bool Init(int argc, char** argv) override;
        void Run() override;
        bool Shutdown() override;

        void Update() override;
        void Render() override;

        void ReceiveKeyboardInput(unsigned char key, int x, int y) override;

    protected:
        uint16_t window_width_ = 800;
        uint16_t window_height_ = 600;
        const char* window_title_ = "GL Application";

    }; // class GLApplication

} // namespace application
} // namespace engine

#endif // GL_APPLICATION_H_
