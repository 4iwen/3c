#pragma once

#include "3c/core/api.h"

#include <glm/glm.hpp>

namespace tc {
    class TC_API Shader {
    public:
        virtual ~Shader() = default;

        virtual void bind() = 0;

        virtual void unbind() = 0;

        virtual void setBool(const std::string &name, bool value) = 0;

        virtual void setInt(const std::string &name, int32_t value) = 0;

        virtual void setInt2(const std::string &name, const glm::ivec2 &value) = 0;

        virtual void setInt3(const std::string &name, const glm::ivec3 &value) = 0;

        virtual void setInt4(const std::string &name, const glm::ivec4 &value) = 0;

        virtual void setFloat(const std::string &name, float value) = 0;

        virtual void setFloat2(const std::string &name, const glm::vec2 &value) = 0;

        virtual void setFloat3(const std::string &name, const glm::vec3 &value) = 0;

        virtual void setFloat4(const std::string &name, const glm::vec4 &value) = 0;

        virtual void setMat3(const std::string &name, const glm::mat3 &value) = 0;

        virtual void setMat4(const std::string &name, const glm::mat4 &value) = 0;

        static std::shared_ptr<Shader> create(const std::string &vertexSource, const std::string &fragmentSource);

        static std::shared_ptr<Shader> createFromFile(const std::string &vertexPath, const std::string &fragmentPath);
    };
} // namespace tc
