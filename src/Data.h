#pragma once

#ifndef DATA_DIR
#define DATA_DIR "."
#endif

namespace GL::Data {
    struct Point {
        float x, y, z;
    };

    using Color = Point;

    struct VertexColor {
        Point position;
        Color color;
    };

    struct UV {
        float u, v;
    };

    struct VertexUV {
        Point position;
        UV uv;
    };

    static constexpr VertexColor CUBE_COLOR[] = {
        {{0.5f, -0.5f, -0.5f}, {1.f, 0.f, 0.f}}, // Red
        {{0.5f, -0.5f, 0.5f}, {0.f, 1.f, 0.f}}, // Green
        {{-0.5f, -0.5f, 0.5f}, {0.f, 0.f, 1.f}}, // Blue
        {{-0.5f, -0.5f, -0.5f}, {1.f, 1.f, 0.f}}, // Yellow
        {{0.5f, 0.5f, -0.5f}, {1.f, 0.f, 1.f}}, // Magenta
        {{0.5f, 0.5f, 0.5f}, {0.f, 1.f, 1.f}}, // Cyan
        {{-0.5f, 0.5f, 0.5f}, {1.f, 0.64f, 0.0f}}, // Orange
        {{-0.5f, 0.5f, -0.5f}, {1.f, 0.75f, 0.79f}} // Pink
    };

    static constexpr unsigned int CUBE_COLOR_INDICES[] = {
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

    static constexpr VertexUV SQUARE_UV[] =
    {
        {{300.f, 200.f, -0.5f}, {0.0f, 0.0f}},
        {{500.f, 200.f, -0.5f}, {1.0f, 0.0f}},
        {{500.f, 400.f, -0.5f}, {1.0f, 1.0f}},
        {{300.f, 400.f, -0.5f}, {0.0f, 1.0f}},
    };

    static constexpr unsigned int SQUARE_UV_INDICES[] = {
        0, 1, 2,
        2, 3, 0
    };
}

