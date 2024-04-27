#include "OBJRenderer/OBJRenderer.h"

int main() {
    OBJRenderer a(Vec2D{100, 100}, Color{0, 0, 0}, SImg::BOTTOM_LEFT);

    a.draw_line(Vec2D{0, 0}, Vec2D{50, 50}, Color{255, 255, 255});
    a.save("hello.ppm");
    SImg::open_file("hello.ppm");
    return 0;
}
