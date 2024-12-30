#pragma once

#include "3c/graphics/texture.h"

namespace tc {
    class TC_API OpenGLTexture : public Texture {
    public:
        OpenGLTexture(const TextureParameters &params);

        ~OpenGLTexture() override;

        void bind(uint32_t slot) override;

        void unbind() override;

        void setData(const std::vector<uint8_t> &data) override;

    private:
        uint32_t m_id;
        TextureParameters m_params;
    };
} // namespace tc
