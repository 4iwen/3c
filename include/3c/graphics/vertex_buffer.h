#pragma once

#include "3c/core/assert.h"
#include "3c/core/api.h"

namespace tc {
    enum class TC_API BufferLayoutElementType {
        NONE,
        BOOL,
        INT,
        INT2,
        INT3,
        INT4,
        FLOAT,
        FLOAT2,
        FLOAT3,
        FLOAT4,
        MAT3,
        MAT4
    };

    struct TC_API BufferLayoutElement {
        BufferLayoutElement(
            BufferLayoutElementType type,
            std::string name,
            bool normalized = false
        );

        BufferLayoutElementType type;
        std::string name;
        bool normalized;
        uint32_t offset;
        uint32_t size;
    };

    class TC_API BufferLayout {
    public:
        BufferLayout() = default;

        BufferLayout(std::initializer_list<BufferLayoutElement> elements);

        const std::vector<BufferLayoutElement> &getElements() const;

        size_t getStride() const;

    private:
        std::vector<BufferLayoutElement> m_elements;
        size_t m_stride = 0;
    };

    class TC_API VertexBuffer {
    public:
        virtual ~VertexBuffer() = default;

        virtual void bind() = 0;

        virtual void unbind() = 0;

        virtual void setData(const std::vector<float> &vertices) = 0;

        virtual void setLayout(const BufferLayout &layout) = 0;

        virtual const BufferLayout &getLayout() const = 0;

        static std::shared_ptr<VertexBuffer> create();
    };
} // namespace tc
