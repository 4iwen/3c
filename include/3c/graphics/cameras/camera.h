#pragma once

#include "3c/core/api.h"

#include <glm/glm.hpp>

namespace tc {
    class TC_API Camera {
    public:
        virtual ~Camera() = default;

        virtual void setAspectRatio(float aspectRatio) = 0;

        void setPosition(const glm::vec3 &position) {
            m_position = position;
            recalculateViewProjection();
        }

        void setRotation(const glm::vec3 &rotation) {
            m_rotation = rotation;
            recalculateViewProjection();
        }

        const glm::vec3 &getPosition() {
            return m_position;
        }

        const glm::vec3 &getRotation() {
            return m_rotation;
        }

        const glm::mat4 &getProjection() {
            return m_projection;
        }

        const glm::mat4 &getViewProjection() {
            return m_viewProjection;
        }

    private:
        virtual void recalculateViewProjection() = 0;

    protected:
        glm::vec3 m_position = {0.0f, 0.0f, 0.0f};
        glm::vec3 m_rotation = {0.0f, 0.0f, 0.0f};
        glm::mat4 m_projection = glm::mat4(1.0f);
        glm::mat4 m_view = glm::mat4(1.0f);
        glm::mat4 m_viewProjection = glm::mat4(1.0f);
    };
} // namespace tc
