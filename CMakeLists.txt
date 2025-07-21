cmake_minimum_required(VERSION 3.31)

project(OpenGL)

set(CMAKE_CXX_STANDARD 20)

add_executable(OpenGL main.cpp)

target_include_directories(OpenGL PRIVATE
        "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-linux/include/"
)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(OpenGL PRIVATE
        glad::glad
        glfw
        glm::glm
)