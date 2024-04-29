#include "OBJRenderer/OBJRenderer.h"
#include "OBJParser/OBJParser.h"
#include "ArgvParser/ArgvParser.h"


int main(const int argc, const char *argv[]) {
    const auto opt_parser = parse_args(argc, argv);
    if (!opt_parser.has_value()) {
        return 1;
    }
    const OBJRendererSettings& argv_parser = opt_parser.value();

    OBJRenderer renderer(Vec2D{argv_parser.width, argv_parser.height}, Color{0, 0, 0}, SImg::BOTTOM_LEFT);
    for (const OBJParser parser(argv_parser.infile); const auto& face : parser.get_faces()) {
        const Vec3D first = parser.get_vertices().at(face.at(0) - 1);
        const Vec3D second = parser.get_vertices().at(face.at(1) - 1);
        const Vec3D third = parser.get_vertices().at(face.at(2) - 1);

        const auto first_v = Vec2D{static_cast<int>((first.x + 1.) * (renderer.get_width()-1) / 2.), static_cast<int>((first.y + 1.) * (renderer.get_height()-1) / 2.)};
        const auto second_v = Vec2D{static_cast<int>((second.x + 1.) * (renderer.get_width()-1) / 2.), static_cast<int>((second.y + 1.) * (renderer.get_height()-1) / 2.)};
        const auto third_v = Vec2D{static_cast<int>((third.x + 1.) * (renderer.get_width()-1) / 2.), static_cast<int>((third.y + 1.) * (renderer.get_height()-1) / 2.)};

        renderer.draw_triangle(first_v, second_v, third_v, get_random_color());
    }

    renderer.save(argv_parser.outfile);
    if (argv_parser.openfile) {
        SImg::open_file(argv_parser.outfile);
    }

    return 0;
}
