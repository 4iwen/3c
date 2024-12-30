#pragma once

#include "3c/core/api.h"
#include "3c/graphics/texture.h"

#include <glm/glm.hpp>

namespace tc {
    struct TC_API Quad {
        glm::vec3 position;
        float rotation;
        glm::vec2 size;
        glm::vec4 tint;
        std::optional<std::shared_ptr<Texture> > texture;
    };
} // namespace tc
