#include "pch.h"

#include "3c/graphics/opengl/opengl_index_buffer.h"

#include <glad/gl.h>

namespace tc {
    OpenGLIndexBuffer::OpenGLIndexBuffer(const std::vector<uint32_t> &indices): m_id(0), m_count(indices.size()) {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        glDeleteBuffers(1, &m_id);
    }

    void OpenGLIndexBuffer::bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }

    void OpenGLIndexBuffer::unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }

    size_t OpenGLIndexBuffer::getCount() {
        return m_count;
    }
} // namespace tc
