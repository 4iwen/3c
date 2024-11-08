#include "pch.h"

#include "3c/graphics/opengl/opengl_renderer.h"

#include <glad/gl.h>

namespace tc {
    OpenGLRenderer::OpenGLRenderer() {
        const char* version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
        const char* vendor = reinterpret_cast<const char *>(glGetString(GL_VENDOR));
        const char* renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
        TC_INFO("OpenGL renderer created:");
        TC_INFO("  Version: {0}", version);
        TC_INFO("  Vendor: {0}", vendor);
        TC_INFO("  Renderer: {0}", renderer);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }

    OpenGLRenderer::~OpenGLRenderer() = default;

    void OpenGLRenderer::clear(glm::vec4 color) {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderer::submit(const std::shared_ptr<VertexArray> &vertexArray) {
        vertexArray->bind();
        glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRenderer::setViewport(uint32_t width, uint32_t height) {
        glViewport(0, 0, width, height);
    }
}
