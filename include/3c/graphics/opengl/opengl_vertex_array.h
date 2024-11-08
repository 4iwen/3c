#pragma once

#include "3c/core/api.h"
#include "3c/graphics/vertex_array.h"

namespace tc {
    class TC_API OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();

        ~OpenGLVertexArray() override;

        void bind() override;

        void unbind() override;

        void addVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) override;

        void setIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) override;

        std::shared_ptr<IndexBuffer> &getIndexBuffer() override;

    private:
        uint32_t m_id;
        std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
        std::shared_ptr<IndexBuffer> m_indexBuffer;
    };
} // namespace tc
