#include "Graphics/GLErrorHelper.h"

// External includes
#include "Gl/glew.h"
#include "Gl/GLU.h"

// Engine includes
#include "Logger/Logger.h"

namespace engine {
namespace graphics {

void CheckAndPrintGLError(const char* i_operation)
{
    const GLenum error_code = glGetError();
    if (error_code != GL_NO_ERROR)
    {
        switch (error_code)
        {
        case GL_INVALID_ENUM:
            LOG_ERROR("%s : An unacceptable value is specified for an enumerated argument.", i_operation);
            break;
        case GL_INVALID_VALUE:
            LOG_ERROR("%s : A numeric argument is out of range.", i_operation);
            break;
        case GL_INVALID_OPERATION:
            LOG_ERROR("%s : The specified operation is not allowed in the current state.", i_operation);
            break;
        case GL_STACK_OVERFLOW:
            LOG_ERROR("%s : This function would cause a stack overflow.", i_operation);
            break;
        case GL_STACK_UNDERFLOW:
            LOG_ERROR("%s : This function would cause a stack underflow.", i_operation);
            break;
        case GL_OUT_OF_MEMORY:
            LOG_ERROR("%s : There is not enough memory left to execute the function.", i_operation);
            break;
        default:
            break;
        }
    }
}

} // namespace graphics
} // namespace engine
