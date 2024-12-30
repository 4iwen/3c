#include "pch.h"

#include "3c/graphics/opengl/opengl_vertex_buffer.h"

#include <glad/gl.h>

namespace tc {
    OpenGLVertexBuffer::OpenGLVertexBuffer(): m_id(0) {
        glGenBuffers(1, &m_id);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        glDeleteBuffers(1, &m_id);
    }

    void OpenGLVertexBuffer::bind() {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    void OpenGLVertexBuffer::unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::setData(const std::vector<float> &vertices) {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(
            GL_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(vertices.size() * sizeof(float)),
            vertices.data(),
            GL_STATIC_DRAW
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::setLayout(const BufferLayout &layout) {
        m_layout = layout;
    }

    const BufferLayout &OpenGLVertexBuffer::getLayout() const {
        return m_layout;
    }
} // namespace tc
