#pragma once

#include "3c/core/api.h"
#include "3c/graphics/vertex_buffer.h"

namespace tc {
    class TC_API OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer();

        ~OpenGLVertexBuffer() override;

        void bind() override;

        void unbind() override;

        void setData(const std::vector<float> &vertices) override;

        void setLayout(const BufferLayout &layout) override;

        const BufferLayout & getLayout() const override;

    private:
        uint32_t m_id;
        BufferLayout m_layout;
    };
} // namespace tc
