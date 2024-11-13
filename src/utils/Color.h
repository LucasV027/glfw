#pragma once

namespace GL {
    class Color {
    public:
        float r, g, b;
    };

    namespace Colors {
       constexpr Color RED(1.f, 0.f, 0.f);
       constexpr Color GREEN(0.f, 1.f, 0.f);
       constexpr Color BLUE(0.f, 0.f, 1.f);
       constexpr Color YELLOW(1.f, 1.f, 0.f);
       constexpr Color CYAN(0.f, 1.f, 1.f);
       constexpr Color MAGENTA(1.f, 0.f, 1.f);
       constexpr Color BLACK(0.f, 0.f, 0.f);
       constexpr Color WHITE(1.f, 1.f, 1.f);
       constexpr Color GRAY(0.5f, 0.5f, 0.5f);
       constexpr Color ORANGE(1.f, 0.647f, 0.f);
       constexpr Color PINK(1.f, 0.f, 0.5f);
       constexpr Color PURPLE(0.5f, 0.f, 0.5f);
       constexpr Color BROWN(0.6f, 0.3f, 0.2f);
       constexpr Color OLIVE(0.5f, 0.5f, 0.f);
    }
}
