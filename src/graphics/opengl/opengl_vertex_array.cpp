#include "pch.h"

#include "3c/graphics/opengl/opengl_vertex_array.h"
#include "3c/core/assert.h"

#include <glad/gl.h>

namespace tc {
    GLint getLayoutElementComponentCount(BufferLayoutElementType type) {
        switch (type) {
            case BufferLayoutElementType::FLOAT:
            case BufferLayoutElementType::INT:
            case BufferLayoutElementType::BOOL:
                return 1;
            case BufferLayoutElementType::FLOAT2:
            case BufferLayoutElementType::INT2:
                return 2;
            case BufferLayoutElementType::FLOAT3:
            case BufferLayoutElementType::INT3:
                return 3;
            case BufferLayoutElementType::FLOAT4:
            case BufferLayoutElementType::INT4:
                return 4;
            case BufferLayoutElementType::MAT3:
                return 3 * 3;
            case BufferLayoutElementType::MAT4:
                return 4 * 4;
            default:
                TC_ASSERT(false, "Unknown buffer layout element type");
        }
    }

    GLenum getLayoutElementGLType(BufferLayoutElementType type) {
        switch (type) {
            case BufferLayoutElementType::FLOAT:
            case BufferLayoutElementType::FLOAT2:
            case BufferLayoutElementType::FLOAT3:
            case BufferLayoutElementType::FLOAT4:
            case BufferLayoutElementType::MAT3:
            case BufferLayoutElementType::MAT4:
                return GL_FLOAT;
            case BufferLayoutElementType::INT:
            case BufferLayoutElementType::INT2:
            case BufferLayoutElementType::INT3:
            case BufferLayoutElementType::INT4:
                return GL_INT;
            case BufferLayoutElementType::BOOL:
                return GL_BOOL;
            default:
                TC_ASSERT(false, "Unknown buffer layout element type");
        }
    }

    OpenGLVertexArray::OpenGLVertexArray(): m_id(0) {
        glGenVertexArrays(1, &m_id);
        glBindVertexArray(m_id);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &m_id);
    }

    void OpenGLVertexArray::bind() {
        glBindVertexArray(m_id);
    }

    void OpenGLVertexArray::unbind() {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) {
        bool hasLayout = !vertexBuffer->getLayout().getElements().empty();
        if (!hasLayout) {
            TC_ASSERT(false, "Vertex buffer has no layout");
        }

        m_vertexBuffers.push_back(vertexBuffer);

        glBindVertexArray(m_id);
        vertexBuffer->bind();

        const auto &layout = vertexBuffer->getLayout();
        const auto &elements = layout.getElements();
        for (GLuint i = 0; i < elements.size(); i++) {
            const auto &element = elements[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(
                i,
                getLayoutElementComponentCount(element.type),
                getLayoutElementGLType(element.type),
                element.normalized ? GL_TRUE : GL_FALSE,
                static_cast<GLsizei>(layout.getStride()),
                reinterpret_cast<const void *>(element.offset)
            );
        }
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) {
        m_indexBuffer = indexBuffer;

        glBindVertexArray(m_id);
        m_indexBuffer->bind();
        glBindVertexArray(0);
    }

    std::shared_ptr<IndexBuffer> &OpenGLVertexArray::getIndexBuffer() {
        return m_indexBuffer;
    }
} // namespace tc
