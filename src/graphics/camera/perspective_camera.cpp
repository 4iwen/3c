#include "pch.h"

#include "3c/graphics/cameras/perspective_camera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace tc {
    PerspectiveCamera::PerspectiveCamera(const PerspectiveCameraParameters &params) : m_params(params) {
        PerspectiveCamera::recalculateViewProjection();
    }

    PerspectiveCamera::~PerspectiveCamera() {
    }

    void PerspectiveCamera::setAspectRatio(float aspectRatio) {
        m_params.aspectRatio = aspectRatio;
        recalculateViewProjection();
    }

    void PerspectiveCamera::recalculateViewProjection() {
        m_projection = glm::perspective(
            glm::radians(m_params.fov),
            m_params.aspectRatio,
            m_params.near,
            m_params.far
        );

        m_view = glm::translate(glm::mat4(1.0f), m_position) *
                 glm::rotate(glm::mat4(1.0f), m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
                 glm::rotate(glm::mat4(1.0f), m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
                 glm::rotate(glm::mat4(1.0f), m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

        m_viewProjection = m_projection * m_view;
    }
} // namespace tc
