#include "pch.h"

#include "3c/graphics/vertex_array.h"
#include "3c/graphics/renderer.h"
#include "3c/core/assert.h"
#include "3c/graphics/opengl/opengl_vertex_array.h"

namespace tc {
    std::shared_ptr<VertexArray> VertexArray::create() {
        switch (Renderer::getGraphicsAPIType()) {
            default:
                TC_ASSERT(false, "No graphics API selected");
            case GraphicsAPIType::OPENGL:
                return std::make_shared<OpenGLVertexArray>();
        }
    }
} // namespace tc
