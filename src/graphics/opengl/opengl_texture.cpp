#include "pch.h"

#include "3c/graphics/opengl/opengl_texture.h"
#include "3c/core/assert.h"

#include <glad/gl.h>

namespace tc {
    GLint getTextureWrapGLType(TextureWrap wrap) {
        switch (wrap) {
            case TextureWrap::REPEAT:
                return GL_REPEAT;
            case TextureWrap::MIRRORED_REPEAT:
                return GL_MIRRORED_REPEAT;
            case TextureWrap::CLAMP_TO_EDGE:
                return GL_CLAMP_TO_EDGE;
            case TextureWrap::CLAMP_TO_BORDER:
                return GL_CLAMP_TO_BORDER;
            default:
                TC_ASSERT(false, "Invalid or missing texture wrap");
        }
    }

    GLint getTextureFilterGLType(TextureFilter filter) {
        switch (filter) {
            case TextureFilter::NEAREST:
                return GL_NEAREST;
            case TextureFilter::LINEAR:
                return GL_LINEAR;
            default:
                TC_ASSERT(false, "Invalid or missing texture filter");
        }
    }

    std::pair<GLenum, GLint> getTextureFormatGLType(TextureFormat format) {
        switch (format) {
            case TextureFormat::RGB:
                return {GL_RGB, GL_RGB8};
            case TextureFormat::RGBA:
                return {GL_RGBA, GL_RGBA8};
            default:
                TC_ASSERT(false, "Invalid or missing texture format");
        }
    }

    uint32_t getBytesPerPixel(TextureFormat format) {
        switch (format) {
            case TextureFormat::RGB:
                return 3;
            case TextureFormat::RGBA:
                return 4;
            default:
                TC_ASSERT(false, "Invalid texture format");
        }
    }

    OpenGLTexture::OpenGLTexture(const TextureParameters &params): m_id(0), m_params(params) {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        // Texture wrap
        GLint textureWrap = getTextureWrapGLType(m_params.wrap);
        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_S,
            textureWrap
        );
        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_WRAP_T,
            textureWrap
        );

        // Texture filter
        GLint textureFilter = getTextureFilterGLType(m_params.filter);
        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            textureFilter
        );
        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER,
            textureFilter
        );

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    OpenGLTexture::~OpenGLTexture() {
        glDeleteTextures(1, &m_id);
    }

    void OpenGLTexture::bind(uint32_t slot) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void OpenGLTexture::unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGLTexture::setData(const std::vector<uint8_t> &data) {
        uint32_t bytesPerPixel = getBytesPerPixel(m_params.format);
        TC_ASSERT(
            data.size() == m_params.width * m_params.height * bytesPerPixel,
            "Data must be the entire texture"
        );

        std::pair<GLenum, GLint> textureFormat = getTextureFormatGLType(m_params.format);

        glBindTexture(GL_TEXTURE_2D, m_id);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            textureFormat.second,
            static_cast<GLsizei>(m_params.width),
            static_cast<GLsizei>(m_params.height),
            0,
            textureFormat.first,
            GL_UNSIGNED_BYTE,
            data.data()
        );
        glBindTexture(GL_TEXTURE_2D, 0);
    }
} // namespace tc
