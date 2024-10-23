#pragma once

#include <glad/glad.h>

namespace lgl::debug {
    void APIENTRY PrintGlDebugOutput(GLenum source,
                                     GLenum type,
                                     unsigned int id,
                                     GLenum severity,
                                     GLsizei length,
                                     const char *message,
                                     const void *userParam);
}

