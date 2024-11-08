#pragma once

#include "3c/core/api.h"

#include "3c/graphics/renderer.h"

namespace tc {
    class TC_API OpenGLRenderer : public Renderer {
    public:
        OpenGLRenderer();

        ~OpenGLRenderer() override;

        void clear(glm::vec4 color) override;

        void submit(const std::shared_ptr<VertexArray> &vertexArray) override;

        void setViewport(uint32_t width, uint32_t height) override;
    };
}
