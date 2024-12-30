#include "pch.h"

#include "3c/graphics/opengl/opengl_shader.h"

#include "3c/core/log.h"
#include "3c/core/assert.h"

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

namespace tc {
    void checkForLinkErrors(uint32_t program) {
        GLint success = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (success == GL_FALSE) {
            GLint length = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(static_cast<size_t>(length));
            glGetProgramInfoLog(program, length, &length, error.data());
            TC_ERROR("Failed to link program:\n{0}", error.data());
        }
    }

    uint32_t linkProgram(uint32_t vertexShader, uint32_t fragmentShader) {
        uint32_t program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        checkForLinkErrors(program);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return program;
    }

    void checkForCompileErrors(uint32_t shader, const std::string &type) {
        GLint success = GL_FALSE;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            GLint length = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(static_cast<size_t>(length));
            glGetShaderInfoLog(shader, length, &length, error.data());
            TC_ERROR("Failed to compile {0} shader:\n{1}", type, error.data());
        }
    }

    std::pair<uint32_t, uint32_t> compileShaders(const std::string &vertexSource, const std::string &fragmentSource) {
        const char *vertexSourceCStr = vertexSource.c_str();
        const char *fragmentSourceCStr = fragmentSource.c_str();

        uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
        uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(vertexShader, 1, &vertexSourceCStr, nullptr);
        glShaderSource(fragmentShader, 1, &fragmentSourceCStr, nullptr);

        glCompileShader(vertexShader);
        checkForCompileErrors(vertexShader, "vertex");

        glCompileShader(fragmentShader);
        checkForCompileErrors(fragmentShader, "fragment");

        return {vertexShader, fragmentShader};
    }

    OpenGLShader::OpenGLShader(const std::string &vertexSource, const std::string &fragmentSource): m_id(0) {
        std::pair<uint32_t, uint32_t> shaderIds = compileShaders(vertexSource, fragmentSource);
        m_id = linkProgram(shaderIds.first, shaderIds.second);
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_id);
    }

    void OpenGLShader::bind() {
        glUseProgram(m_id);
    }

    void OpenGLShader::unbind() {
        glUseProgram(0);
    }

    void OpenGLShader::setBool(const std::string &name, bool value) {
        GLint location = glGetUniformLocation(m_id, name.c_str());
        TC_ASSERT(location != -1, "Uniform not found: {0}", name);
        glUniform1ui(location, value);
    }

    void OpenGLShader::setInt(const std::string &name, int32_t value) {
        GLint location = glGetUniformLocation(m_id, name.c_str());
        TC_ASSERT(location != -1, "Uniform not found: {0}", name);
        glUniform1i(location, value);
    }

    void OpenGLShader::setInt2(const std::string &name, const glm::ivec2 &value) {
        GLint location = glGetUniformLocation(m_id, name.c_str());
        TC_ASSERT(location != -1, "Uniform not found: {0}", name);
        glUniform2i(location, value.x, value.y);
    }

    void OpenGLShader::setInt3(const std::string &name, const glm::ivec3 &value) {
        GLint location = glGetUniformLocation(m_id, name.c_str());
        TC_ASSERT(location != -1, "Uniform not found: {0}", name);
        glUniform3i(location, value.x, value.y, value.z);
    }

    void OpenGLShader::setInt4(const std::string &name, const glm::ivec4 &value) {
        GLint location = glGetUniformLocation(m_id, name.c_str());
        TC_ASSERT(location != -1, "Uniform not found: {0}", name);
        glUniform4i(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::setFloat(const std::string &name, float value) {
        GLint location = glGetUniformLocation(m_id, name.c_str());
        TC_ASSERT(location != -1, "Uniform not found: {0}", name);
        glUniform1f(location, value);
    }

    void OpenGLShader::setFloat2(const std::string &name, const glm::vec2 &value) {
        GLint location = glGetUniformLocation(m_id, name.c_str());
        TC_ASSERT(location != -1, "Uniform not found: {0}", name);
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::setFloat3(const std::string &name, const glm::vec3 &value) {
        GLint location = glGetUniformLocation(m_id, name.c_str());
        TC_ASSERT(location != -1, "Uniform not found: {0}", name);
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::setFloat4(const std::string &name, const glm::vec4 &value) {
        GLint location = glGetUniformLocation(m_id, name.c_str());
        TC_ASSERT(location != -1, "Uniform not found: {0}", name);
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::setMat3(const std::string &name, const glm::mat3 &value) {
        GLint location = glGetUniformLocation(m_id, name.c_str());
        TC_ASSERT(location != -1, "Uniform not found: {0}", name);
        glUniformMatrix3fv(location, 1, GL_FALSE, value_ptr(value));
    }

    void OpenGLShader::setMat4(const std::string &name, const glm::mat4 &value) {
        GLint location = glGetUniformLocation(m_id, name.c_str());
        TC_ASSERT(location != -1, "Uniform not found: {0}", name);
        glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(value));
    }
} // namespace tc
