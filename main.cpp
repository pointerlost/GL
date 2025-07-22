#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "FileHandler.h"
#include "Shader.h"
#include <filesystem>

float triangle[] = {
    -0.5, -0.5, 0.0,  1.0, 1.0, 0.0,
     0.0,  0.5, 0.0,  0.0, 1.0, 0.0,
     0.5, -0.5, 0.0,  0.0, 0.0, 1.0
};


int main() {

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return 1;
    }
    GLFWwindow* window = glfwCreateWindow(720, 480, "OpenGL | Shaders", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGL()) {
        std::cout << "Failed to load GLAD" << std::endl;
        return -1;
    }

    // prepare vao and vbo to send data to the gpu
    uint32_t VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO and VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    // send position to GPU
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // send color to the GPU
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    const SHADER::Shader shader("basic.vert", "basic.frag");

    // engine life-loop
    while (!glfwWindowShouldClose(window)) {
        // this cleaning the new back buffer before we draw the new frame
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);

        auto transform = glm::mat4(1.0f);
        // transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        transform = glm::rotate(transform, static_cast<float>(glfwGetTime()), glm::vec3(1.0f, 0.0f, 0.0f));

        // bind the program
        shader.use();

        // get uniform location from GPU
        const auto transformLoc = glGetUniformLocation(shader.getShaderProgram(), "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        // bind the VAO
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // back and front buffers swap, then
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}