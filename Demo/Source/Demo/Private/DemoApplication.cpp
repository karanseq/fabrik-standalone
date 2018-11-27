#include "Demo\DemoApplication.h"

// Library includes

// External includes
#include <GL\glew.h>

// Engine includes
#include "Data\PooledString.h"
#include "Graphics\ShaderBuilder.h"
#include "Logger\Logger.h"
#include "Util\FileUtils.h"

void DemoApplication::TestCompileShaders()
{
    const engine::data::PooledString vertex_shader_file_path("Content\\Shaders\\mesh_vertex_shader.glsl");
    const engine::util::FileUtils::FileData vertex_shader_data = engine::util::FileUtils::Get()->ReadFile(vertex_shader_file_path, /*i_cache_file =*/false);
    if (vertex_shader_data.file_size == 0)
    {
        LOG_ERROR("Failed to read vertex shader");
        return;
    }

    const engine::data::PooledString fragment_shader_file_path("Content\\Shaders\\mesh_fragment_shader.glsl");
    const engine::util::FileUtils::FileData fragment_shader_data = engine::util::FileUtils::Get()->ReadFile(fragment_shader_file_path, /*i_cache_file =*/false);
    if (fragment_shader_data.file_size == 0)
    {
        LOG_ERROR("Failed to read fragment shader");
        return;
    }

    GLuint vertex_shader = 0;
    if (engine::graphics::ShaderBuilder::BuildShader(vertex_shader,
        GL_VERTEX_SHADER,
        reinterpret_cast<char*>(vertex_shader_data.file_contents)))
    {
        LOG("Successfully built vertex shader");
    }
    else
    {
        LOG_ERROR("Failed to build vertex shader");
        return;
    }

    GLuint fragment_shader = 0;
    if (engine::graphics::ShaderBuilder::BuildShader(fragment_shader,
        GL_FRAGMENT_SHADER,
        reinterpret_cast<char*>(fragment_shader_data.file_contents)))
    {
        LOG("Successfully built fragment shader");
    }
    else
    {
        LOG_ERROR("Failed to build fragment shader");
        return;
    }

    GLuint program = 0;
    if (engine::graphics::ShaderBuilder::LinkProgram(program, vertex_shader, fragment_shader))
    {
        LOG("Successfully linked GL program");
    }
    else
    {
        LOG_ERROR("Failed to link GL program");
        return;
    }
}
