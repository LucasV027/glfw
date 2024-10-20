#include "glApplication.h"

int main() {
    glApplication app(600, 600, "Hello world !");
    app.mainLoop();

    return 0;
}
