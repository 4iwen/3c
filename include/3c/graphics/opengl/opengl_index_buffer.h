#pragma once

#include "3c/core/api.h"
#include "3c/graphics/index_buffer.h"

namespace tc {
    class TC_API OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer();

        ~OpenGLIndexBuffer() override;

        void bind() override;

        void unbind() override;

        void setData(const std::vector<uint32_t> &indices) override;

        size_t getCount() override;

    private:
        uint32_t m_id;
        size_t m_count;
    };
} // namespace tc
