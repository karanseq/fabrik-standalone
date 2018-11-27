#ifndef SDL_APPLICATION_H_
#define SDL_APPLICATION_H_

// Library includes
#include <stdint.h>

// External includes
#include "SDL.h"

// Engine includes
#include "Application\Application.h"

// Forward declarations

namespace engine {
namespace application {

    class SDLApplication : public ApplicationInterface
    {
    public:
        SDLApplication() = default;
        SDLApplication(const char* i_window_title);
        virtual ~SDLApplication() = default;

        // ApplicationInterface implementation
    public:
        bool Init() override;
        void Run() override;
        void Shutdown() override;

        void Update() override;
        void Render() override;

        // Implementation
    private:
        bool InitGLAttributes();
        void HandleSDLEvent(const SDL_Event& i_event);

        // Data
    protected:
        uint16_t                                window_width_ = 800;
        uint16_t                                window_height_ = 600;
        const char*                             window_title_ = "SDL Application";

    private:
        SDL_Window*                             window_ = nullptr;
        SDL_GLContext                           gl_context_;

    }; // class SDLApplication

} // namespace application
} // namespace engine

#endif // SDL_APPLICATION_H_