#ifndef GLUT_HELPER_H_
#define GLUT_HELPER_H_

// Library includes
#include <stdint.h>

namespace engine {
namespace graphics {

    /*
        GLUTHelper
    */

    typedef void(*DisplayFunc)(void);
    typedef void(*IdleFunc)(void);
    typedef void(*KeyboardFunc)(unsigned char, int, int);

    class GLUTHelper
    {
    public:
        struct InitParams
        {
            int*                    pargc = nullptr;
            char**                  argv = nullptr;
            unsigned int            display_mode = 0;

            uint16_t                window_width = 0;
            uint16_t                window_height = 0;
            const char*             window_title = nullptr;

            DisplayFunc             display_func;
            IdleFunc                idle_func;
            KeyboardFunc            keyboard_func;

        }; // struct InitParams

    public:
        static bool Init(const InitParams& i_params);
        static void Run();
        static bool Shutdown();

    private:
        GLUTHelper() = delete;
        ~GLUTHelper() = delete;

        GLUTHelper(const GLUTHelper&) = delete;
        GLUTHelper& operator=(const GLUTHelper&) = delete;

    }; // class GLUTHelper

}
} // namespace engine

#endif // GLUT_HELPER_H_
