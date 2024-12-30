#pragma once

#include "3c/core/api.h"
#include "3c/graphics/cameras/camera.h"

namespace tc {
    struct PerspectiveCameraParameters {
        float aspectRatio;
        float fov = 90.0f;
        float near = 0.1f;
        float far = 100.0f;
    };

    class TC_API PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera(const PerspectiveCameraParameters &params);

        ~PerspectiveCamera() override;

        void setAspectRatio(float aspectRatio) override;

    private:
        void recalculateViewProjection() override;

    private:
        PerspectiveCameraParameters m_params;
    };
} // namespace tc
