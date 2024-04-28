#include <iostream>

#include "OBJRenderer/OBJRenderer.h"
#include "OBJParser/OBJParser.h"

int main() {
    OBJRenderer a(Vec2D{1000, 1000}, Color{0, 0, 0}, SImg::BOTTOM_LEFT);

    for (const OBJParser b("person.obj"); const auto& face : b.get_faces()) {
        auto first = b.get_vertices().at(face.at(0)-1);
        auto second = b.get_vertices().at(face.at(1)-1);
        auto third = b.get_vertices().at(face.at(2)-1);

        const auto first_v = Vec2D{static_cast<int>((first.x + 1.) * (a.get_width()-1) / 2.), static_cast<int>((first.y + 1.) * (a.get_height()-1) / 2.)};
        const auto second_v = Vec2D{static_cast<int>((second.x + 1.) * (a.get_width()-1) / 2.), static_cast<int>((second.y + 1.) * (a.get_height()-1) / 2.)};
        const auto third_v = Vec2D{static_cast<int>((third.x + 1.) * (a.get_width()-1) / 2.), static_cast<int>((third.y + 1.) * (a.get_height()-1) / 2.)};

        a.draw_line(first_v, second_v, Color{255, 255, 255});
        a.draw_line(second_v, third_v, Color{255, 255, 255});
        a.draw_line(third_v, first_v, Color{255, 255, 255});
    }

    a.save("hello.ppm");
    SImg::open_file("hello.ppm");
    return 0;
}
