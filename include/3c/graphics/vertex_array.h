#pragma once

#include "3c/graphics/index_buffer.h"
#include "3c/graphics/vertex_buffer.h"
#include "3c/core/api.h"

namespace tc {
    class TC_API VertexArray {
    public:
        virtual ~VertexArray() = default;

        virtual void bind() = 0;

        virtual void unbind() = 0;

        virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) = 0;

        virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) = 0;

        virtual std::shared_ptr<IndexBuffer> &getIndexBuffer() = 0;

        static std::shared_ptr<VertexArray> create();
    };
} // namespace tc
