#include "pch.h"

#include "3c/graphics/vertex_buffer.h"
#include "3c/graphics/renderer.h"
#include "3c/core/assert.h"
#include "3c/graphics/opengl/opengl_vertex_buffer.h"

namespace tc {
    uint32_t bufferLayoutElementTypeSize(BufferLayoutElementType type) {
        switch (type) {
            case BufferLayoutElementType::BOOL:
                return 1;
            case BufferLayoutElementType::INT:
            case BufferLayoutElementType::FLOAT:
                return 4;
            case BufferLayoutElementType::INT2:
            case BufferLayoutElementType::FLOAT2:
                return 4 * 2;
            case BufferLayoutElementType::INT3:
            case BufferLayoutElementType::FLOAT3:
                return 4 * 3;
            case BufferLayoutElementType::INT4:
            case BufferLayoutElementType::FLOAT4:
                return 4 * 4;
            case BufferLayoutElementType::MAT3:
                return 4 * 3 * 3;
            case BufferLayoutElementType::MAT4:
                return 4 * 4 * 4;
            default:
                TC_ASSERT(false, "Unknown buffer layout element type");
        }
    }

    BufferLayoutElement::BufferLayoutElement(
        BufferLayoutElementType type,
        std::string name,
        bool normalized
    ) : type(type), name(std::move(name)), normalized(normalized), offset(0), size(bufferLayoutElementTypeSize(type)) {
    }

    BufferLayout::BufferLayout(
        std::initializer_list<BufferLayoutElement> elements
    ): m_elements(elements) {
        uint32_t offset = 0;
        m_stride = 0;
        for (auto &element: m_elements) {
            element.offset = offset;
            offset += element.size;
            m_stride += element.size;
        }
    }

    const std::vector<BufferLayoutElement> &BufferLayout::getElements() const {
        return m_elements;
    }

    size_t BufferLayout::getStride() const {
        return m_stride;
    }

    std::shared_ptr<VertexBuffer> VertexBuffer::create(const std::vector<float> &vertices) {
        switch (Renderer::getGraphicsAPIType()) {
            default:
                TC_ASSERT(false, "No graphics API selected");
            case GraphicsAPIType::OPENGL:
                return std::make_shared<OpenGLVertexBuffer>(vertices);
        }
    }
} // namespace tc
