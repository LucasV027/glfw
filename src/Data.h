#pragma once


namespace lgl::Data {
    struct Point {
        float x, y, z;
    };

    using Color = Point;

    static constexpr Point points[] = {
        {-0.5f, -0.5f, 0.0f},
        {0.5f, -0.5f, 0.0f},
        {0.f, 0.5f, 0.0f},
    };

    static constexpr Color colors[] = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };

    float vertices[] = {
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f // top left
    };
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };

    static constexpr float cubeVertices[] = {
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
    };

    struct Vertex {
        Point position;
        Color color;
    };

    static constexpr Vertex cubeVerticesWithColors[] = {
        {{ 0.5f, -0.5f, -0.5f}, {1.f, 0.f, 0.f}},  // Red
        {{ 0.5f, -0.5f,  0.5f}, {0.f, 1.f, 0.f}},  // Green
        {{-0.5f, -0.5f,  0.5f}, {0.f, 0.f, 1.f}},  // Blue
        {{-0.5f, -0.5f, -0.5f}, {1.f, 1.f, 0.f}},  // Yellow
        {{ 0.5f,  0.5f, -0.5f}, {1.f, 0.f, 1.f}},  // Magenta
        {{ 0.5f,  0.5f,  0.5f}, {0.f, 1.f, 1.f}},   // Cyan
        {{-0.5f,  0.5f,  0.5f}, {1.f, 0.64f, 0.0f}}, // Orange
        {{-0.5f,  0.5f, -0.5f}, {1.f, 0.75f, 0.79f}}  // Pink
    };

    static constexpr unsigned int cubeIndices[] = {
        1, 2, 3,
        4, 7, 6,
        4, 5, 1,
        1, 5, 6,
        6, 7, 3,
        4, 0, 3,
        0, 1, 3,
        5, 4, 6,
        0, 4, 1,
        2, 1, 6,
        2, 6, 3,
        7, 4, 3
    };


    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void *>(0));
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void *>(sizeof(Point)));
}

