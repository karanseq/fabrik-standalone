#include "Graphics/Mesh.h"

// Engine includes
#include "Assert/Assert.h"
#include "Data/PooledString.h"
#include "Graphics/Color.h"
#include "Graphics/GLErrorHelper.h"
#include "Graphics/RenderData.h"
#include "Logger/Logger.h"
#include "Math/Vec3D.h"

namespace engine {
namespace graphics {

bool Mesh::Initialize(const engine::data::PooledString& /*i_file_path*/)
{
    // Create a vertex array object and make it active
    {
        constexpr GLsizei array_count = 1;
        glGenVertexArrays(array_count, &vertex_array_id_);
        CheckAndPrintGLError("Failed to generate vertex array");
        glBindVertexArray(vertex_array_id_);
        CheckAndPrintGLError("Failed to bind vertex array");
    }

    // Create a vertex buffer object and make it active
    GLuint vertex_buffer_id = 0;
    {
        constexpr GLsizei buffer_count = 1;
        glGenBuffers(buffer_count, &vertex_buffer_id);
        CheckAndPrintGLError("Failed to generate vertex buffer");
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
        CheckAndPrintGLError("Failed to bind vertex buffer");
    }

    // Assign data to the vertex buffer
    constexpr GLuint vertex_count = 8;
    {
        constexpr float half_size = 1.0f;
        const MeshVertexFormat vertex_data[vertex_count] = {
            { engine::math::Vec3D(-half_size, -half_size, half_size),   engine::graphics::Color::RED },
            { engine::math::Vec3D(half_size, -half_size, half_size),    engine::graphics::Color::PURPLE },
            { engine::math::Vec3D(half_size, half_size, half_size),     engine::graphics::Color::BLUE },
            { engine::math::Vec3D(-half_size, half_size, half_size),    engine::graphics::Color::PURPLE },
            { engine::math::Vec3D(half_size, -half_size, -half_size),   engine::graphics::Color::PURPLE },
            { engine::math::Vec3D(-half_size, -half_size, -half_size),  engine::graphics::Color::RED },
            { engine::math::Vec3D(-half_size, half_size, -half_size),   engine::graphics::Color::PURPLE },
            { engine::math::Vec3D(half_size, half_size, -half_size),    engine::graphics::Color::BLUE },
        };

        constexpr size_t buffer_size = vertex_count * sizeof(MeshVertexFormat);
        glBufferData(GL_ARRAY_BUFFER, buffer_size, vertex_data, GL_STATIC_DRAW);
        CheckAndPrintGLError("Failed to allocate vertex buffer");
        // Vertex data can be freed at this point
    }

    // Create an index buffer and make it active
    GLuint index_buffer_id = 0;
    {
        constexpr GLsizei buffer_count = 1;
        glGenBuffers(buffer_count, &index_buffer_id);
        CheckAndPrintGLError("Failed to generate index buffer");
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id);
        CheckAndPrintGLError("Failed to bind index buffer");
    }

    // Assign data to the index buffer
    constexpr uint32_t index_count = 36;
    index_count_ = index_count;
    {
        const uint32_t indices[index_count] = {
            0, 1, 2, 0, 2, 3,       // front
            4, 5, 6, 4, 6, 7,       // back
            5, 0, 3, 5, 3, 6,       // left
            1, 4, 7, 1, 7, 2,       // right
            3, 2, 7, 3, 7, 6,       // top
            5, 4, 1, 5, 1, 0        // bottom
        };

        constexpr size_t buffer_size = index_count * sizeof(uint32_t);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_size, indices, GL_STATIC_DRAW);
        CheckAndPrintGLError("Failed to allocate index buffer");
    }

    // Initialize vertex attribute
    {
        constexpr GLsizei stride = static_cast<GLsizei>(sizeof(MeshVertexFormat));

        // Position
        {
            constexpr GLuint    vertex_position_location = 0;
            constexpr GLuint    element_count = 3;
            glVertexAttribPointer(vertex_position_location,
                element_count,
                GL_FLOAT,
                GL_FALSE,
                stride, reinterpret_cast<void*>(offsetof(MeshVertexFormat, position))
            );
            CheckAndPrintGLError("Failed to set 'position' vertex attribute");
            glEnableVertexAttribArray(vertex_position_location);
            CheckAndPrintGLError("Failed to enable 'position' vertex attribute");
        }

        // Color
        {
            constexpr GLuint    vertex_color_location = 1;
            constexpr GLuint    element_count = 4;
            glVertexAttribPointer(vertex_color_location,
                element_count,
                GL_FLOAT,
                GL_TRUE,
                stride, reinterpret_cast<void*>(offsetof(MeshVertexFormat, color))
            );
            CheckAndPrintGLError("Failed to set 'color' vertex attribute");
            glEnableVertexAttribArray(vertex_color_location);
            CheckAndPrintGLError("Failed to enable 'color' vertex attribute");
        }
    }

    return true;
}

void Mesh::Draw() const
{
    glBindVertexArray(vertex_array_id_);
    ASSERT(glGetError() == GL_NO_ERROR);

    glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, 0);
    ASSERT(glGetError() == GL_NO_ERROR);
}

} // namespace graphics
} // namespace engine
