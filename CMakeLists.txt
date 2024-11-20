cmake_minimum_required(VERSION 3.5)
project(glfw-project)

set(CMAKE_CXX_STANDARD 20)
set(DATA_DIR \"${CMAKE_SOURCE_DIR}/res\")

add_executable(${PROJECT_NAME}
        src/main.cpp

        src/Application.cpp
        src/Application.h

        src/gl/Program.cpp
        src/gl/Program.h
        src/gl/Debug.cpp
        src/gl/Debug.h
        src/gl/VertexBuffer.cpp
        src/gl/VertexBuffer.h
        src/gl/IndexBuffer.cpp
        src/gl/IndexBuffer.h
        src/gl/VertexArray.cpp
        src/gl/VertexArray.h
        src/gl/VertexBufferLayout.cpp
        src/gl/VertexBufferLayout.h
        src/gl/Renderer.cpp
        src/gl/Renderer.h
        src/gl/Texture.h
        src/gl/Texture.cpp

        src/utils/Data.h
        src/utils/Color.h
        src/utils/Color.cpp

        src/core/scene/Scene.h
        src/core/scene/TextureScene.h
        src/core/scene/TextureScene.cpp
        src/core/scene/ClearColorScene.cpp
        src/core/scene/ClearColorScene.h
        src/core/scene/CubeScene.h
        src/core/scene/CubeScene.cpp

        src/core/Camera.h
        src/core/Camera.cpp

        src/extern/stb_image.h
        src/extern/stb_image.cpp

        src/utils/Loader.h
        src/utils/Loader.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src src/extern src/gl src/core/scene src/utils src/core)
target_compile_definitions(${PROJECT_NAME} PRIVATE DATA_DIR=${DATA_DIR})

include(cmake/dependencies.cmake)
target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw glm imgui)
