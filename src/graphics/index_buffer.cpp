#include "pch.h"

#include "3c/graphics/index_buffer.h"
#include "3c/graphics/renderer.h"
#include "3c/core/assert.h"
#include "3c/graphics/opengl/opengl_index_buffer.h"

namespace tc {
    std::shared_ptr<IndexBuffer> IndexBuffer::create() {
        switch (Renderer::getGraphicsAPIType()) {
            default:
                TC_ASSERT(false, "No graphics API selected");
            case GraphicsAPIType::OPENGL:
                return std::make_shared<OpenGLIndexBuffer>();
        }
    }
} // namespace tc
