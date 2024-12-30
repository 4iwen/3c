#pragma once

#include "3c/core/api.h"

namespace tc {
    enum class TC_API TextureFormat {
        NONE,
        RGB,
        RGBA
    };

    enum class TC_API TextureWrap {
        NONE,
        REPEAT,
        MIRRORED_REPEAT,
        CLAMP_TO_EDGE,
        CLAMP_TO_BORDER
    };

    enum class TC_API TextureFilter {
        NONE,
        NEAREST,
        LINEAR
    };

    struct TC_API TextureParameters {
        uint32_t width;
        uint32_t height;
        TextureFormat format;
        TextureWrap wrap;
        TextureFilter filter;
    };

    // only 2D for now
    class TC_API Texture {
    public:
        virtual ~Texture() = default;

        virtual void bind(uint32_t slot) = 0;

        virtual void unbind() = 0;

        virtual void setData(const std::vector<uint8_t> &data) = 0;

        static std::shared_ptr<Texture> create(const TextureParameters &params);

        static std::shared_ptr<Texture> createFromFile(
            const std::string &path,
            TextureParameters &params
        );
    };
} // namespace tc
