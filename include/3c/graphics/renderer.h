#pragma once

#include "3c/core/api.h"
#include "3c/graphics/vertex_array.h"

#include <glm/glm.hpp>

namespace tc {
    enum class TC_API GraphicsAPIType {
        NONE,
        OPENGL
    };

    class TC_API Renderer {
    public:
        virtual ~Renderer() = default;

        virtual void clear(glm::vec4 color) = 0;

        virtual void submit(const std::shared_ptr<VertexArray> &vertexArray) = 0;

        virtual void setViewport(uint32_t width, uint32_t height) = 0;

        static GraphicsAPIType getGraphicsAPIType() { return s_apiType; }

        static std::shared_ptr<Renderer> create(GraphicsAPIType apiType);

    private:
        static GraphicsAPIType s_apiType;
    };
} // namespace tc
