#include "pch.h"

#include "3c/graphics/cameras/orthographic_camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace tc {
    OrthographicCamera::OrthographicCamera(const OrthographicCameraParameters &params): m_params(params) {
        OrthographicCamera::recalculateViewProjection();
    }

    OrthographicCamera::~OrthographicCamera() {
    }

    void OrthographicCamera::setAspectRatio(float aspectRatio) {
        m_params.aspectRatio = aspectRatio;
        recalculateViewProjection();
    }

    void OrthographicCamera::recalculateViewProjection() {
        m_projection = glm::ortho(
            -m_params.aspectRatio * m_params.zoom,
            m_params.aspectRatio * m_params.zoom,
            -m_params.zoom,
            m_params.zoom,
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
