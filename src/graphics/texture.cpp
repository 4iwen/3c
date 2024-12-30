#include "pch.h"

#include "3c/graphics/texture.h"

#include "3c/graphics/renderer.h"
#include "3c/graphics/opengl/opengl_texture.h"
#include "3c/core/utils.h"

#include <stb_image.h>

namespace tc {
    std::shared_ptr<Texture> Texture::create(const TextureParameters &params) {
        switch (Renderer::getGraphicsAPIType()) {
            default:
                TC_ASSERT(false, "No graphics API selected");
            case GraphicsAPIType::OPENGL:
                return std::make_shared<OpenGLTexture>(params);
        }
    }

    std::shared_ptr<Texture> Texture::createFromFile(const std::string &path, TextureParameters &params) {
        stbi_set_flip_vertically_on_load(1);

        int32_t width;
        int32_t height;
        int32_t channels;
        stbi_uc *data = stbi_load(
            path.c_str(),
            &width,
            &height,
            &channels,
            0
        );
        TC_ASSERT(data, "Failed to load image: {0}", path);
        TC_ASSERT(channels == 3 || channels == 4, "Unsupported channel count: {0}", channels);

        params.width = static_cast<uint32_t>(width);
        params.height = static_cast<uint32_t>(height);
        params.format = channels == 3 ? TextureFormat::RGB : TextureFormat::RGBA;

        std::vector<uint8_t> dataVec(
            data,
            data + width * height * channels
        );

        std::shared_ptr<Texture> texture = create(params);
        texture->setData(
            dataVec
        );

        stbi_image_free(data);
        return texture;
    }
} // namespace tc
