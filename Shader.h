//
// Created by pointerlost on 7/22/25.
//
#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/ext/matrix_float4x4.hpp"

namespace SHADER {

    class Shader {
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader() = default;

        void use() const;

        uint32_t getShaderProgram() const;

        uint32_t createShaderProgram(const char* vertexPath, const char* fragmentPath);

        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setMat4(const std::string& name, const glm::mat4& value) const;

    private:
        unsigned int m_program;
    };

}
