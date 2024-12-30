#pragma once

#include "3c/core/api.h"

namespace tc {
    class TC_API IndexBuffer {
    public:
        virtual ~IndexBuffer() = default;

        virtual void bind() = 0;

        virtual void unbind() = 0;

        virtual void setData(const std::vector<uint32_t> &indices) = 0;

        virtual size_t getCount() = 0;

        static std::shared_ptr<IndexBuffer> create();
    };
} // namespace tc
