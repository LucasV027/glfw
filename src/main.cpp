#include "Application.h"

int main() {
    GL::Application app(800, 600, "Hello world !");
    app.mainLoop();

    return 0;
}
