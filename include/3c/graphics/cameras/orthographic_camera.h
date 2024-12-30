#pragma once

#include "3c/core/api.h"
#include "3c/graphics/cameras/camera.h"

namespace tc {
    struct OrthographicCameraParameters {
        float aspectRatio;
        float zoom;
        float near;
        float far;

        OrthographicCameraParameters(
            float aspectRatio,
            float zoom,
            float near,
            float far
        ): aspectRatio(aspectRatio), zoom(zoom), near(near), far(far) {
        }
    };

    class TC_API OrthographicCamera : public Camera {
    public:
        OrthographicCamera(const OrthographicCameraParameters &params);

        ~OrthographicCamera() override;

        void setAspectRatio(float aspectRatio) override;

    private:
        void recalculateViewProjection() override;

    private:
        OrthographicCameraParameters m_params;
    };
} // namespace tc
