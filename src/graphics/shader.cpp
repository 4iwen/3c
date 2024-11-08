#include "pch.h"

#include "3c/graphics/shader.h"
#include "3c/core/assert.h"
#include "3c/graphics/renderer.h"
#include "3c/graphics/opengl/opengl_shader.h"

namespace tc {
    std::shared_ptr<Shader> Shader::create(const std::string &vertexSource, const std::string &fragmentSource) {
        switch (Renderer::getGraphicsAPIType()) {
            default:
                TC_ASSERT(false, "No graphics API selected");
            case GraphicsAPIType::OPENGL:
                return std::make_shared<OpenGLShader>(vertexSource, fragmentSource);
        }
    }

    std::shared_ptr<Shader> Shader::createFromFile(const std::string &vertexPath, const std::string &fragmentPath) {
        std::ifstream vertexFile(vertexPath);
        TC_ASSERT(vertexFile.is_open(), "Failed to open vertex shader file: {0}", vertexPath);

        std::string vertexSource;
        while (!vertexFile.eof()) {
            std::string line;
            std::getline(vertexFile, line);
            vertexSource += line + "\n";
        }

        vertexFile.close();

        std::ifstream fragmentFile(fragmentPath);
        TC_ASSERT(fragmentFile.is_open(), "Failed to open fragment shader file: {0}", fragmentPath);

        std::string fragmentSource;
        while (!fragmentFile.eof()) {
            std::string line;
            std::getline(fragmentFile, line);
            fragmentSource += line + "\n";
        }

        fragmentFile.close();

        switch (Renderer::getGraphicsAPIType()) {
            default:
                TC_ASSERT(false, "No graphics API selected");
            case GraphicsAPIType::OPENGL:
                return std::make_shared<OpenGLShader>(vertexSource, fragmentSource);
        }
    }
} // namespace tc
