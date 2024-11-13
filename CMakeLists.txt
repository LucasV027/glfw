cmake_minimum_required(VERSION 3.5)
project(glfw-project)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} src/main.cpp
        src/Application.cpp
        src/Application.h
        src/glAbstraction/Program.cpp
        src/glAbstraction/Program.h
        src/glAbstraction/Debug.cpp
        src/glAbstraction/Debug.h
        src/glAbstraction/VertexBuffer.cpp
        src/glAbstraction/VertexBuffer.h
        src/glAbstraction/IndexBuffer.cpp
        src/glAbstraction/IndexBuffer.h
        src/glAbstraction/VertexArray.cpp
        src/glAbstraction/VertexArray.h
        src/glAbstraction/VertexBufferLayout.cpp
        src/glAbstraction/VertexBufferLayout.h
        src/glAbstraction/Renderer.cpp
        src/glAbstraction/Renderer.h
        src/Data.h
        src/extern/stb_image.h
)

# dependencies
include(FetchContent)

# OpenGL
find_package(OpenGL)

# Glad
FetchContent_Declare(glad GIT_REPOSITORY https://github.com/Dav1dde/glad.git GIT_TAG df8e9e16110b305479a875399cee13daa0ccadd9)
FetchContent_MakeAvailable(glad)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.3.2)
FetchContent_MakeAvailable(glfw)

# GLM
FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git GIT_TAG 1.0.1)
FetchContent_MakeAvailable(glm)

target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw glm)
