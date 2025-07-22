//
// Created by pointerlost on 7/22/25.
//
#include <iostream>
#include "Shader.h"
#include "FileHandler.h"

namespace SHADER {
    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
        const std::string vertex = core::FileHandler::readFile(vertexPath);
        const std::string fragment = core::FileHandler::readFile(fragmentPath);

        m_program = createShaderProgram(vertex.c_str(), fragment.c_str());
    }

    void Shader::use() const {
        glUseProgram(m_program);
    }

    uint32_t Shader::getShaderProgram() const {
        return m_program;
    }

    uint32_t Shader::createShaderProgram(const char* vertexPath, const char* fragmentPath) {

        // create vertex shader
        const uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexPath, nullptr);
        glCompileShader(vertexShader);

        // Check compile status
        GLint success;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cerr << "Shader compile error: " << infoLog << "\n";
        }

        // create fragment shader
        const uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentPath, nullptr);
        glCompileShader(fragmentShader);

        // Check compile status
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            std::cerr << "Shader compile error: " << infoLog << "\n";
        }

        // create program shader
        const uint32_t program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        // Check compile status
        glGetShaderiv(program, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(program, 512, nullptr, infoLog);
            std::cerr << "Shader compile error: " << infoLog << "\n";
        }

        return program;
    }
}
