#include "pch.h"

#include "3c/graphics/renderer.h"
#include "3c/core/assert.h"
#include "3c/graphics/opengl/opengl_renderer.h"

#include <glad/gl.h>

namespace tc {
    GraphicsAPIType Renderer::s_apiType = GraphicsAPIType::NONE;

    std::shared_ptr<Renderer> Renderer::create(GraphicsAPIType apiType) {
        s_apiType = apiType;

        switch (s_apiType) {
            default:
                TC_ASSERT(false, "No graphics API selected");
            case GraphicsAPIType::OPENGL:
                return std::make_shared<OpenGLRenderer>();
        }
    }
} // namespace tc
