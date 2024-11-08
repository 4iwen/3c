#pragma once

#include "3c/graphics/shader.h"

namespace tc {
    class TC_API OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string &vertexSource, const std::string &fragmentSource);

        ~OpenGLShader() override;

        void bind() override;

        void unbind() override;

        void setBool(const std::string &name, bool value) override;

        void setInt(const std::string &name, int32_t value) override;

        void setInt2(const std::string &name, const glm::ivec2 &value) override;

        void setInt3(const std::string &name, const glm::ivec3 &value) override;

        void setInt4(const std::string &name, const glm::ivec4 &value) override;

        void setFloat(const std::string &name, float value) override;

        void setFloat2(const std::string &name, const glm::vec2 &value) override;

        void setFloat3(const std::string &name, const glm::vec3 &value) override;

        void setFloat4(const std::string &name, const glm::vec4 &value) override;

        void setMat3(const std::string &name, const glm::mat3 &value) override;

        void setMat4(const std::string &name, const glm::mat4 &value) override;

    private:
        uint32_t m_id;
    };
} // namespace tc
